extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s32 scalePercentSaturate16(s32, s32);
extern void startEffectTimer(void *, s32, s32);
extern void _call_via_r2(void *, void *, s32);
extern void _call_via_r1(void *, void *);
extern void releaseActorEffectParts(void);
extern u8 gGameStatus[];

/* Global flags: bit 0 at +0x1510 selects the spawned part's variant. */
struct ChildEffectPermutedWorkspace { u8 _0[0x1510]; u8 variantBit; };
extern struct ChildEffectPermutedWorkspace gMainWorkspace;

extern u8 gActorChildEffectPermutationTable[];
extern u8 gActorChildEffectParamTable[];
extern u32 gMainObjTimerCallbacks;

/* Turn a variant byte into an offset into the 0x20-stride parameter table. */
inline u32 paramRowOffset(u8 *table, u32 index) { return ((u32) table[index]) << 5; }
static inline u8 lowBit(u8 b) { u32 m = 1; m &= b; return (u8)m; }

/* Spawn the table-permuted child effect of an actor's current script step.
 * Allocate a render part, choose its 0x20-byte parameter row through the
 * variant permutation table, fill the part and effect state from that row and
 * gGameStatus, install releaseActorEffectParts as the actor's update handler,
 * start the child's script timer, then advance to and dispatch the next script
 * command. If the part pool is exhausted, only clean up the old child. */
void spawnActorChildEffectPermuted(void *arg0)
{
  void *header; void *state; void *sprite; s32 partAddr; u32 rowOffset; u8 *params;
  u8 *part; u8 *gameStatus; u8 *permTable; s32 zero; s32 stepOffset;
  header = *((void **) (((u8 *) arg0) + 0x6C));
  state = ((u8 *) header) + 4;
  sprite = *((void **) (((u8 *) arg0) + 0x38));
  gameStatus = gGameStatus;
  partAddr = (s32) allocEffectPart();
  *((s32 *) (((u8 *) state) + 0x2C)) = partAddr;
  if (partAddr == 0) { cleanupFailedEffectSpawn(arg0); return; }
  *((s32 *) (((u8 *) state) + 0x30)) = 0;
  *((s32 *) (((u8 *) state) + 0x34)) = 0;
  *((s32 *) (((u8 *) state) + 0x38)) = 0;
  *((s32 *) (((u8 *) state) + 0x3C)) = 0;
  permTable = gActorChildEffectPermutationTable;
  rowOffset = *((u32 *) (((u8 *) arg0) + 0x9C));
  rowOffset = paramRowOffset(permTable, rowOffset);
  params = gActorChildEffectParamTable + rowOffset;
  part = (u8 *) partAddr;
  part[1] = lowBit(gMainWorkspace.variantBit);
  *((u8 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 2)) = 2;
  *((u8 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 3)) = 8;
  zero = 0;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 4)) = gameStatus[0x304] | zero;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 6)) = *((u16 *) params);
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 8)) = *((u16 *) (params + 2));
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 0x0A)) = 0;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 0x0C)) = 0;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 0x0E)) = (u16) scalePercentSaturate16(*((u16 *) (gameStatus + 0x2E2)), *((u16 *) (params + 4)));
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 0x16)) = 5;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 0x18)) = *((u16 *) (params + 0x1C));
  *((void **) (((u8 *) (*((void **) (((u8 *) state) + 0x2C)))) + 0x10)) = sprite;
  *((void **) (((u8 *) state) + 0x18)) = *((void **) (((u8 *) arg0) + 0x24));
  *((void **) (((u8 *) arg0) + 0x24)) = (void *) releaseActorEffectParts;
  *((s32 *) (((u8 *) sprite) + 0x24)) = *((s32 *) (params + 0x08));
  startEffectTimer(((u8 *) header) + 0x20, 0, *((s32 *) (params + 0x0C)));
  *((s32 *) (((u8 *) sprite) + 0x14)) = *((s32 *) (params + 0x10));
  *((s32 *) (((u8 *) sprite) + 0x18)) = 0xFFD00000;
  *((s32 *) (((u8 *) state) + 0x08)) = *((s32 *) (params + 0x14));
  *((s32 *) (((u8 *) state) + 0x0C)) = *((s32 *) (params + 0x18));
  {
    u8 *stepDesc = (u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + ((u32) arg0));
    stepDesc[0x19] = (u8) zero;
  }
  {
    u32 *callbackSlot = &gMainObjTimerCallbacks;
    u8 *scriptPtr = ((u8 *) arg0) + 0x18;
    _call_via_r2(scriptPtr, ((u8 *) arg0) + 0x22, *callbackSlot);
    {
      u8 *stepDesc2;
      stepOffset = *((s16 *) (((u8 *) arg0) + 0x22));
      stepOffset = stepOffset * 2;
      stepDesc2 = (u8 *) (((u32) stepOffset) + ((u32) arg0));
      stepDesc2[0x19] = (u8) (stepDesc2[0x19] + 1);
    }
    {
      u8 *stepPtr = scriptPtr + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2);
      u8 cmdId = *stepPtr;
      u32 cmdTable = *((u32 *) (((u8 *) arg0) + 0x14));
      u32 handler = *((u32 *) (cmdTable + (cmdId * 4)));
      _call_via_r1(arg0, (void *) handler);
    }
  }
}
