s32 setEffectBehavior(void *, s32);
s32 sub_0809C5EC(void *);
s32 sub_080C31E4(void *, void *, s32);

/* While the state counter is above 9, clear the linked object's action step and
 * ramp its charge value at +0x24 by 0x80 until it reaches 0x1400, then put the
 * linked object into its release state and advance to the next handler. */
void sub_08099D64(void *arg0)
{
  u16 charge;
  int handlerTable;
  void *sub;
  sub = (*((s32 *) (((s8 *) arg0) + 0x3C))) + 0x48;
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) > 9U)
  {
    *((s8 *) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) sub) + 8)))) + 0x3C)))) + 0x28)))) + 1)) = 0;
    charge = *((u16 *) (((s8 *) sub) + 0x24));
    if (charge == 0x1400)
    {
      setEffectBehavior(*((void **) (((s8 *) sub) + 8)), 1);
      sub_0809C5EC(*((void **) (((s8 *) sub) + 8)));
      *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
      handlerTable = 0x08671BB0;
      sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) handlerTable));
      return;
    }
    *((u16 *) (((s8 *) sub) + 0x24)) = (u16) (charge + 0x80);
  }
}
