void sub_080C31E4(void *, void *, s32);
struct S_MMIO
{
  u8 _0[8];
  u16 w;
};
void sub_08005E28(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *p;
  u8 v = *((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19);
  s32 *lit;
  if (v == 0x10)
  {
    ((struct S_MMIO *) 0x03000830)->w = v;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    lit = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *lit);
  }
  else
  {
    ((struct S_MMIO *) 0x03000830)->w = *((u8 *) (0x080C98AF + (v - 1)));
  }
}

