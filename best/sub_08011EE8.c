extern u8 D_02027898[];
extern u8 D_02023130[];
extern u8 D_080CB278[];
s32 sub_08007D7C(u8 *, s32, s32);
void sub_08012704(s32, s32, s32, s32, void *);
void sub_08012870(s32, s32, s32, s32, s32, s32, void *);
s32 sub_08015850(s32, s32, s32, s32, s32, s32);
s32 sub_080159BC(s32, s32, s32, s32, s32, void *);
struct S11
{
  u8 _0[2];
  u16 f02;
  u16 f04;
  u16 f06;
  u32 f08;
  u32 f0C;
  s32 f10;
  s32 f14;
};
struct R11
{
  u16 f00;
  u16 pad;
  u32 f04;
  u32 f08;
};
struct Q11
{
  u16 f00;
  u16 pad;
  u32 f04;
  u32 f08;
  u32 f0C;
  u32 f10;
};
void sub_08011EE8(struct S11 *a, s32 arg1, s32 arg2, s32 arg3)
{
  int new_var3;
  struct R11 r;
  struct Q11 q;
  u16 flags = 0;
  s32 dy;
  s32 dx;
  int new_var4;
  s32 t;
  int new_var2;
  struct R11 *new_var;
  if ((a->f04 & 1) != 0)
  {
    a->f08 = a->f08 + a->f10;
    a->f0C = a->f0C + a->f14;
    a->f14 = a->f14 + arg1;
    goto END;
  }
  if (sub_08015850(a->f08, a->f0C, 0xFFFFFF00, 0x100, 0xFFFFFF00, 0x100) == 0)
  {
    goto END;
  }
  if (((((a->f04 & 2) == 0) && (a->f14 > (0 - 1))) && ((a->f02 & 4) != 0)) && ((a->f04 & 4) == 0))
  {
    goto STATIC_PATH;
  }
  new_var2 = 6;
  DYNAMIC_PATH:
  dx = a->f10;

  dy = a->f14 + arg1;
  new_var4 = 0xA;
  a->f14 = dy;
  new_var3 = 8;
  if ((a->f04 & 0x10) != 0)
  {
    if (sub_080159BC(a->f08, a->f0C, dx, dy, a->f06, &q) == 1)
    {
      dy += q.f08;
      dx += q.f04;
      t = q.f00;
      if (t & 1)
      {
        flags |= 0x100;
      }
      if (t & 6)
      {
        flags |= 0x200;
      }
      if (t & new_var3)
      {
        flags |= 0x400;
      }
    }
    if ((arg2 != 0) && (sub_080159BC(a->f08, a->f0C - arg2, dx, dy, 0x100 | a->f06, &q) == 1))
    {
      t = q.f00;
      if (t & 0xE)
      {
        dy += q.f08;
        dx += q.f04;
        if (t & 6)
        {
          flags |= 0x200;
        }
        if (t & new_var3)
        {
          flags |= 0x400;
        }
      }
    }
  }
  if ((((dy < 0) || (4 & (*((u16 *) (D_080CB278 + (((u32) (sub_08007D7C(D_02023130 + (D_02027898[0] << 6), a->f08, a->f0C) << 16)) >> 15)))))) || (4 & (*((u16 *) (D_080CB278 + (((u32) ((sub_08007D7C(D_02023130 + (D_02027898[0] << new_var2), a->f08 + dx, a->f0C) << 8) << 8)) >> 15)))))) || (a->f04 & 4))
  {
    sub_08012870(a->f08, a->f0C, dx, dy, arg2, new_var4, &r);
  }
  else
  {
    sub_08012870(a->f08, a->f0C, dx, dy, arg2, 0xE, &r);
  }
  new_var = &r;
  goto AFTER_PATHS;
  STATIC_PATH:
  a->f14 = 0;

  dx = a->f10;
  if ((a->f04 & 0x10) != 0)
  {
    if (sub_080159BC(a->f08, a->f0C, dx, 0, a->f06, &q) == 1)
    {
      dx += q.f04;
      t = q.f00;
      if (t & 1)
      {
        flags |= 0x100;
      }
      if (t & 6)
      {
        flags |= 0x200;
      }
      if (t & new_var3)
      {
        flags |= 0x400;
      }
    }
    if (((arg2 != 0) && (sub_080159BC(a->f08, a->f0C - arg2, dx, 0, 0x100 | a->f06, &q) == 1)) && (q.f00 & 6))
    {
      dx += q.f04;
      flags |= 0x200;
    }
  }
  sub_08012704(a->f08, a->f0C, dx, arg2, &r);
  if (((r.f00 & 2) != 0) && ((a->f04 & 8) == 0))
  {
    sub_08012870(r.f04, r.f08, (a->f08 + dx) - r.f04, 0, 0x1F0000, new_var4, new_var);
    a->f08 = r.f04;
    a->f0C = r.f08;
    flags = (a->f02 = r.f00);
    goto END;
  }
  flags |= r.f00;
  AFTER_PATHS:
  if (flags & 0x100)
  {
  }

  flags |= 4;
  a->f14 = 0;
  flags |= r.f00;
  a->f02 = flags;
  a->f08 = r.f04;
  a->f0C = r.f08;
  END:
  return;

}

