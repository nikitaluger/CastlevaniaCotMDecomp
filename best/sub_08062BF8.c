struct Arg0_62BF8
{
  u8 _0[0x18];
  u8 unk18;
  u8 _19[9];
  s16 unk22;
  u8 _24[0x14];
  u8 *unk38;
  u8 _3C[0x30];
  u8 *unk6C;
};
struct R4_62BF8
{
  u32 unk00;
  u32 unk04;
  u32 unk08;
  u32 unk0C;
  u8 _10[0x30];
  u32 unk40;
  u32 unk44;
  u32 unk48;
  u32 unk4C;
  u32 unk50;
  u32 unk54;
  u8 _58[0xC];
  u32 unk64;
  u32 unk68;
  u8 _6C[0x18];
  u32 unk84;
  u8 _88[0x3C];
  u32 unkC4;
};
struct S080E03A0
{
  u32 v0;
  u32 v4;
  u8 _8[0x50];
};
struct S02025FF0
{
  u8 _0[0x24];
  u32 f24;
  u8 _28[2];
  u16 f2A;
  u8 _2C[0x14C1];
  u8 f14ED;
  u8 _14EE[0x266];
  u32 f1754;
};
struct S02021E90
{
  u8 _0[0x146E];
  u16 f146E;
};
extern struct S080E03A0 D_080E03A0[];
extern struct S02025FF0 D_02025FF0;
extern struct S02021E90 D_02021E90;
extern u8 D_02025368[];
extern u32 D_08671BD0;
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806BA20(void *, void *, void *);
extern void sub_0806B104(void *, void *, void *);
extern s32 sub_0806B66C(void *, void *, void *, void *);
extern void sub_0806B820(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_08005E80(s32);
extern void sub_08086240(void *, s32);
extern void sub_0806B280(void *, void *, void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806E114(void *, s32, u32, u32);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806A884(void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
void sub_08062BF8(struct Arg0_62BF8 *arg0)
{
  struct R4_62BF8 *r8 = (struct R4_62BF8 *) (((u8 *) arg0->unk6C) + 4);
  u8 *r9 = arg0->unk38;
  struct R4_62BF8 *r4 = r8;
  u8 *r5 = D_02025368;
  int new_var;
  s32 cnt;
  s32 v;
  s32 cap;
  u16 w;
  if (sub_0806C4B4(r4, r4) != 0)
  {
    return;
  }
  sub_0806C5EC(arg0, r9, r4, r4);
  cnt = ++r4->unk54;
  if ((cnt > 6) && (r4->unk4C == 0))
  {
    r4->unk4C = 1;
  }
  sub_0806BA20(r9, r8, r4);
  v = r4->unk0C + D_080E03A0[r8->unk44].v0;
  r4->unk0C = v;
  cap = D_080E03A0[r8->unk44].v4;
  if (v > cap)
  {
    r4->unk0C = cap;
  }
  if (D_02025FF0.f24 != 0)
  {
    w = D_02025FF0.f2A;
  }
  else
  {
    w = D_02021E90.f146E;
  }
  r8->unk48 = (w >> 6) & 1;
  sub_0806B104(r9, r8, r4);
  if (sub_0806B66C(arg0, r9, r8, r4) == 0)
  {
    sub_0806B820(arg0, r9, r8, r4);
  }
  sub_0806AB04(arg0, r9, r8, r4);
  if (r8->unk40 == 1)
  {
    u8 v18;
    sub_08005E80(0x67);
    new_var = 0x22;
    r8->unk4C = 0;
    r8->unk50 = 0;
    r8->unk54 = 0;
    if ((D_02025FF0.f14ED == 0x35) && (((s32) D_02025FF0.f1754) <= 8))
    {
      D_02025FF0.f1754 = 9;
    }
    v18 = arg0->unk18;
    switch (v18)
    {
      case 0x0B:
        sub_08086240(r8, 9);
        ((u8 *) arg0)[((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + 0x19] = 0;
      {
        u32 *pt = &D_08671BD0;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 9, *pt);
      }
        r4->unk08 = 0;
        break;

      case 0x11:
        ((u8 *) arg0)[((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + 0x19] = 0;
      {
        u32 *pt = &D_08671BD0;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0x10, *pt);
      }
        r4->unk08 = 0;
        break;

      default:
        if (r8->unk68 == 0)
      {
        sub_0806B280(arg0, r9, r8, r4);
        ((u8 *) arg0)[((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + 0x19] = 0;
        {
          u32 *pt = &D_08671BD0;
          sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 7, *pt);
        }
      }
      else
      {
        u8 *p18;
        u8 *p22;
        u32 *pd;
        u16 rv;
        ((u8 *) arg0)[((*((s16 *) (((u8 *) arg0) + new_var))) * 2) + 0x19] = 0;
        pd = &D_08671BD0;
        p18 = ((u8 *) arg0) + 0x18;
        p22 = ((u8 *) arg0) + 0x22;
        rv = sub_08065CC8(arg0, r9, r8, r4);
        sub_080C31E8(p18, p22, rv, *pd);
        if (r4->unk08 != 0)
        {
          sub_0806E114(arg0, 3, r4->unk00, r4->unk04);
        }
        else
        {
          sub_0806E114(arg0, 9, r4->unk00, r4->unk04);
        }
      }
        break;

    }

  }
  else
  {
    s32 t;
    if (D_02025FF0.f24 != 0)
    {
      t = D_02025FF0.f2A & (*((u16 *) (r5 + 0x3C0)));
    }
    else
    {
      t = D_02021E90.f146E & (*((u16 *) (r5 + 0x3C0)));
    }
    if (t != 0)
    {
      if ((r8->unk84 != 0) && ((*((u8 *) (r5 + 0x3CA))) != 0))
      {
        u16 x;
        u32 zero;
        sub_08005E80(0x68);
        x = (*((u16 *) (r9 + 2))) ^ 0x10;
        zero = 0;
        *((u16 *) (r9 + 2)) = x;
        r8->unk64 = 0x11;
        r8->unk68 = 1;
        sub_0806A7AC(r9, r8, 0x1B);
        sub_0806E114(arg0, 6, r4->unk00, r4->unk04);
        ((u8 *) arg0)[((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + 0x19] = zero;
        {
          u32 *pt = &D_08671BD0;
          sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0x15, *pt);
        }
      }
    }
  }
  sub_0806A884(r9, r4);
  {
    s32 t2 = sub_0806BCD8(arg0, r9, r8, r4);
    r4->unkC4 = t2;
    if (((u16) t2) != 0)
    {
      ((u8 *) arg0)[((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + 0x19] = 0;
      {
        u32 *pt = &D_08671BD0;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, r4->unkC4, *pt);
      }
    }
  }
  sub_08003740(((u8 *) r8) + 0x28, r9);
  sub_0806C6B0(arg0, r9, r8, r4);
}

