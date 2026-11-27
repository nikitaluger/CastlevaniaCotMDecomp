extern void sub_080BB940(void *, void *);
extern void sub_080BE8D0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
void sub_080B9F64(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 *new_var;
  u8 *r4 = ((u8 *) (*((void **) (self + 0x3C)))) + 0x48;
  s32 v;
  sub_080BB940(*((void **) (self + 0x3C)), *((void **) (self + 0x4C)));
  v = (*((s32 *) (r4 + 0x40))) + 0xFFFFFD00;
  *((s32 *) (r4 + 0x40)) = v;
  if (v < 0)
  {
    v = (*((s32 *) (r4 + 0x40)) = 0);
  }
  sub_080BE8D0(*((s32 *) (r4 + 0x34)), *((s32 *) (r4 + 0x40)));
  v = *((s32 *) (r4 + 0x40));
  new_var = &v;
  if (v == 0)
  {
    s32 *lit;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = *new_var;
    lit = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *lit);
  }
}

void sub_080BA0F4(void *arg0);
