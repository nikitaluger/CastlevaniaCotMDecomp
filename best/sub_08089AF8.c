extern u8 D_02021E90[];
extern u8 D_08507DD0[];
extern u32 D_08671BB0[];
extern void sub_08003A6C(void *, s32, void *);
extern void sub_08005E80(s32);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
void sub_08089AF8(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *p = *((u8 **) (self + 0x6C));
  u32 *new_var;
  void *r8 = *((void **) (self + 0x38));
  u8 *q = p + 4;
  u8 *r3;
  (*((s32 *) (q + 0x2C)))--;
  if (((*((s32 *) (q + 0x2C))) & 2) != 0)
  {
    r3 = p + 0x34;
    if ((*r3) <= 0x0F)
    {
      (*r3)++;
    }
    D_02021E90[0x1468] = 0x31;
    D_02021E90[0x146A] = 0x1F;
    if ((*((s32 *) (q + 0x2C))) == 1)
    {
      D_02021E90[0x1460] = 0;
      D_02021E90[0x1464] = 0;
      D_02021E90[0x1462] = 0xF8;
      D_02021E90[0x1466] = 0xA0;
    }
    else
    {
      D_02021E90[0x1460] = 0xA0 - (*r3);
      D_02021E90[0x1464] = 0;
      D_02021E90[0x1462] = (*r3) + 0xA0;
      D_02021E90[0x1466] = 0x80;
    }
  }
  else
  {
    D_02021E90[0x1460] = 0;
    D_02021E90[0x1464] = 0;
    D_02021E90[0x1462] = 0;
    D_02021E90[0x1466] = 0;
  }
  if ((*((s32 *) (q + 0x2C))) == 0)
  {
    sub_08003A6C(p + 0x1C, 0, D_08507DD0);
    sub_08005E80(0x19B);
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    new_var = D_08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, new_var[0]);
  }
  sub_0806D588(r8, q);
}
