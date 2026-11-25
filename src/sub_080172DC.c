s32 sub_08014990(s32);
void sub_0801843C(void);
void sub_080C31E4(void *, void *, u32);
void sub_080008A0(void *, s32);

/* Step: refresh the entity's child objects, then move it up or down (velocity
 * +0x60000 or -0x60000 depending on its facing bit), reset its 5-frame delay
 * counter to 5, clear the script action byte and advance the script through
 * *0x08671BB0. The duplicated else branch mirrors the original source's null
 * check; folding it changes register allocation, so it stays. */
void sub_080172DC(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 sprite = *((s32 *) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *delay = work + 0x48;
  void **scriptCb;
  u8 zero;
  sub_0801843C();
  if (sub_08014990(sprite) > 0)
  {
    *((s32 *) (work + 0x10)) = 0x60000;
  }
  else
    if (self)
  {
    *((s32 *) (work + 0x10)) = (s32) 0xFFFA0000;
  }
  else
  {
    *((s32 *) (work + 0x10)) = (s32) 0xFFFA0000;
  }
  zero = 0;
  *((u16 *) (delay + 0x16)) = 5;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
  scriptCb = (void **) 0x08671BB0;
  sub_080C31E4(self + 0x18, self + 0x22, (s32) (*scriptCb));
}
