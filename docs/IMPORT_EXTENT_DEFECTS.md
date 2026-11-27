# Import-time extent defects — findings and repair log

Baseline for comparison: commit `c0108aa` (the original save as committed before this session).
App versions: started on 1.0.11-rr.1 (branch build), upgraded to 1.0.13-rr.1, then 1.0.14-rr.1 (release channel).

## Result

| Metric | Baseline (`c0108aa`) | Now | Delta |
|---|---:|---:|---:|
| Matched functions | 3,894 | 3,959 | **+65** |
| Set aside (`asm`) | 368 | 316 | −52 (phantom deletions, recovered functions matched) |
| Layout entries | 4,551 | 4,519 | −32 |

A large share of the new matches is directly attributable to the repairs below: 3 boundary cuts, 30+ extent
extensions, 1 compiler-profile correction, 7 source restorations, six re-point pairs, two jump-table/data
splits, three recovered 4-byte prologue stubs and ten phantom deletions. The remainder came from
autopilot/deep-permuter passes and the app's token-free local-source reuse. Many agent notes blamed "terminal
compiler walls"; the corrected bytes matched within 4–45 attempts.

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

Two further shapes of the same import bug appeared in the larger cases: a function could be declared as a
**4-byte `pad_*` prologue stub** with its entire body unlisted (`pad_08054910`, `pad_08075E4C`, `pad_080B4F94`
— all matched once extended to 488/336/196 bytes), and a jump-table dispatcher could end at `mov pc,r0` with
its 0x81-entry table and case code split into large "functions" (`sub_08084500`, 1,188 bytes real). In both
cases a literal-reference scan against the ROM identified the true owner and end address.

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
| `sub_08061E34` | 32 → 44 | phantom `sub_08061E54` was three literal words (`0x02027A00`, `0x02021E90`, `0x0000127C`), not code; matched after 22 attempts |
| `sub_08084500` | 78 → 1,188 | 0x81-entry jump table + case code; phantoms `sub_0808454E` (36 B) and `sub_08084572` (1,074 B) deleted — 2,461 attempts recovered; still open, best 9,860 (82.4%) |
| `sub_0804006C` | 404 → 480 | mid-body split; phantom `sub_08040200` (76 B, 1,426 attempts) deleted; matched |
| `sub_080121F8` | 154 → 256 | unlisted tail through `bx r1` + pool word; still open, best 80 |
| `sub_080BF7C8` | 890 → 904 | phantom `sub_080BFB42` was its own `bx r1` + `Smsh` string; re-set aside as m4a ARM blobs |
| `sub_080BFDBE` | 594 → 610 | phantom `sub_080C0010` was its `bx r1` tail + literal; still open, no match yet |
| `sub_08085158` | 566 → 576 | own `pop`/`bx r1` epilogue + referenced literal `0x1508` |
| `sub_080B4DD4` | 138 → 352 | five referenced literal words + tail pool; matched after 45 attempts |
| `pad_08054910` | 4 → 488 | 4-byte prologue stub; entire body unlisted; matched after 4 attempts |
| `pad_08075E4C` | 4 → 336 | same; matched after 11 attempts |
| `pad_080B4F94` | 4 → 196 | same; matched after 54 attempts |
| `sub_08012A94` | 416 → 432 | **still unmatched** (see below) |
| `sub_08012C44` | 416 → 432 | **still unmatched** (see below) |

### Compiler-profile correction

`sub_080825EC` (192 → 212 bytes) plus its exact compiler range changed from
`-mno-thumb-interwork -O2 -fno-strength-reduce` to `-mthumb-interwork -O2 -fno-strength-reduce`
(12 of its 12 nearest matched neighbours use the latter). Body became byte-exact and it matched.

### Re-point fixes (neighbour starts on a literal-pool word)

Six pairs had a set-aside neighbour whose `vram` pointed at a pool word instead of the real prologue. For each,
the preceding function was extended through its literal and the neighbour was re-pointed to the real entry with
the same end address; `rom_offset`, target and symbol were re-derived, and the manifest layout/`set_aside` vram
updated. The neighbour's set-aside status was preserved unless the judge matched it.

| Preceding function | Re-pointed neighbour | Result |
|---|---|---|
| `sub_0805B808` 110 → 116 | `sub_0805B878` 460 → 388 @ `0x0805B87C` | both matched (agent / reused) |
| `sub_08021200` 136 → 140 | `sub_0802128A` 54 → 52 @ `0x0802128C` | both matched (`restored` + autopilot) |
| `sub_080653B0` 240 → 244 | `sub_080654A0` 392 → 388 @ `0x080654A4` | preceding matched; neighbour remains set aside with corrected bytes |
| `sub_0801E0DC` 76 → 80 | `sub_0801E12A` 54 → 52 @ `0x0801E12C` | both matched (`restored` + autopilot) |
| `sub_080B9F64` 84 → 88 | `sub_080B9FB8` 4 B deleted @ `0x080B9FB8` | both matched; score-200 note said all 38 body insns were exact and only the `0x08671BB0` pool word was excluded |
| `sub_08001614` 16 → 20 | `sub_08001626` 54 → 52 @ `0x08001628` | both matched; six agents had identified the 2 phantom leading bytes |

