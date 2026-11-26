extern void sub_0806A7AC(u8 *, u8 *, s32);
extern void sub_0806A884(u8 *, u8 *);
extern s32 sub_08003740(u8 *, s32);
struct S_02025FF0
{
  u8 _0[0x24];
  u32 f24;
  u16 f28;
  u16 f2A;
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90
{
  u8 _0[0x146C];
  u16 f146C;
  u16 f146E;
};
extern struct S_02021E90 gCameraState;
void sub_0806A5C8(u8 *arg0)
{
  struct S_02021E90 *new_var;
  u8 *r1;
  u8 *r4;
  u8 *r5;
  u8 *r6;
  s32 v;
  r1 = *((u8 **) (arg0 + 0x6C));
  r4 = r1 + 4;
  r6 = *((u8 **) (arg0 + 0x38));
  r5 = r4;
  *((u32 *) (r6 + 0x14)) = 0xF0 << 15;
  *((u32 *) (r6 + 0x18)) = 0xC8 << 15;
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f28 & 0x100))
    {
    }
    else
    {
      goto b1;
    }
  }
  else
    if (gCameraState.f146C & 0x100)
  {
    b1:
    v = (*((s32 *) (r4 + 0x1C))) + 1;

    *((s32 *) (r4 + 0x1C)) = v;
    if (v > 0x34)
    {
      *((s32 *) (r4 + 0x1C)) = 0;
    }
    sub_0806A7AC(r6, r4, *((s32 *) (r4 + 0x1C)));
  }
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f28 & 0x200))
    {
    }
    else
    {
      goto b2;
    }
  }
  else
    if (gCameraState.f146C & 0x200)
  {
    b2:
    v = (*((s32 *) (r4 + 0x1C))) - 1;

    *((s32 *) (r4 + 0x1C)) = v;
    if (v < 0)
    {
      *((s32 *) (r4 + 0x1C)) = 0x34;
    }
    sub_0806A7AC(r6, r4, *((s32 *) (r4 + 0x1C)));
  }
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f28 & 1))
    {
    }
    else
    {
      goto b3;
    }
  }
  else
    if (gCameraState.f146C & 1)
  {
    b3:
    sub_0806A7AC(r6, r4, *((s32 *) (r4 + 0x1C)));

  }
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f2A & 0x10))
    {
    }
    else
    {
      goto b4;
    }
  }
  else
    if (gCameraState.f146E & 0x10)
  {
    b4:
    *((u32 *) r5) += 0x80 << 10;

  }
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f2A & 0x20))
    {
    }
    else
    {
      goto b5;
    }
  }
  else
  {
    new_var = &gCameraState;
    if ((*new_var).f146E & 0x20)
    {
      b5:
      *((u32 *) r5) += 0xFFFE0000;

    }
  }
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f2A & 0x40))
    {
    }
    else
    {
      goto b6;
    }
  }
  else
    if (gCameraState.f146E & 0x40)
  {
    b6:
    *((u32 *) (r5 + 4)) += 0xFFFE0000;

  }
  if (gMainWorkspace.f24 != 0)
  {
    if (!(gMainWorkspace.f2A & 0x80))
    {
    }
    else
    {
      goto b7;
    }
  }
  else
    if ((*new_var).f146E & 0x80)
  {
    b7:
    *((u32 *) (r5 + 4)) += 0x80 << 10;

  }
  sub_0806A884(r6, r5);
  sub_08003740(r4 + 0x28, (s32) r6);
}

