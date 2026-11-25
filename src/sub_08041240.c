void sub_080113A8(void *, void *);
void sub_08011EE8(void *, s32, s32);
void sub_080415D4(s32, void *, void *, void *);
void sub_080C31E4(void *, void *, u32);
extern u32 D_08671BB0;

/* Entity update driven by the component's flags: marks the entity and its
 * child active, updates the track pose and plays an action. Flag 4 finishes
 * the entity (applies a pose, clears the step and posts a message); otherwise
 * flag 1 performs a one-time velocity/zeroing setup.
 */
void sub_08041240(void *self)
{
  void *fx = *((void **) (((u8 *) self) + 0x38));
  void *component = *((void **) (((u8 *) self) + 0x3C));
  void *track = ((u8 *) component) + 0x34;
  void *initDone = ((u8 *) component) + 0x48;
  u8 *activeFlag = ((u8 *) self) + 0x70;
  u32 zero = 0;
  u8 one = 1;
  *activeFlag = one;
  *((u8 *) ((*((u8 **) (((u8 *) self) + 0x30))) + 0x70)) = one;
  sub_080113A8(fx, track);
  sub_08011EE8(component, 0x16C1, 0);
  ;
  if ((*((u16 *) (((u8 *) component) + 2))) & 4)
  {
    u32 *pd;
    sub_080415D4(2, fx, component, track);
    *((u8 *) initDone) = (u8) zero;
    *activeFlag = (u8) zero;
    *((u8 *) ((*((u8 **) (((u8 *) self) + 0x30))) + 0x70)) = (u8) zero;
    *((u8 *) ((((u8 *) self) + ((*((s16 *) (((u8 *) self) + 0x22))) * 2)) + 0x19)) = (u8) zero;
    pd = &D_08671BB0;
    sub_080C31E4(((u8 *) self) + 0x18, ((u8 *) self) + 0x22, *pd);
  }
  else
    if ((*((u16 *) (((u8 *) component) + 2))) & 1)
  {
    if ((*((u8 *) initDone)) == 0)
    {
      *((u32 *) (((u8 *) component) + 0x14)) = 0;
      *((u32 *) (((u8 *) component) + 0x10)) = 0;
      *((u8 *) initDone) = 1;
    }
  }
}
