extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallback;

/* Spawn the entity's work object, set its initial animation frame and flags,
 * reset the current script step, then advance the script and dispatch the
 * handler chosen by the new command byte. */
void sub_0809F41C(u8 *self)
{
  s16 stepIndex;
  u8 *stepPtr;
  u8 *work;
  s32 zero;
  allocWorkSlot(self, 0, 0x98, 0);
  if ((*((u32 *) (self + 0x3C))) == 0)
  {
    sub_080C31E0(self, *((void **) (self + 0x24)));
    return;
  }
  work = *((u8 **) (self + 0x3C));
  zero = 0;
  *((u16 *) (work + 0x1C)) = 0x4C;
  (self + 0x6C)[0] = zero;
  *((u16 *) (self + 0x02)) |= 0x1000;
  stepIndex = *((s16 *) (self + 0x22));
  self[(stepIndex * 2) + 0x19] = zero;
  {
    void **scriptCb = &gMainObjTimerCallback;
    stepPtr = self + 0x18;
    sub_080C31E4(stepPtr, self + 0x22, *scriptCb);
  }
  stepIndex = *((s16 *) (self + 0x22));
  self[(stepIndex * 2) + 0x19]++;
  stepIndex = *((s16 *) (self + 0x22));
  stepPtr = stepPtr + (stepIndex * 2);
  sub_080C31E0(self, *((void **) ((*((u32 *) (self + 0x14))) + (stepPtr[0] * 4))));
}
