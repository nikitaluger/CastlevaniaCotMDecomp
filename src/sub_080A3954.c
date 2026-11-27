/* Run an entity's behavior script step: advance the script and, every sixth
 * frame, spawn a jittered object at a position derived from a coordinate table;
 * also clear state 0x5A and post its associated effect. */
extern s32 sub_0800583C(s32);
extern void sub_080A3E8C(void *, void *, void *, void *);
extern void sub_080A56A8(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 gTrigFuncPtr;
extern s32 gScriptStepCallbacks;
extern s32 D_08101C7C[];
void sub_080A3954(void *arg0)
{
  void *script;
  void *state;
  void *state34;
  void *state48;
  s32 stepCount;
  script = *((void **) (((u8 *) arg0) + 0x38));
  state = *((void **) (((u8 *) arg0) + 0x3C));
  state34 = ((u8 *) state) + 0x34;
  state48 = ((u8 *) state) + 0x48;
  sub_080A3E8C(script, state34, state, state48);
  stepCount = (*((s32 *) (((u8 *) state48) + 0x3C))) + 1;
  *((s32 *) (((u8 *) state48) + 0x3C)) = stepCount;
  if (stepCount == 6)
  {
    s32 *posTable;
    s32 centerX;
    s32 spread;
    s32 *randomFn;
    s32 tableIndex;
    s32 rand1;
    s32 rand2;
    s32 posX;
    *((s32 *) (((u8 *) state48) + 0x3C)) = 0;
    centerX = sub_0800583C(0x3000) + 0x4000;
    spread = (sub_0800583C(0x80000) + 0x280000) >> 8;
    randomFn = &gTrigFuncPtr;
    rand1 = sub_080C31E0(centerX + 0x4000, *randomFn);
    posTable = D_08101C7C;
    tableIndex = *((s32 *) (((u8 *) state48) + 0x38));
    posX = (*(posTable + (tableIndex * 2))) + ((rand1 >> 8) * spread);
    rand2 = sub_080C31E0(centerX, *randomFn);
    tableIndex = *((s32 *) (((u8 *) state48) + 0x38));
    sub_080A56A8(posX, (*((s32 *)((u8 *)D_08101C7C + 4 + (tableIndex << 3)))) + ((rand2 >> 8) * spread));
  }
  {
    s32 stateIndex = *((s16 *) (((u8 *) arg0) + 0x22));
    u32 stateOffset = stateIndex << 1;
    u32 entityBase = (u32)arg0;
    u8 *stateBytePtr = (u8 *)(stateOffset + entityBase);
    if (stateBytePtr[0x19] == 0x5A)
    {
      stateBytePtr[0x19] = 0;
      {
        s32 *effectFn = &gScriptStepCallbacks;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 2, *effectFn);
      }
    }
  }
}
