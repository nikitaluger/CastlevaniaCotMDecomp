extern void *sub_08016190(void);
extern void sub_0806D2D0(void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_0806E6BC(void);
extern u8 D_02025FF0[];
extern void *D_08671BB0;
void sub_0806E248(void *arg0)
{
  u8 *r5;
  u8 *r7;
  u8 *r4;
  u8 *r6;
  void *tmp;
  u8 *base;
  u8 **new_var;
  u8 *swbase;
  s32 idx;
  s32 *new_var3;
  unsigned char new_var2;
  u8 *r4b;
  void **gp;
  u16 v;
  r5 = (u8 *) arg0;
  r7 = *((u8 **) (r5 + 0x6C));
  r4 = r7 + 4;
  r6 = *((u8 **) (r5 + 0x38));
  tmp = sub_08016190();
  *((void **) (r4 + 0x2C)) = tmp;
  if (tmp == 0)
  {
    sub_0806D2D0(r5);
    return;
  }
  {
    u8 *p = (u8 *)tmp;
    u32 zero = 0;
    p[1] = zero;
    p = *((u8 **) (r4 + 0x2C));
    p[2] = zero;
    p = *((u8 **) (r4 + 0x2C));
    p[3] = zero;
    new_var = &p;
    p = *((u8 **) (r4 + 0x2C));
    *((u16 *) ((*new_var) + 4)) = zero;
    p = *((u8 **) (r4 + 0x2C));
    {
      unsigned long long one = 1;
      *((u16 *) ((*new_var) + 6)) = (char) one;
      p = *((u8 **) (r4 + 0x2C));
      *((u16 *) (p + 8)) = one;
    }
    p = *((u8 **) (r4 + 0x2C));
    *((u16 *) ((*new_var) + 0xA)) = zero;
    p = *((u8 **) (r4 + 0x2C));
    *((u16 *) (p + 0xC)) = zero;
    p = *((u8 **) (r4 + 0x2C));
    *((u16 *) ((*new_var) + 0xE)) = zero;
    p = *((u8 **) (r4 + 0x2C));
    *((u32 *) ((*new_var) + 0x10)) = (u32) r6;
    *((u16 *) (p + 0x16)) = 0x1E;
  }
  *((u32 *) (r4 + 0x18)) = *((u32 *) (r5 + 0x24));
  *((void **) (r5 + 0x24)) = (void *) sub_0806E6BC;
  {
    u8 *b = D_02025FF0;
    u32 off1 = 0x1728;
    u32 off2 = 0x172C;
    *((u32 *) (r7 + 4)) = *((u32 *) (b + off1));
    *((u32 *) (r4 + 4)) = *((u32 *) (b + off2));
    *((u32 *) (r6 + 0x1C)) = 0x80000006;
    *((u32 *) (r4 + 0x30)) = *((u8 *) (b + 0x14ED));
    base = b;
  }
  new_var3 = (s32 *) (r5 + 0x7C);
  {
    s32 sw = *new_var3;
    swbase = base;
    if (((u32) sw) <= 5)
    {
      switch (sw)
      {
        case 1:
          v = *((u16 *) (swbase + 0x18C2));
          swbase = (u8 *) 0x4000;
          *((u16 *) r6) = (u16) (((u32) swbase) | v);
          break;
        case 0:
        case 2:
        case 4:
          v = *((u16 *) (swbase + 0x18C2));
          swbase = (u8 *) 0xD000;
          *((u16 *) r6) = (u16) (((u32) swbase) | v);
          break;
        case 3:
        case 5:
          v = *((u16 *) (swbase + 0x18C2));
          swbase = (u8 *) 0xC000;
          *((u16 *) r6) = (u16) (((u32) swbase) | v);
          break;
      }
    }
  }
  gp = (void **)0x08671BB0;
  idx = *((s16 *) (r5 + 0x22));
  *((u8 *) ((r5 + (idx * 2)) + 0x19)) = 0;
  r4b = r5 + 0x18;
  sub_080C31E4(r4b, r5 + 0x22, *gp);
  ;
  *((u8 *) ((r5 + ((*((s16 *) (r5 + 0x22))) * 2)) + 0x19)) += 1;
  idx = *((s16 *) (r5 + 0x22));
  new_var2 = idx;
  {
    u8 vv = *((u8 *) ((new_var2 * 2) + r4b));
    void **arr = *((void ***) (r5 + 0x14));
    sub_080C31E0(r5, arr[vv]);
  }
}
