extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080A0340(void *, s32);
extern void sub_080A04B4(void);
extern void sub_080A04E0(void);
extern void *gMainObjTimerCallback;

/* Allocates and initializes an FX object for this entity and its component,
 * loads the visual resources, clears the current script step, posts a message
 * and advances to the next step. Bails out via sub_080C31E0 if the FX object or
 * the component could not be created.
 */
void sub_0809F014(u8 *self)
{
  u8 *fxObj;
  s16 stepIdx;
  u8 *stepBase;
  u8 *fx;
  u8 *component;
  s32 zero;

  fxObj = allocSpriteObject();
  if (fxObj == NULL)
  {
    sub_080C31E0(self, *((void **) (self + 0x24)));
    return;
  }
  *((u8 **) (self + 0x38)) = fxObj;
  allocWorkSlot(self, 0, 0x48, 0);
  if ((*((u32 *) (self + 0x3C))) == 0)
  {
    sub_080C31E0(self, *((void **) (self + 0x24)));
    return;
  }
  fx = fxObj;
  *((u8 *) (fx + 0x2A)) = 0xBF & *((u8 *) (fx + 0x2A));
  component = *((u8 **) (self + 0x3C));
  zero = 0;
  *((u16 *) (component + 0x1C)) = 0x4C;
  sub_080A04B4();
  sub_080A04E0();
  sub_080A0340(self, 0);
  (self + 0x70)[0] = zero;
  (self + 0x74)[0] = zero;
  *((u32 *) (self + 0x5C)) = 1;
  *((u16 *) (self + 0x02)) |= 0x1000;
  stepIdx = *((s16 *) (self + 0x22));
  self[(stepIdx * 2) + 0x19] = zero;
  {
    void **lit = &gMainObjTimerCallback;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *lit);
  }
  stepIdx = *((s16 *) (self + 0x22));
  self[(stepIdx * 2) + 0x19]++;
  stepIdx = *((s16 *) (self + 0x22));
  stepBase = stepBase + (stepIdx * 2);
  sub_080C31E0(self, *((void **) (*((u32 *) (self + 0x14)) + (stepBase[0] * 4))));
}
