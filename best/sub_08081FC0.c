extern void sub_08003A6C(s32, s32, s32);
extern void sub_0808BBAC(s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern s32 sub_080C31E4(s32, s32, s32);
extern u8 D_084F52C8[];
extern u8 D_084F52F0[];
extern u8 D_08671BB0[];
void sub_08081FC0(u8 *arg0)
{
  u8 *r5 = arg0;
  u8 *r4 = (*((u8 **) (arg0 + 0x6C))) + 4;
  int new_var;
  u8 *r6 = *((u8 **) (arg0 + 0x38));
  s32 r8 = 0;
  *((s32 *) (r4 + 0x2C)) = r8;
  *((s32 *) (r4 + 0x30)) = r8;
  *((s32 *) (r4 + 0x34)) = r8;
  *((s32 *) (r4 + 0x38)) = r8;
  *((s32 *) (r4 + 0x3C)) = r8;
  *((s32 *) (r4 + 0x18)) = *((s32 *) (arg0 + 0x24));
  *((s32 *) (arg0 + 0x24)) = 0x0808449D;
  *((u16 *) (r6 + 0x04)) = 0x1000;
  *((u16 *) (r6 + 0x06)) = 0x1000;
  *((u32 *) (r6 + 0x24)) = (u32) D_084F52C8;
  sub_08003A6C((s32) ((*((u8 **) (arg0 + 0x6C))) + 0x20), 0, (s32) D_084F52F0);
  *((s32 *) (r6 + 0x14)) = 0x780000;
  *((s32 *) (r6 + 0x18)) = 0x500000;
  *((s32 *) (r4 + 0x10)) = 0x100;
  *((volatile u16 *) 0x05000000) = 0x4010;
  sub_0808BBAC(0x40, 1, 3);
  *((s32 *) (r4 + 0x14)) = 1;
  {
    s32 idx = *((s16 *) (arg0 + 0x22));
    u8 *p = (u8 *) ((idx * 2) + ((u32) arg0));
    *((u8 *) (p + 0x19)) = (u8) r8;
  }
  {
    void **fnaddr = &D_08671BB0;
    u8 *base = arg0 + 0x18;
    sub_080C31E4((s32) base, (s32) (arg0 + 0x22), *((s32 *) fnaddr));
  }
  {
    s32 idx = *((s16 *) (arg0 + 0x22));
    u8 *p = (u8 *) ((idx * 2) + ((u32) arg0));
    *((u8 *) (p + 0x19)) = (*((u8 *) (p + 0x19))) + 1;
  }
  {
    s32 idx = *((s16 *) (arg0 + 0x22));
    u8 *base = arg0 + 0x18;
    u8 b;
    new_var = 2;
    sub_080C31E0((s32) arg0, *((u32 *) ((*((u32 *) (arg0 + 0x14))) + ((*((u8 *) (((u32) base) + ((u32) (idx * new_var))))) * 4))));
  }
}

