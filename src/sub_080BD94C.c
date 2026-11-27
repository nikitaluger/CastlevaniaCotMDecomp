extern s32 randomSignedOffset(s32);
extern s32 getAngleFromDelta(s32, s32);
extern s32 sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u32 gTrigFuncTable;
extern u32 gMainObjTimerCallbacks;

struct S_02025FF0 { u8 _0[0x174C]; s32 targetX; s32 targetY; };
extern struct S_02025FF0 gMainWorkspace;

/* Aims an entity at the target: computes the angle to it, derives two facing
 * values through a callback, resets a state field and advances the script. */
void sub_080BD94C(u8 *self)
{
  u8 *body = *(u8 **)(self + 0x3C);
  u8 *state = body + 0x48;
  s32 angle;
  u32 *pCallback;

  angle = getAngleFromDelta(gMainWorkspace.targetY - *(s32 *)(body + 0xC),
                       gMainWorkspace.targetX - *(s32 *)(body + 8));
  angle += randomSignedOffset(0x1000);
  *(s32 *)(state + 4) = angle;

  pCallback = &gTrigFuncTable;
  *(s32 *)(state + 8) = sub_080C31E0((void *)angle, (void *)*pCallback) >> 8;
  *(s32 *)(state + 0xC) = sub_080C31E0((void *)(*(s32 *)(state + 4) + 0x4000), (void *)*pCallback) >> 8;
  *(s32 *)(body + 0x48) = 0;

  *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
  {
    u32 *pStepCounter = &gMainObjTimerCallbacks;
    u8 *stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, (void *)*pStepCounter);
    {
      s16 stepIdx = *(s16 *)(self + 0x22);
      (*(u8 *)(stepIdx * 2 + self + 0x19))++;
      stepIdx = *(s16 *)(self + 0x22);
      stepBase += stepIdx * 2;
      {
        u8 stepByte = *stepBase;
        void **handlerTable = *(void ***)(self + 0x14);
        sub_080C31E0(self, handlerTable[stepByte]);
      }
    }
  }
}
