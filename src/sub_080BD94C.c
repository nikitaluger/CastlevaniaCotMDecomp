extern s32 sub_0800583C(s32);
extern s32 sub_08005910(s32, s32);
extern s32 sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u32 D_08671BFC;
extern u32 D_08671BB0;

struct S_02025FF0 { u8 _0[0x174C]; s32 targetX; s32 targetY; };
extern struct S_02025FF0 D_02025FF0;

/* Aims an entity at the target: computes the angle to it, derives two facing
 * values through a callback, resets a state field and advances the script. */
void sub_080BD94C(u8 *self)
{
  u8 *body = *(u8 **)(self + 0x3C);
  u8 *state = body + 0x48;
  s32 angle;
  u32 *pCallback;

  angle = sub_08005910(D_02025FF0.targetY - *(s32 *)(body + 0xC),
                       D_02025FF0.targetX - *(s32 *)(body + 8));
  angle += sub_0800583C(0x1000);
  *(s32 *)(state + 4) = angle;

  pCallback = &D_08671BFC;
  *(s32 *)(state + 8) = sub_080C31E0((void *)angle, (void *)*pCallback) >> 8;
  *(s32 *)(state + 0xC) = sub_080C31E0((void *)(*(s32 *)(state + 4) + 0x4000), (void *)*pCallback) >> 8;
  *(s32 *)(body + 0x48) = 0;

  *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
  {
    u32 *pStepCounter = &D_08671BB0;
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
