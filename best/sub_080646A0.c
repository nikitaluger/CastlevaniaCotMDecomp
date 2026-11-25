extern s32 sub_0806C4B4(u8 *, u8 *);
extern void sub_0806C5EC(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806E114(u8 *, s32, s32, s32);
extern s32 sub_08007B78(s32, s32, s32);
extern void sub_0806AB04(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806A800(u8 *, s32);
extern void sub_0806A7AC(u8 *, u8 *, s32);
extern void sub_0806A884(u8 *, u8 *);
extern s32 sub_08003740(u8 *, u8 *);
extern u16 sub_08065CC8(u8 *, u8 *, u8 *, u8 *);
extern u16 sub_0806BCD8(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806C6B0(u8 *, u8 *, u8 *, u8 *);
extern void sub_080C31E8(u8 *, u8 *, u16, s32);
extern u8 D_02023130[];
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
};
extern struct S_02025FF0 D_02025FF0;
extern s32 D_080DEA88[];
extern s32 D_080E03A0[];
extern s32 D_08671BD0[];
inline s32 *inline_fn(u8 *arg0, int arg1)
{
  return (s32 *) (arg0 + arg1);
}

inline u8 *inline_fn2(u8 *arg0)
{
  return arg0 + 4;
}

void sub_080646A0(u8 *arg0)
{
  u8 *r4;
  u8 *r9;
  u8 *new_var4;
  s32 *new_var;
  u8 *r10;
  u8 *sp0;
  u8 *new_var3;
  s32 v5;
  int new_var7;
  int new_var6;
  s32 v;
  s32 a;
  s32 b;
  u16 w;
  s32 *new_var2;
  u8 *new_var5;
  s32 sp;
  r4 = *((u8 **) (arg0 + 0x6C));
  r9 = inline_fn2(r4);
  new_var7 = 0xE4 * 2;
  r10 = *((u8 **) (arg0 + 0x38));
  if (sub_0806C4B4(inline_fn2(r4), inline_fn2(r4)) != 0)
  {
    goto end;
  }
  sub_0806C5EC(arg0, r10, inline_fn2(r4), inline_fn2(r4));
  v = *inline_fn(r9, 0x6C);
  *inline_fn(inline_fn2(r4), 0x6C) = (v = v + 1);
  new_var2 = inline_fn(r9, 4);
  if ((v & 3) == 0)
  {
    sub_0806E114(arg0, 7, *inline_fn(r4, 4), *inline_fn(inline_fn2(r4), 4));
  }
  new_var = D_080DEA88;
  v5 = 1;
  a = ((s32) D_02023130) + (((D_02025FF0.f18A8 << 3) << 1) << 2);
  b = (*new_var2) + 0x10000;
  v = sub_08007B78(a, *inline_fn(r4, 4), b) & 0x3F;
  if (((*((u16 *) (r10 + 2))) & 0x10) != 0)
  {
    if ((v == 3) || (v == 0x13))
    {
      v5 = 4;
    }
  }
  else
    if ((v == 2) || (v == 0x12))
  {
    v5 = 4;
  }
  {
    s32 off = *inline_fn(r9, 8);
    volatile unsigned long tbl = *inline_fn(((u8 *) D_080E03A0) + 0x4C, 0x58 * (*inline_fn(inline_fn2(r4), 0x44)));
    if (((off + 1) - 1) >= 0)
    {
      off = tbl;
      off = off + (off * v5);
      *inline_fn(inline_fn2(r4), 8) = off;
      if (off < 0)
      {
        *inline_fn(inline_fn2(r4), 8) = 0;
      }
    }
    else
    {
      off = v5;
      off = off + ((-tbl) * off);
      *((s32 *) (inline_fn2(r4) + 8)) = off;
      if (off > 0)
      {
        *((s32 *) (inline_fn2(r4) + 8)) = 0;
      }
    }
  }
  sub_0806AB04(arg0, r10, inline_fn2(r4), inline_fn2(r4));
  v = sub_08007B78(a, *((s32 *) (r9 + 0)), b) & 0x3F;
  if (v)
  {
  }
  if (((*((u16 *) (r10 + 2))) & 0x10) != 0)
  {
    if ((v == 2) || (v == 0x12))
    {
      *((s32 *) (inline_fn2(r4) - (-0x30))) = *((s32 *) (((u8 *) new_var) + (0xEE * 2)));
      sub_0806A800(inline_fn2(r4), 0x17);
    }
    else
    {
      *((s32 *) (inline_fn2(r4) + 0x30)) = *((s32 *) (((u8 *) new_var) + new_var7));
      sub_0806A800(inline_fn2(r4), 0x16);
    }
  }
  else
  {
    new_var4 = ((u8 *) D_080DEA88) + (0xE4 * 2);
    if ((v == 3) || (v == 0x13))
    {
      *((s32 *) (inline_fn2(r4) + 0x30)) = *((s32 *) (((u8 *) new_var) + (0xEE * 2)));
      sub_0806A800(inline_fn2(r4), 0x17);
    }
    else
    {
      new_var5 = new_var4;
      *((s32 *) ((r4 + (new_var6 = 4)) + 0x30)) = *((s32 *) new_var5);
      sub_0806A800(r4 + new_var6, 0x16);
    }
  }
  if ((*((s32 *) ((r4 + new_var6) + 0x40))) == 0)
  {
    sub_0806A7AC(r10, r4 + new_var6, 0x10);
    *((u8 *) ((arg0 + (2 * (*((s16 *) (arg0 + 0x22))))) + 0x19)) = 0;
    {
      s32 *fp = (s32 *) 0x08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *fp);
    }
  }
  sub_0806A884(r10, r4 + new_var6);
  sp0 = r9 + 0x28;
  sp = sub_08003740(sp0, r10);
  if (sp == 0)
  {
    *((s32 *) ((r4 + new_var6) + 8)) = sp;
    sub_0806E114(arg0, new_var6, *((s32 *) (r4 + new_var6)), *((s32 *) ((r4 + new_var6) + new_var6)));
    *((u8 *) ((arg0 + (2 * (*((s16 *) (arg0 + 0x22))))) + 0x19)) = 0;
    {
      s32 *fp = (s32 *) 0x08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, sub_08065CC8(arg0, r10, r4 + new_var6, r4 + new_var6), *fp);
    }
  }
  w = (*((s32 *) (r9 + 0xC4)) = sub_0806BCD8(arg0, r10, r9, r9));
  if (w != 0)
  {
    sub_08003740(sp0, r10);
    *((u8 *) ((arg0 + (2 * (*((s16 *) (arg0 + 0x22))))) + 0x19)) = 0;
    new_var3 = arg0;
    {
      s32 *fp = (s32 *) 0x08671BD0;
      sub_080C31E8(arg0 + 0x18, new_var3 + 0x22, *((u32 *) ((r4 + new_var6) + 0xC4)), *fp);
    }
  }
  sub_0806C6B0(arg0, r10, r4 + new_var6, r4 + new_var6);
  end:
  return;

}
