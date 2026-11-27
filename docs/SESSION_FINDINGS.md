# Session findings — extent repairs and migration fallout

Baseline for comparison: commit `c0108aa` (the original save as committed before this session).
App versions: started on 1.0.11-rr.1 (branch build), upgraded to 1.0.13-rr.1, then 1.0.14-rr.1 (release channel).

## Result

| Metric | Baseline (`c0108aa`) | Now | Delta |
|---|---:|---:|---:|
| Matched functions | 3,894 | 3,938 | **+44** |
| Set aside (`asm`) | 368 | 346 | −22 (phantom entries removed) |
| Layout entries | 4,551 | 4,529 | −22 |

≈21 of the new matches are directly attributable to the repairs listed below; the remainder came from
autopilot/deep-permuter passes and the app's token-free local-source reuse.

## Root cause

The wrong function extents were **already present in the baseline**, not introduced by the migration. In the
original project these functions were best attempts (scores 100–1000), never matches. The defect originates in
the initial port/import of the ROM: the GBA splitter records function ends at the return instruction and
excludes the function's own trailing literal pool and alignment pad. The pool bytes are then either left
outside the declared extent (compiled object emits its own pool → permanent extra diff rows) or misclassified
as tiny separate `asm` functions (`pad_*`, `sub_080…` 2–20 byte entries). One such artifact was a zero-byte
function (`sub_0801569A`) which the newer app's manifest validator rejected outright, blocking every sync.

The migration was the **trigger**, not the cause: the newer build validates manifests strictly and judges
saved C against these extents, so the old latent defect became visible. The dev fixed the zero-size crash in
1.0.13 ("a function without a recorded size no longer stops saving"; reader skips zero-size entries with no C).

## Repairs applied

All edits were made with a DB backup and a manifest backup under `backups/`, verified against the ROM bytes at
the target address, and validated with the app's own `_manifest` validator before resuming sync.

### Boundary cuts (declared extent too long — the trailing bytes were the *next* function's prologue)

| Function | Size |
|---|---|
| `sub_080548C8` | 76 → 72 |
| `sub_08075DA4` | 172 → 168 |
| `sub_080B4F34` | 100 → 96 |

### Extent extensions (declared extent too short — excluded the function's own pool/pad)

| Function | Size | Notes |
|---|---|---|
| `sub_080AD8D4` | 128 → 132 | phantom `sub_080AD956` removed |
| `sub_08012704` | 360 → 364 | |
| `sub_0808AFD4` | 104 → 108 | bad 135-score source replaced with correct 300-score C |
| `sub_08053DFC` | 264 → 268 | |
| `sub_0804964C` | 68 → 72 | phantom `sub_08049692` removed |
| `sub_0807FB98` | 148 → 152 | |
| `sub_08032A04` | 72 → 76 | invalid 115-score source replaced with correct 200-score C |
| `sub_080BA79C` | 60 → 64 | invalid 135-score source replaced with correct 200-score C |
| `sub_080B8084` | 78 → 84 | fence/r7 135-score source replaced with correct 300-score C |
| `sub_0807F5E0` | 148 → 152 | |
| `sub_08084348` | 148 → 152 | |
| `sub_08079DF0` | 348 → 352 | |
| `sub_0806A5C8` | 474 → 484 | stale 365 source replaced with correct 500-score C; two phantoms removed |
| `sub_08082B58` | 190 → 208 | |
| `sub_0808154C` | 218 → 236 | |
| `sub_08081AE8` | 190 → 208 | saved 1325 source was known-wrong; an agent wrote fresh C and matched |
| `sub_0801565C` | 60 → 64 | absorbed `sub_0801569A`; exact match later found by local-source reuse (`remaining` vs `t`) |
| `sub_0808039C` | 202 → 220 | |
| `sub_0804C2F8` | 240 → 248 | pool phantom `sub_0804C3E8` removed |
| `sub_08012A94` | 416 → 432 | **still unmatched** (see below) |
| `sub_08012C44` | 416 → 432 | **still unmatched** (see below) |

### Compiler-profile correction

`sub_080825EC` (192 → 212 bytes) plus its exact compiler range changed from
`-mno-thumb-interwork -O2 -fno-strength-reduce` to `-mthumb-interwork -O2 -fno-strength-reduce`
(12 of its 12 nearest matched neighbours use the latter). Body became byte-exact and it matched.

## Unresolved

`sub_08012A94` and `sub_08012C44` (twins, both 432 bytes, open, best 200) have all 203 instructions present
and differ by exactly one row: ROM `adds r3,r7,#0` vs agbcc `movs r3,#0` for `i = status` with `status = 0`.
Every C spelling, declaration permutation, type, volatile/register hint, flag profile, repair family and
`prove_chain` has been tried without moving off 200. Both are left open with no active claim so the token-free
local-source reuse path can still solve them — a single source variant emitting the register copy should fix both.

Several other open functions are genuine compiler walls (frameless-leaf LR frames, high-register coloring
ties, linker-level interworking veneers) with 100–500 attempts across many models. A set-aside audit of all 347
entries found no further extent/phantom mislabels; the small entries are padding, literal fragments or BIOS
stubs, and the larger ones are documented toolchain ceilings.

## Procedure used for an extent repair

1. Confirm the proposed end from **ROM bytes**, not from agent notes (some notes contain typo'd addresses).
2. Ownership check: the trailing bytes must be referenced by this function's own code (pcrel `ldr` into the pool)
   or be the next function's prologue. A return instruction (`4700` / `7047`) at the proposed end means the
   report is cutting off the function's own return — do not apply it.
3. Back up `progress/decompdecomp.json` and the project DB to `backups/` (on the real disk; `/tmp` is a 16 GB
   tmpfs and filled up once).
4. In one transaction: extend `size`/`n_insns`/`target`, delete the pool phantom row + claim + symbol, update the
   function's symbol size; mirror the layout/`set_aside` change in the manifest. For source restores, set
   `best_source` to the known-good payload digest and restore `best/<name>.c`.
5. Validate with `progress._manifest(...)`; the first validation may transiently fail while the app moves the
   phantom's draft to `unlisted/` — re-check after the move.
6. Let the agents recompile. Do not hand-edit the manifest while the app is running without checking the DB lock;
   two app hangs required a forced stop/restart.
