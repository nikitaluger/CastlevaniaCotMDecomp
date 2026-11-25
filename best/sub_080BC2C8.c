struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
struct E
{
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  s16 fE;
  u32 f10;
};
struct P
{
  u8 _0[8];
  u32 f8;
  u32 fC;
  u32 f10;
  u32 f14;
  u8 _18[4];
  u16 f1C;
  u8 _1E[4];
  u16 f22;
  u8 _24[4];
  struct E *f28;
};
struct BD
{
  u8 _0[8];
  u16 f8;
  u16 fA;
  u8 _C[0x1C];
};
extern struct BD D_080CBDD0[];
extern u16 D_08102F10[];
extern u16 D_08102F1C[];
extern u32 D_08671BB0;
void *sub_0800355C(void);
void sub_0800168C(void *, s32, s32, s32);
s32 sub_080057F8(void);
s32 sub_08005820(s32);
s32 sub_0800583C(s32);
void sub_0801131C(void *, s32, s32);
void sub_08011368(void *, s32, s32, s32);
long long sub_08013C2C(s32);
void sub_08014288(void *, void *, void *);
void *sub_08016190(void);
void sub_080BC73C(void *, void *, void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_08097DC8(void);
void sub_080BC2C8(u8 *arg0)
{
  u8 *r5 = arg0;
  u8 *new_var7;
  u8 *r6;
  struct P *r4;
  u8 *r7;
  u8 *r8;
  u8 *new_var;
  u8 *new_var5;
  u8 *r9;
  u8 *r10;
  u8 *r11;
  s16 idx;
  s32 r;
  int new_var2;
  u32 fn_ptr;
  unsigned long new_var4;
  int new_var3;
  u8 *arg22;
  u16 new_var6;
  u16 *tab;
  new_var7 = r5 + 0x24;
  r6 = sub_0800355C();
  if (r6 == 0)
  {
    sub_080C31E0(r5, *((u32 *) new_var7));
    return;
  }
  *((u32 *) (r5 + 0x38)) = (u32) r6;
  sub_0800168C(r5, 0, 0x48, 0);
  if ((*((u32 *) (r5 + 0x3C))) == 0)
  {
    sub_080C31E0(r5, *((u32 *) (r5 + 0x24)));
    return;
  }
  *((u32 *) (r6 + 0x1C)) = 0x80000009;
  r4 = (struct P *) (*((u32 *) (r5 + 0x3C)));
  r7 = ((u8 *) r4) + 0x34;
  sub_08014288(r5, r4, sub_08097DC8);
  r4->f1C = 0x68;
  r = sub_08013C2C((s16) r4->f1C);
  new_var3 = (r << 16) < 0;
  r4->f22 = (u16) r;
  if ((r << 16) < 0)
  {
    sub_080C31E0(r5, *((u32 *) new_var7));
    return;
  }
  idx = r4->f22;
  r = ((idx << 6) + 0x200) & 0xFC0;
  new_var6 = (u16) r;
  *((u16 *) r6) = new_var6;
  *((u16 *) r6) |= D_02025FF0.w;
  sub_0801131C(r6, (s32) r7, (s32) D_08102F10);
  sub_08011368(r6, (s32) r7, 0, 1);
  tab = D_08102F1C;
  r8 = sub_08016190();
  r4->f28 = (struct E *) r8;
  if (r8 == 0)
  {
    sub_080C31E0(r5, *((u32 *) (r5 + 0x24)));
    return;
  }
  r8[1] = 5;
  r8[2] = 8;
  r8[3] = 1;
  idx = r4->f1C;
  new_var = r5 + 0x7C;
  *((u16 *) (r8 + 4)) = D_080CBDD0[idx].f8;
  *((u16 *) (r8 + 6)) = tab[0];
  new_var2 = 2;
  *((u16 *) (r8 + 8)) = tab[1];
  new_var7 = r8;
  *((u16 *) (new_var7 + 10)) = tab[2];
  new_var4 = 0x8C;
  *((u16 *) (r8 + 12)) = tab[3];
  *((u16 *) (r8 + 14)) = D_080CBDD0[r4->f1C].fA;
  *((u32 *) (new_var7 + 16)) = (u32) r6;
  *((u32 *) (r5 + 0x6C)) = sub_08005820(0x200000) - (-0x100000);
  *((u32 *) new_var) = 0xFFFF & sub_080057F8();
  r = (*((s32 *) (r5 + 0x8C)) = sub_0800583C(0x180));
  if (r < 0)
  {
    r = r - 0x80;
  }
  else
  {
    r = r + 0x80;
  }
  *((s32 *) (r5 + new_var4)) = r;
  *((u32 *) (r5 + 0x5C)) = 1;
  *((u32 *) (r5 + 0x9C)) = 0;
  sub_080BC73C(r5, r6, r4);
  new_var5 = r5 + 2;
  *((u16 *) new_var5) |= 0x1000;
  idx = *((u16 *) (r5 + 0x22));
  *((u8 *) ((r5 + (idx * 2)) + 0x19)) = 0;
  fn_ptr = D_08671BB0;
  r7 = r5;
  r7 = r7 + 0x18;
  arg22 = r5 + 0x22;
  sub_080C31E4(r7, arg22, fn_ptr);
  *((u8 *) ((r5 + (idx * 2)) + 0x19)) += 1;
  r9 = r7 + (idx * new_var2);
  sub_080C31E0(r5, *((u32 *) ((*((u32 *) (r5 + 0x14))) + ((*((u8 *) r9)) * 4))));
}

