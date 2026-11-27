extern void sub_0808BB54(void);
extern void sub_080C31E0(void *arg, void *func);
extern void sub_080C31E8(void *scriptData, void *scriptIndex, s32 arg, s32 callback);
extern u32 gScriptStepCallbacks;

/* Script step: while the current step's flag bit 0 is clear, counts down the
 * byte at self+0x50 and drives two halfwords of the gfx state from it; when the
 * count reaches zero, clears the step flag, resets the effect and dispatches the
 * step's script callbacks. */
void sub_080AEB4C(u8 *self)
{
  s32 stepIdx;
  s32 zero;
  volatile u16 *gfxState;
  u8 *stepCount;
  u8 *stepData;
  u8 count;
  u32 *scriptCb;
  u16 color;
  stepIdx = *((s16 *) (self + 0x22));
  if (((*((u8 *) ((self + (stepIdx * 2)) + 0x19))) & 1) == 0)
  {
    (*(self + 0x50))--;
  }
  gfxState = (volatile u16 *) 0x03000830;
  zero = 0;
  color = zero + (0xFD << 6);
  gfxState[2] = color;
  stepCount = self + 0x50;
  count = *stepCount;
  gfxState[3] = count | ((0x10 - count) << 8);
  if ((*stepCount) == 0)
  {
    *((u8 *) (self + 0x4C)) = zero;
    sub_0808BB54();
    stepIdx = *((s16 *) (self + 0x22));
    *((u8 *) ((self + (stepIdx * 2)) + 0x19)) = zero;
    scriptCb = &gScriptStepCallbacks;
    stepData = self + 0x18;
    sub_080C31E8(stepData, self + 0x22, 0, *scriptCb);
    ((u8 *)(self + (*(s16 *)(self + 0x22)) * 2))[0x19]++;
    stepData += (*(s16 *)(self + 0x22)) * 2;
    sub_080C31E0(self, *(void **)(*(u8 **)(self + 0x14) + *(u8 *)stepData * 4));
  }
}
