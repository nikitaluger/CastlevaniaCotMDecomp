extern u8 gMainWorkspace[];
extern u8 D_080E06C0[];
void sub_0806D588(void *, void *);
unsigned short _call_via_r1(void *, void *);
s32 sub_0806D35C(void *, void *, void *);
s32 sub_080C364C(s32, s32);
struct E_080E06C0
{
  s32 f0;
  s32 f4;
  s32 f8;
  s32 fC;
  s32 f10;
};
inline void *inline_fn(void *arg0)
{
  return arg0 + 0x1728;
}

inline void *inline_fn2(void *arg0, int arg1)
{
  return arg0 + arg1;
}

inline u8 inline_fn23(u8 **arg0)
{
  return (*arg0)[1];
}

inline void *inline_fn234(u8 *arg0)
{
  return inline_fn2(arg0, 0x2C);
}

inline int inline_fn2345(s32 arg0)
{
  return -arg0;
}

void sub_0806E380(void *arg0)
{
  u8 *s = (u8 *) arg0;
  u8 *r10;
  u8 *new_var8;
  u8 *new_var6;
  void *new_var17;
  void *new_var19;
  void *new_var25;
  u8 *r8;
  s32 new_var2;
  volatile int new_var;
  void *v38;
  u8 new_var21;
  u16 *new_var12;
  u8 *sp4;
  s32 ret;
  s32 i;
  int new_var14;
  u16 *new_var4;
  s32 *new_var27;
  u16 new_var26;
  s32 v;
  u8 *new_var13;
  u8 *new_var9;
  s32 cur;
  u8 **new_var11;
  s32 delta;
  s32 *new_var5;
  volatile unsigned int idx;
  s32 *new_var23;
  s32 *new_var16;
  void *new_var15;
  char new_var24;
  u8 **new_var10;
  struct E_080E06C0 *e;
  int new_var20;
  u16 *new_var7;
  void *new_var3;
  u8 *dst;
  u8 *src;
  u8 *new_var18;
  void *new_var28;
  u16 *new_var22;
  r10 = *((u8 **) (s + 0x6C));
  r8 = r10 + 4;
  v38 = *((void **) (s + 0x38));
  new_var4 = (u16 *) (r8 + 2);
  new_var14 = 2;
  new_var18 = s;
  new_var11 = &(*((u8 **) (new_var18 + 0x28)));
  new_var4 = (new_var7 = *new_var11);
  sp4 = *((u8 **) (new_var4 + 0x6C));
  idx = *((u16 *) ((*((u8 **) (new_var4 + 0x38))) + 2));
  sp4 = sp4 + 4;
  ret = sub_0806D35C(arg0, v38, r8);
  if ((ret == 1) || (ret == 4))
  {
    return;
  }
  new_var3 = v38;
  new_var5 = &new_var2;
  if ((ret == 2) || (ret == 3))
  {
    new_var2 = *((s32 *) (arg0 + 0x172C));
    for (i = 0x3F; i >= 0; i--)
    {
      *((u32 *) ((arg0 + 0x1518) + (i * 4))) = *((u32 *) inline_fn(arg0));
      *((u32 *) ((arg0 + 0x1618) + (i * 4))) = *((u32 *) (arg0 + 0x172C));
    }

    *((u32 *) (arg0 + 0x1718)) = 0;
    new_var13 = new_var18 + 0x7C;
    ;
    *((s32 *) r8) = *((s32 *) inline_fn(arg0));
    *(new_var23 = (s32 *) (r8 + 4)) = *new_var5;
    sub_0806D588(new_var3, r8);
    if ((*((u32 *) new_var13)) == 1)
    {
      *((s32 *) (arg0 + 0x1744)) = *((s32 *) r8);
      *((s32 *) ((new_var17 = arg0) + 0x174C)) = *((s32 *) (r8 + 4));
    }
    return;
  }
  new_var2 = *((s32 *) (arg0 - (-0x172C)));
  if ((*((u8 *) (0x173A + arg0))) == 0x2E)
  {
    goto fail;
  }
  s = sp4 + 0x130;
  ;
  e = (struct E_080E06C0 *) (D_080E06C0 - (-((idx * 10) * 2)));
  if (e->f0 == 0)
  {
    v = (*((s32 *) (arg0 + 0x1718))) - e->f4;
    v = v & 0x3F;
    new_var15 = (arg0 + 0x1518) + (v * 4);
    *((s32 *) (r10 + 4)) = *((s32 *) new_var15);
    new_var19 = arg0 + 0x1618;
    *((s32 *) (r8 + 4)) = *((s32 *) (new_var19 - (-(v * 4))));
  }
  else
    if (e->f0 == 1)
  {
    delta = e->fC;
    new_var = *new_var23;
    new_var26 = *((u16 *) (arg0 + 0x1738));
    if (new_var26 & 0x10)
    {
      if (new_var7)
      {
        delta = inline_fn2345(delta);
      }
      else
      {
        delta = inline_fn2345(delta);
      }
    }
    v = e->f10;
    cur += sub_080C364C(((*((s32 *) (arg0 + 0x1728))) + delta) - cur, (*e).f4);
    new_var27 = &cur;
    *(r10 + 4) = *new_var27;
    idx = new_var;
    cur = idx;
    cur += sub_080C364C((new_var2 - v) - cur, e->f4);
    *new_var23 = cur;
  }
  ;
  v = e->f8;
  new_var20 = 0x14ED;
  if (v == 1)
  {
    new_var21 = *((u8 *) (arg0 + new_var20));
    v = (*((s32 *) (0x1718 + arg0))) - (*e).f4;
    if (new_var21 != (*((u8 *) (r8 + 0x30))))
    {
      goto fail;
      do
      {
      }
      while (0);
    }
  }
  else
    if (v == new_var14)
  {
    if ((*((u8 *) (arg0 + 0x173A))) == 0x16)
    {
      goto ok;
      if (1)
      {
      }
    }
    if (new_var > (*((s32 *) (arg0 + 0x172C))))
    {
      goto ok;
    }
    if (new_var7 || e->f0)
    {
      goto fail;
    }
    else
    {
      goto fail;
    }
  }
  new_var12 = (u16 *) new_var3;
  ok:
  switch (*((u32 *) new_var13))
  {
    new_var24 = *((s32 *) r8);
    new_var10 = &(*((u8 **) s));
    new_var16 = (s32 *) inline_fn2(r10, 4);
    case 1:
      *((s32 *) (arg0 + 0x1744)) = new_var24;
      *((s32 *) inline_fn2(arg0, 0x1748)) = new_var;
      new_var6 = *((u8 **) inline_fn234(r8));
      dst = new_var6;
      src = *new_var10;
      (*((u8 **) inline_fn2(r8, 0x2C)))[1] = (*((u8 *) inline_fn2(arg0, 0x1510))) & inline_fn23(new_var10);
      (*((u8 **) inline_fn2(r8, 0x2C)))[2] = (*new_var10)[2];
      dst[3] = (*new_var10)[3];
      new_var4 = *((u8 **) inline_fn234(r8));
      *((u16 *) inline_fn2(*((u8 **) inline_fn2(r8, 0x2C)), 4)) = *((u16 *) inline_fn2(*new_var10, 4));
      *((u16 *) inline_fn2(*((u8 **) inline_fn234(r8)), 6)) = *((u16 *) inline_fn2(src, 6));
      new_var22 = (u16 *) inline_fn2(src, 8);
      *((u16 *) inline_fn2(*((u8 **) inline_fn2(r8, 0x2C)), 8)) = *new_var22;
      *((u16 *) inline_fn2(new_var4, 0xA)) = *((u16 *) inline_fn2(src, 0xA));
      *((u16 *) inline_fn2(*((u8 **) inline_fn234(r8)), 0xC)) = *((u16 *) inline_fn2(src, 0xC));
      *((u16 *) inline_fn2(*((u8 **) inline_fn2(r8, 0x2C)), 0xE)) = *((u16 *) inline_fn2(src, 0xE));
      new_var25 = inline_fn2(src, 0x16);
      *((u16 *) inline_fn2(*((u8 **) inline_fn2(r8, 0x2C)), 0x16)) = *((u16 *) new_var25);
      *((u16 *) new_var3) |= 0x4000;
      goto copy;

    case 0:

    case 2:

    case 4:
      *((u16 *) new_var3) |= 0xD000;
      goto copy;

    case 3:

    case 5:
      *new_var12 |= 0xC000;
      cur = *new_var16;
      break;
      sub_0806D588(new_var3, inline_fn2(r10, 4));

  }


  new_var8 = new_var18;
  copy:
  *((u32 *) inline_fn2(r8, 0x24)) = *((u32 *) inline_fn2(*((u8 **) inline_fn2(*((u8 **) inline_fn2(new_var8, 0x28)), 0x38)), 0x24));

  *((u16 *) inline_fn2(r8, 0x28)) = *((u16 *) inline_fn2((u8 *) new_var3, 0x28));
  *new_var7 = idx;
  return;
  new_var28 = *((void **) inline_fn2(new_var18, 0x24));
  fail:
  _call_via_r1(arg0, new_var28);

}
