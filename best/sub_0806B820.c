struct S_02025368
{
  u8 pad[0x3BE];
  u16 w3BE;
  u16 w3C0;
  u8 pad2[0xB];
  u8 b3CD;
};
struct S_02021E90
{
  u8 pad[0x146C];
  u16 w146C;
  u16 w146E;
};
struct S_02025FF0
{
  u8 pad[0x24];
  u32 flag;
  u16 w28;
  u16 w2A;
};
struct TableEntry
{
  u8 pad[0x18];
  u32 f18;
  u32 f1C;
  u8 pad2[0xC];
  u32 f28;
  u8 pad3[0x2C];
};
extern struct S_02025368 D_02025368;
extern struct S_02021E90 D_02021E90;
extern struct S_02025FF0 D_02025FF0;
extern struct TableEntry D_080E03A0[];
extern u32 D_08671BD0;
void sub_08005E80(u16);
void sub_0806A7AC(void *, void *, s32);
void *sub_0806D2A0(void *, s32, s32, s32);
void sub_0806DE0C(void);
void _call_via_r3(void *, void *, s32, u32);
s32 sub_0806B820(void *arg0, void *arg1, void *arg2, void *arg3)
{
  char new_var;
  s32 val_5C = *((s32 *) (((u8 *) arg2) + 0x5C));
  if (val_5C > 10)
  {
    return 0;
  }
  if (val_5C != 0)
  {
    goto path_93C;
  }
  if (D_02025FF0.flag != 0)
  {
    if ((D_02025FF0.w2A & 0x40) == 0)
    {
      goto path_93C;
    }
  }
  else
    if ((D_02021E90.w146E & 0x40) == 0)
  {
    goto path_93C;
  }
  if (D_02025FF0.flag != 0)
  {
    if ((D_02025FF0.w28 & D_02025368.w3C0) == 0)
    {
      goto path_93C;
    }
  }
  else
    if ((D_02021E90.w146C & D_02025368.w3C0) == 0)
  {
    goto path_93C;
  }
  if (D_02025368.b3CD == 0)
  {
    goto path_93C;
  }
  if ((*((u32 *) (((u8 *) arg2) + 0x4C))) == 0)
  {
    *((u32 *) (((u8 *) arg2) + 0x4C)) = 1;
  }
  *((u32 *) (((u8 *) arg2) + 0x58)) = 0x28;
  *((u32 *) (((u8 *) arg2) + 0x40)) = 0;
  {
    u32 idx = *((u32 *) (((u8 *) arg2) + 0x44));
    *((u32 *) (((u8 *) arg3) + 0x0C)) = D_080E03A0[*((u32 *) (((u8 *) arg2) + 0x44))].f28;
  }
  sub_0806A7AC(arg1, arg2, 0x0D);
  sub_08005E80(0x66);
  {
    s16 idx = *((s16 *) (((u8 *) arg0) + 0x22));
    new_var = 0x19;
    ((u8 *) arg0)[(idx * 2) + new_var] = 0;
  }
  _call_via_r3(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0x16, D_08671BD0);
  {
    void *r = sub_0806D2A0(arg0, 0x2D, 0x1E, 2);
    if (r != NULL)
    {
      *((u32 *) (((u8 *) r) + 0x7C)) = 2;
    }
  }
  {
    void *r = sub_0806D2A0(arg0, 0x2D, 0x1E, 2);
    if (r != NULL)
    {
      *((u32 *) (((u8 *) r) + 0x7C)) = 3;
    }
  }
  return 2;
  path_93C:
  if (D_02025FF0.flag != 0)
  {
    if ((D_02025FF0.w28 & D_02025368.w3BE) == 0)
    {
      return 0;
    }
  }
  else
    if ((D_02021E90.w146C & D_02025368.w3BE) == 0)
  {
    return 0;
  }

  {
    u32 v4C = *((u32 *) (((u8 *) arg2) + 0x4C));
    if (v4C == 0)
    {
      *((u32 *) (((u8 *) arg2) + 0x40)) = 0;
      {
        u32 idx = *((u32 *) (((u8 *) arg2) + 0x44));
        *((u32 *) (((u8 *) arg3) + 0x0C)) = D_080E03A0[*((u32 *) (((u8 *) arg2) + 0x44))].f18;
      }
      *((u32 *) (((u8 *) arg2) + 0x4C)) = 1;
      *((u32 *) (((u8 *) arg2) + 0x50)) = 0;
      sub_0806A7AC(arg1, arg2, 0x0A);
      sub_08005E80(0x65);
      sub_0806DE0C();
      {
        s16 idx = *((s16 *) (((u8 *) arg0) + 0x22));
        ((u8 *) arg0)[(idx * 2) + 0x19] = 0;
      }
      _call_via_r3(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 3, D_08671BD0);
      return 1;
    }
  }
  {
    u32 v4C = *((u32 *) (((u8 *) arg2) + 0x4C));
    if (v4C == 1)
    {
      if (D_02025368.pad[0] != 0)
      {
        u32 idx;
        *((u32 *) (((u8 *) arg3) + 0x0C)) = D_080E03A0[*((u32 *) (((u8 *) arg2) + 0x44))].f1C;
        *((u32 *) (((u8 *) arg2) + 0x4C)) = 2;
        *((u32 *) (((u8 *) arg2) + 0x50)) = 0;
        sub_0806A7AC(arg1, arg2, 0x0C);
        sub_08005E80(0x65);
        sub_0806DE0C();
        return 1;
      }
    }
  }
  return 0;
}

