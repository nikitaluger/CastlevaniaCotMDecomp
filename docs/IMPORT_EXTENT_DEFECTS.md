# Import-time extent defects — findings and repair log

Baseline for comparison: commit `c0108aa` (the original save as committed before this session).
App versions: started on 1.0.11-rr.1 (branch build), upgraded to 1.0.13-rr.1, then 1.0.14-rr.1 (release channel).

## Result

| Metric | Baseline (`c0108aa`) | Now | Delta |
|---|---:|---:|---:|
| Matched functions | 3,894 | 3,948 | **+54** |
| Set aside (`asm`) | 368 | 340 | −28 (24 phantoms removed, 4 recovered functions matched) |
| Layout entries | 4,551 | 4,527 | −24 |

≈32 of the new matches are directly attributable to the repairs below (3 boundary cuts, 22 extent extensions,
1 compiler-profile correction, 7 source restorations, and 5 from the re-point fixes); the remainder came from
autopilot/deep-permuter passes and the app's token-free local-source reuse.

## Root cause

The wrong function extents were **already present in the baseline**, not introduced by the migration. In the
original project these functions were best attempts (scores 100–1000), never matches. The defect originates in
the initial port/import of the ROM: the GBA splitter records function ends at the return instruction and
excludes the function's own trailing literal pool and alignment pad. The pool bytes are then either left
outside the declared extent (compiled object emits its own pool → permanent extra diff rows) or misclassified
as tiny separate `asm` functions (`pad_*`, `sub_080…` 2–20 byte entries). One such artifact was a zero-byte
function (`sub_0801569A`) which the newer app's manifest validator rejected outright, blocking every sync.

A second sub-type of the same import bug: the splitter sometimes placed a function start **on a literal-pool
word** rather than at the real prologue 2–4 bytes later. The "function" then began with the halfwords of another
function's constant (e.g. `sub_0805B878` began with `subs r0,r6,r6; lsrs r7,r4,#1`, which are really the two
halfwords of `0x08671BB0` loaded by `sub_0805B808`). Agents interpreted these as linker leftovers or a
non-standard calling convention and set the entry aside; correcting the address made 7 of 8 such cases match.

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
| `sub_08055840` | 74 → 84 | was set aside; reopened, score-500 source restored, phantom `sub_0805588A` removed |
| `sub_080A36AC` | 300 → 324 | was set aside; reopened, score-1200 source restored |
| `sub_08080920` | 200 → 220 | phantom `sub_080809E8` removed |
| `sub_08012A94` | 416 → 432 | **still unmatched** (see below) |
| `sub_08012C44` | 416 → 432 | **still unmatched** (see below) |

### Compiler-profile correction

`sub_080825EC` (192 → 212 bytes) plus its exact compiler range changed from
`-mno-thumb-interwork -O2 -fno-strength-reduce` to `-mthumb-interwork -O2 -fno-strength-reduce`
(12 of its 12 nearest matched neighbours use the latter). Body became byte-exact and it matched.

### Re-point fixes (neighbour starts on a literal-pool word)

Four pairs had a set-aside neighbour whose `vram` pointed at a pool word instead of the real prologue. For each,
the preceding function was extended through its literal and the neighbour was re-pointed to the real entry with
the same end address; `rom_offset`, target and symbol were re-derived, and the manifest layout/`set_aside` vram
updated. The neighbour's set-aside status was preserved unless the judge matched it.

| Preceding function | Re-pointed neighbour | Result |
|---|---|---|
| `sub_0805B808` 110 → 116 | `sub_0805B878` 460 → 388 @ `0x0805B87C` | both matched (agent / reused) |
| `sub_08021200` 136 → 140 | `sub_0802128A` 54 → 52 @ `0x0802128C` | both matched (`restored` + autopilot) |
| `sub_080653B0` 240 → 244 | `sub_080654A0` 392 → 388 @ `0x080654A4` | preceding matched; neighbour remains set aside with corrected bytes |
| `sub_0801E0DC` 76 → 80 | `sub_0801E12A` 54 → 52 @ `0x0801E12C` | both matched (`restored` + autopilot) |

## Unresolved

`sub_08012A94` and `sub_08012C44` (twins, both 432 bytes, open, best 200) have all 203 instructions present
and differ by exactly one row: ROM `adds r3,r7,#0` vs agbcc `movs r3,#0` for `i = status` with `status = 0`.
Every C spelling, declaration permutation, type, volatile/register hint, flag profile, repair family and
`prove_chain` has been tried without moving off 200. Both are left open with no active claim so the token-free
local-source reuse path can still solve them — a single source variant emitting the register copy should fix both.

Several other open functions are genuine compiler walls (frameless-leaf LR frames, high-register coloring
ties, linker-level interworking veneers) with 100–500 attempts across many models. A set-aside audit of 347
entries found two further extent mislabels (`sub_08055840`, `sub_080A36AC`), both repaired above; the remaining
small entries are padding, literal fragments or BIOS stubs, and the larger ones are documented toolchain ceilings.
`sub_080654A0` (388 B, re-pointed to `0x080654A4`) is still set aside: its old verdict ("non-standard calling
convention, hand-written asm") was based on the pool-word halfwords now excluded from its extent, so the reason
is obsolete, but 1,140 attempts stayed between scores 17,805 and 18,005 and there is no preserved source — a
new agent would need to reconstruct a large function from scratch.

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
6. For a re-point case, instead of deleting the neighbour: set its `vram`, `rom_offset`, `size`, `n_insns` and
   `target` from the ROM at the real prologue address, update its symbol and the manifest layout/`set_aside` vram,
   and keep the same end address. Check no other function starts inside the new range.
7. Let the agents recompile. Do not hand-edit the manifest while the app is running without checking the DB lock;
   four app hangs during the session required a forced stop/restart (API timeouts, 75–93% CPU, 4–9 GB RSS,
   DB write lock held for minutes). The DB kept every match; the manifest needed one restart cycle to flush the
   most recent one.
