struct S_02025FF0_7B01C
{
  u8 _0[0x10];
  u32 f10;
  u8 _14[0x14ED - 0x14];
  u8 f14ED;
  u8 _14EE[0x173A - 0x14EE];
  u8 f173A;
  u8 _173B[0x18A8 - 0x173B];
  u8 f18A8;
  u8 _18A9[0x18C2 - 0x18A9];
  u16 f18C2;
};
extern struct S_02025FF0_7B01C D_02025FF0;
extern u8 D_02023130[];
extern u32 D_08671BB0;
extern s32 sub_0806D518(void *, void *, void *);
extern s32 sub_08007DD8(s32, s32);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E0(void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_0806D330(void *, void *);
static inline s32 sum2(s32 a, s32 b) { s32 r = b + a; return r; }
static inline u32 andOne(u16 f) { u32 m = 1; m &= f; return m; }
void sub_08084230(void *arg0)
{
  void *self = arg0;
  void *p6C = *((void **) (((u8 *) self) + 0x6C));
  u8 *p8 = ((u8 *) p6C) + 4;
  u8 *p38 = *((u8 **) (((u8 *) self) + 0x38));
  u8 *p4 = p8;
  s32 t;
  u32 flags;
  u8 idx;
  u32 addr;
  s32 val2;
  s16 i;
  u32 zero;
  u32 *pp;
  s32 sum;
  if (sub_0806D518(self, p38, p4) != 0) return;
  t = (*((s32 *) (p4 + 0xC))) + 0x2000;
  *((s32 *) (p4 + 0xC)) = t;
  if (t > 0x80000)
  {
    *((s32 *) (p4 + 0xC)) = 0x80000;
  }
  *((s32 *) (((u8 *) p6C) + 4)) += *((s32 *) (p4 + 8));
  sum = sum2(*((s32 *) (p4 + 4)), *((s32 *) (p4 + 0xC)));
  *((s32 *) (p4 + 4)) = sum;
  flags = andOne(*((u16 *) ((*((u8 **) (p4 + 0x2C))) + 0x14)));
  if (flags) goto label_0808429A;
  idx = D_02025FF0.f18A8;
  addr = (u32)D_02023130 + (idx << 6);
  val2 = sub_08007DD8(addr, *((s32 *) (((u8 *) p6C) + 4)));
  if ((val2 << 16) == 0) goto label_080842D2;
label_0808429A:
  sub_08003A6C(((u8 *) p6C) + 0x20, 0, (void *) 0x084FCB30);
  {
    u16 *p6 = (u16 *)(*((u8 **) (p4 + 0x2C)) + 6);
    zero = 0;
    *p6 = 6;
  }
  *((u16 *) ((*((u8 **) (p4 + 0x2C))) + 0x08)) = 6;
  sub_08005E80(0x88);
  i = *((s16 *) (((u8 *) self) + 0x22));
  *((u8 *) (((u8 *) self) + i * 2 + 0x19)) = zero;
  pp = &D_08671BB0;
  sub_080C31E4(((u8 *) self) + 0x18, ((u8 *) self) + 0x22, *pp);
label_080842D2:
  *((u16 *) p38) = D_02025FF0.f18C2;
  sub_08003740(p8 + 0x1C, p38);
  sub_0806D588(p38, p4);
  if ((D_02025FF0.f173A == 0x1C) || ((D_02025FF0.f14ED == 0) && (D_02025FF0.f10 != 0)))
  {
    sub_080C31E0(self, *((void **) (((u8 *) self) + 0x24)));
  }
  else
  {
    sub_0806D330(self, p38);
  }
}
