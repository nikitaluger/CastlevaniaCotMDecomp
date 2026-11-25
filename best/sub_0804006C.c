extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_08016190(void);
extern s16 sub_08013C2C(s32);
extern void sub_0801131C(void *, s32, s32);
extern void sub_08011368(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08014290(void);
extern u8 D_02025FF0[];
extern u8 D_080CD400[];
extern u8 D_080CF460[];
extern u8 D_02021E90[];
extern u32 D_08671BB0;
struct Stride28
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x20];
};
extern struct Stride28 D_080CBDD0[];
inline void *inline_fn(u8 *arg0)
{
  return *((void **) (arg0 + 0x3C));
}

void sub_0804006C(void *arg0)
{
  u8 *r6 = (u8 *) arg0;
  u8 *new_var8;
  u8 *new_var3;
  void *r7;
  void *r5;
  u8 *r4;
  int new_var12;
  s16 t2;
  s16 v;
  void *t3;
  s32 x;
  u8 new_var4;
  s32 y;
  void *r8;
  u8 *r9;
  u8 byte0;
  u32 *new_var6;
  s32 off;
  u32 val;
  s16 *new_var13;
  s16 idx;
  u8 b;
  void **tbl;
  u8 *base18;
  void *new_var9;
  void *new_var11;
  u8 *new_var7;
  int new_var2;
  u16 *new_var5;
  int new_var;
  u8 *new_var14;
  r7 = sub_0800355C();
  if (r7 == 0)
  {
    goto fail;
  }
  *((void **) (r6 + 0x38)) = r7;
  sub_0800168C(r6, 0, 0x48, 0);
  if (inline_fn(r6) == 0)
  {
    goto fail;
  }
  *((s32 *) (((u8 *) r7) + 0x1C)) = 0x8000000A;
  r5 = inline_fn(r6);
  r4 = ((u8 *) r5) + 0x34;
  sub_08014288(r6, r5, (void *) sub_08014290);
  r8 = 0;
  *((s16 *) (((u8 *) r5) + 0x1C)) = 0x30;
  new_var13 = (s16 *) (((u8 *) r5) + 0x22);
  new_var11 = r5;
  *((s32 *) (((u8 *) new_var11) + 0x08)) = *((s32 *) (r6 + 0x4C));
  *((s32 *) (((u8 *) r5) + 0x0C)) = *((s32 *) (((u8 *) arg0) + 0x5C));
  *new_var13 = (t2 = sub_08013C2C(0x30));
  new_var4 = (u8) ((s32) r8);
  if (t2 < 0)
  {
    goto fail;
  }
  new_var2 = 0x18C2;
  v = *new_var13;
  new_var = 8;
  x = (v << 6) + 0x200;
  y = (t2 + new_var) << 12;
  x = x | y;
  *((s16 *) (((u8 *) r7) + 0)) = (s16) x;
  r9 = D_02025FF0;
  base18 = ((u8 *) new_var11) + 0x34;
  new_var2 = *((u16 *) (r9 + new_var2));
  *((s16 *) (((u8 *) r7) + 0)) = (s16) (x | new_var2);
  idx = *((s16 *) (((u8 *) new_var11) + 0x1C));
  sub_0801131C(r7, (s32) r4, (((idx << 1) + idx) << 2) + ((s32) D_080CD400));
  sub_08011368(r7, (s32) r4, 0x10, 0);
  r4 = (u8 *) D_080CF460;
  t3 = sub_08016190();
  *((void **) (((u8 *) new_var11) + 0x28)) = t3;
  if (t3 == 0)
  {
    goto fail;
  }
  *((u8 *) (((u8 *) t3) + 1)) = 5;
  *((u8 *) (((u8 *) t3) + 2)) = (u8) ((s32) r8);
  *((u8 *) (((u8 *) t3) + 3)) = new_var4;
  new_var5 = (u16 *) (((u8 *) new_var11) + 0x36);
  new_var7 = (u8 *) t3;
  idx = *((s16 *) (((u8 *) new_var11) + 0x1C));
  t3 = new_var7 + 0x0A;
  *((u16 *) (new_var7 + 4)) = D_080CBDD0[idx].f4;
  *((u16 *) (new_var7 + 6)) = *((u16 *) base18);
  *((u16 *) (new_var7 + 8)) = *new_var5;
  *((u16 *) t3) = *((u16 *) (((u8 *) new_var11) + 0x38));
  *((u16 *) (new_var7 + 0x0C)) = *((u16 *) (((u8 *) new_var11) + 0x3A));
  idx = *((s16 *) (((u8 *) new_var11) + 0x1C));
  *((u16 *) (new_var7 + 0x0E)) = D_080CBDD0[idx].f6;
  *((void **) (new_var7 + 0x10)) = r7;
  new_var6 = &val;
  r4 = r9 + 0x18A8;
  byte0 = *r4;
  off = (byte0 + 1) << 6;
  val = *((u32 *) ((D_02021E90 + 0x1278) + off));
  base18 = D_02021E90 + 0x127C;
  val = (*new_var6) + 0x8000;
  val = val & 0xFFFF0000;
  new_var14 = base18 + off;
  *((s32 *) (((u8 *) r7) + 0x14)) = (*((s32 *) (((u8 *) new_var11) + 0x08))) - ((s32) val);
  val = *((u32 *) new_var14);
  base18 = base18 + (idx * 2);
  new_var3 = r6 + 0x22;
  ;
  new_var9 = (void *) D_08671BB0;
  *((s32 *) (((u8 *) r7) + 0x18)) = (*((s32 *) (((u8 *) new_var11) + 0x0C))) - ((s32) (val & 0xFFFF0000));
  val = val + 0xFFFF8000;
  *((u16 *) (((u8 *) arg0) + 0x02)) = (*((u16 *) (new_var8 = r6 + 0x02))) | (new_var12 = 0x1000);
  idx = *((s16 *) new_var3);
  *((((u8 *) arg0) + (idx * 2)) + 0x19) = (u8) ((s32) r8);
  base18 = r6 + 0x18;
  sub_080C31E4(base18, new_var3, new_var9);
  (*((u8 *) (((idx * 2) + ((u8 *) arg0)) + 0x19)))++;
  idx = *((s16 *) new_var3);
  b = *base18;
  tbl = *((void ***) (r6 + 0x14));
  sub_080C31E0((u8 *) arg0, tbl[b]);
  fail:
  sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

  return;
  return;
  idx = *((s16 *) new_var3);
}

