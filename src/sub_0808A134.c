extern void sub_08003A6C(void *a, s32 b, void *c);
extern void sub_08003740(void *a, void *b);
extern void sub_0806D588(void *a, void *b);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern u8 D_08506368[];
extern u8 D_08506434[];
extern u32 D_08671BB0;

struct P38 { u8 _0[2]; u16 f2; u8 _4[0x20]; u32 f24; };

/* Sets a flag and pointer on the FX object, spawns an effect from the child, seeds
 * the child's movement values, updates the FX position, then advances the script
 * step, posts a message and dispatches the next behavior handler.
 */
void sub_0808A134(void *arg0)
{
  u8 *self = (u8 *)arg0;
  u8 *child = *(u8 **)(self + 0x6C);
  u8 *childData = child + 4;
  struct P38 *fx = *(struct P38 **)(self + 0x38);
  u8 *fxPos;
  s32 zero = 0;

  fx->f2 |= 0x10;
  *(void **)((u8 *)fx + 0x24) = D_08506368;
  fxPos = child + 0x20;
  sub_08003A6C(fxPos, 0, D_08506434);
  sub_08003740(fxPos, fx);
  *(u32 *)(child + 4) = 0x00C00000;
  *(u32 *)(childData + 4) = 0x00800000;
  sub_0806D588(fx, childData);
  *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
  {
    u32 *msgPtr = &D_08671BB0;
    u8 *step = self + 0x18;
    sub_080C31E4(step, self + 0x22, *msgPtr);
    {
      s16 stepIdx = *(s16 *)(self + 0x22);
      (*(u8 *)(stepIdx * 2 + self + 0x19))++;
      stepIdx = *(s16 *)(self + 0x22);
      step += stepIdx * 2;
      {
        u8 handler = *step;
        void **handlerTable = *(void ***)(self + 0x14);
        sub_080C31E0(self, handlerTable[handler]);
      }
    }
  }
}
