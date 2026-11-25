extern void sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, s32);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_0806D2F8(void *, void *);
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 {
  u8 _0[0x10];
  u32 f10;
  u8 _1[0x14ED - 0x14];
  u8 f14ED;
  u8 _2[0x173A - 0x14EE];
  u8 f173A;
  u8 _3[0x18C2 - 0x173B];
  u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_080E4DEC[];
extern u8 D_084DE8B8[];
extern s32 D_08671BB0;
struct S_A0 {
  u8 _0[0x22];
  s16 f22;
  void *f24;
  void *f28;
  u8 _1[0x0C];
  void *f38;
  u8 _2[0x30];
  void *f6C;
};
struct S_6C { u8 _0[4]; s32 f4; };
struct S_7 {
  u8 _0[4];
  s32 f4;
  u8 _1[0x54 - 0x8];
  s32 f54;
};
struct S_38 { u16 f00; u16 f02; };
struct S_res {
  u8 _0[0x7C];
  s32 f7C;
  u8 _1[0x8C - 0x80];
  s32 f8C;
  u8 _2[0x9C - 0x90];
  s32 f9C;
};
struct Sub { u8 _0[0x19]; u8 f19; };
void sub_08079B48(struct S_A0 *arg0)
{
  struct S_6C *p6C;
  struct S_7 *p7;
  struct S_7 *p7b;
  struct S_38 *p38;
  struct S_res *p2;
  s32 *dst;
  s32 v1;
  s32 v2;
  s32 b;
  p6C = arg0->f6C;
  p7 = (struct S_7 *)((u8 *)p6C + 4);
  p38 = arg0->f38;
  p7b = p7;
  if (sub_0806D518(arg0, p38, p7) != 0) goto end;
  p38->f00 = D_02025FF0.f18C2;
  v1 = p7b->f54 - 1;
  p7b->f54 = v1;
  if ((v1 & 7) != 0) goto skip;
  p2 = sub_0806D2A0((s32)arg0->f28, 0x4C, 0xA, 0x12);
  if (p2 == NULL) goto skip;
  p2->f7C = p6C->f4;
  p2->f8C = p7b->f4;
  dst = &p2->f9C;
  b = D_080E4DEC[(p7b->f54 >> 3) & 7];
  *dst = (p38->f02 & 0x10) ? ((b + 0x80) & 0xFF) : b;
skip:
  v2 = p7->f54;
  p7 = (struct S_7 *)((u8 *)p7 + 0x1C);
  if (v2 == 0) {
    sub_08003A6C(p7, 0, (s32)D_084DE8B8);
    ((struct Sub *)((u8 *)arg0 + arg0->f22 * 2))->f19 = (u8)v2;
    {
      s32 *fn = &D_08671BB0;
      sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *fn);
    }
  }
  sub_08003740(p7, p38);
  sub_0806D588(p38, p7b);
  if ((D_02025FF0.f173A == 0x1C) ||
      ((D_02025FF0.f14ED == 0) && (D_02025FF0.f10 != 0))) {
    sub_080C31E0(arg0, (s32)arg0->f24);
  } else {
    sub_0806D2F8(arg0, p38);
  }
end:
  return;
}