`sub_08061E34` / `sub_08061E54` is a variant of the same pattern: the neighbour was **pure pool data**, not a
misaligned function, so it was deleted rather than re-pointed. It had burned 1,180 attempts on a "literal-pool
leaf wall"; the real function matched on the first 22 attempts with the three words inside its own extent.
The same pure-data case was `sub_0803CE96` (12 B, 1,540 attempts, no function referenced the bytes) — deleted.

## Unresolved

`sub_08012A94` and `sub_08012C44` (twins, both 432 bytes, open, best 200) have all 203 instructions present
and differ by exactly one row: ROM `adds r3,r7,#0` vs agbcc `movs r3,#0` for `i = status` with `status = 0`.
Every C spelling, declaration permutation, type, volatile/register hint, flag profile, repair family and
`prove_chain` has been tried without moving off 200. Both are left open with no active claim so the token-free
local-source reuse path can still solve them — a single source variant emitting the register copy should fix both.

Set-aside verdicts are not always final: `sub_08094A40` was labelled a permanent commutative-AND coloring wall
and matched at score 0 after 1,144 attempts. The single-register ties listed below are plausible reuse targets,
but each already has 100–1,400 attempts behind it.

Several other open functions are genuine compiler walls (frameless-leaf LR frames, high-register coloring
ties, linker-level interworking veneers) with 100–500 attempts across many models. A set-aside audit of 347
entries found two further extent mislabels (`sub_08055840`, `sub_080A36AC`), both repaired above; the remaining
small entries are padding, literal fragments or BIOS stubs, and the larger ones are documented toolchain ceilings.
`sub_080654A0` (388 B, re-pointed to `0x080654A4`) is still set aside: its old verdict ("non-standard calling
convention, hand-written asm") was based on the pool-word halfwords now excluded from its extent, so the reason
is obsolete, but 1,140 attempts stayed between scores 17,805 and 18,005 and there is no preserved source — a
new agent would need to reconstruct a large function from scratch.

Two set-asides are **genuine not-C cases**, not extent defects. `sub_080BF7C8` (904 B) is `m4aSoundMain`
(magic `0x68736D53`) with two inline raw ARM opcode blobs entered via `add rX,pc,#4; bx rX`; none of the 3,959
matched sources uses inline asm, while the other m4a functions in the same region match without such blobs.
`sub_080BFDBE` (610 B) has a hand-crafted split prologue and a `pop {r3}; bx r3` return that agbcc cannot emit;
agents reached `not_c` after the extent fix. Leave both set aside — unlike the cases above, their verdicts are
about code shape, not wrong bytes.

Still open but close: `sub_080121F8` (256 B, best **80**, unclaimed), `sub_08085158` (576 B, best 560) and
`sub_08084500` (1,188 B, best 9,860 / 82.4% after reconstructing the switch case bodies from the operator note).

## Tool defects observed (not project-data problems)

Both of the following are defects in the app / repair library, not in any function's saved data. They surfaced as
"needs attention" flags and cost time before being diagnosed; neither damaged a source or a match.

### 1. Deep-proposal result key race (`KeyError: 'choices'`)

`decompnet/app/deep_proposals.py:252` reads `result['choices']`, but the worker writes `result['candidates']` and a
done-callback renames the key. Under DB-write contention the reader can win the race, get no `choices`, and fail
the whole deep-lane turn. `sub_08096F5C` was flagged because of this; its saved data is intact (it is a genuine
frameless-branchy-leaf wall with a semantically wrong score-325 best). Needs a library fix or a defensive `.get`.

### 2. `nested_guard_repairs` prefix collision (`ValueError: substring not found`)

`decomprepair/nested_guard_repairs.py:69` used `str.index(parts[1])` to locate the second `&&` operand. When that
operand is a prefix of the first (`mask != 0` inside `mask != 0xC0`, `r_arm != 0` inside `r_arm != 0x30`) `index`
returns 0, and the following `raw.rindex('&&', 0, cut)` raises. One crashing family aborts the whole proposal
batch, so deep-permuter produced **zero** candidates for `sub_0800E644` and `sub_0800D860`.

Resolved locally by changing `index` → `rindex` on that line (original backed up at
`backups/nested_guard_repairs.py.orig`); with the patched library both functions generate candidates again
(800 and 1,544). A source-side workaround — swapping the `&&` operands — also works, but the library fix covers
every function with the same shape. This needs the same fix upstream; release 1.0.14-rr.1 reports itself current.

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
   five app hangs during the session required a forced stop/restart (API timeouts, 75–93% CPU, 4–9 GB RSS,
   DB write lock held for minutes). The DB kept every match; the manifest needed one restart cycle to flush the
   most recent one. Relaunch with `setsid nohup decomp … &` so the app survives the agent harness's background
   shell tasks. Routine DB/manifest repairs need no restart at all.
