
struct S_02025FF0_78C6C
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
extern struct S_02025FF0_78C6C gMainWorkspace;
extern u8 D_02023130[];
extern s32 sub_0806D518(void *, void *, void *);
extern s32 sub_08007DD8(void *, s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_0806D330(void *, void *);

void sub_08078C6C(void *arg0)
{
  u8 *self = (u8 *)arg0;
  void *p6C = *((void **) (self + 0x6C));
  u8 *p8 = ((u8 *) p6C) + 4;
  u8 *p38 = *((u8 **) (self + 0x38));
  u8 *p4 = p8;
  s32 t;
  void *p;
  void *base;
  if (sub_0806D518(self, p38, p4) == 0)
  {
    t = (*((s32 *) (p4 + 0xC))) + 0x4000;
    *((s32 *) (p4 + 0xC)) = t;
    if (t > 0x80000)
    {
      *((s32 *) (p4 + 0xC)) = 0x80000;
    }
    *((s32 *) (((u8 *) p6C) + 4)) += *((s32 *) (p4 + 8));
    t = (*((s32 *) (p4 + 4))) + (*((s32 *) (p4 + 0xC)));
    *((s32 *) (p4 + 4)) = t;
    base = D_02023130 + (gMainWorkspace.f18A8 << 6);
    if ((u16)sub_08007DD8(base, *((s32 *) (((u8 *) p6C) + 4))) != 0)
    {
      sub_0808DBF8(*((s32 *) (((u8 *) p6C) + 4)), *((s32 *) (p4 + 4)), 0);
      goto block_9;
    }
    if (--(*((s32 *) (p4 + 0x54))) == 0)
    {
      p = sub_0806D2A0(*((s32 *) (self + 0x28)), 0x48, 0x0A, 0x12);
      if (p != 0)
      {
        *((s32 *) (((u8 *) p) + 0x7C)) = *((s32 *) (((u8 *) p6C) + 4));
        *((s32 *) (((u8 *) p) + 0x8C)) = *((s32 *) (p4 + 4));
      }
      *((s32 *) (p4 + 0x54)) = 4;
    }
    *((u16 *) p38) = gMainWorkspace.f18C2;
    sub_08003740(p8 + 0x1C, p38);
    sub_0806D588(p38, p4);
    if ((gMainWorkspace.f173A == 0x1C) || ((gMainWorkspace.f14ED == 0) && (gMainWorkspace.f10 != 0)))
    {
      block_9:
      sub_080C31E0(self, *((void **) (self + 0x24)));
    }
    else
    {
      sub_0806D330(self, p38);
    }
  }
}
