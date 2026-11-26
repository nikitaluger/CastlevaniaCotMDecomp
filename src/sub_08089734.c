extern void sub_08003A6C(void *a, s32 b, void *c);
extern void sub_08003740(void *a, void *b);
extern void sub_0806D588(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_080C31E0(void *a, void *b);
extern u32 gMainObjTimerCallback;
struct P38 { u16 f0; u8 _2[0x22]; u32 f24; };

/* Sets a flag and pointer on the FX object, spawns an effect from the child, seeds
 * the child's movement values, updates the FX position, then advances the script
 * step, posts a message and dispatches the next behavior handler.
 */
void sub_08089734(void *arg0)
{
  u8 *self = (u8 *)arg0;
  u8 *child = *(u8 **)(self + 0x6C);
  u8 *childData = child + 4;
  struct P38 *fx = *(struct P38 **)(self + 0x38);
  u8 *fxPos;
  s32 zero = 0;
  u32 *msgPtr;
  u8 *step;
  s16 stepIdx;

  fx->f0 |= 0x100;
  *(void **)((u8 *)fx + 0x24) = (void *)0x08500CA8;
  fxPos = child + 0x20;
  sub_08003A6C(fxPos, 0, (void *)0x08500D64);
  sub_08003740(fxPos, fx);
  *(u32 *)(child + 4) = 0x500000;
  *(u32 *)(childData + 4) = 0xC70000;
  sub_0806D588(fx, childData);
  *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
  msgPtr = &gMainObjTimerCallback;
  step = self + 0x18;
  sub_080C31E4(step, self + 0x22, *msgPtr);
  stepIdx = *(s16 *)(self + 0x22);
  (*(u8 *)(stepIdx * 2 + self + 0x19))++;
  stepIdx = *(s16 *)(self + 0x22);
  step += stepIdx * 2;
  {
    u8 handler = *step;
    void **handlerTable = *(void ***)(self + 0x14);
    sub_080C31E0(self, handlerTable[handler]);
  }
}
