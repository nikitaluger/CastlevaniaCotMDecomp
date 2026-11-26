extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u8 D_02023130[];
extern u32 D_08671BD0[];
extern s32 sub_0806C4B4(void *a, void *b);
extern void sub_0806C5EC(void *a, void *b, void *c, void *d);
extern void *sub_0806D2A0(void *a, s32 b, s32 c, s32 d);
extern void sub_0806A7AC(void *a, void *b, s32 c);
extern void sub_0806C49C(void *a, void *b);
extern s32 sub_0806B3E8(void *a, void *b, void *c, void *d);
extern s32 sub_0806B820(void *a, void *b, void *c, void *d);
extern s32 sub_0806B104(void *a, void *b, void *c);
extern void sub_0806B280(void *a, void *b, void *c, void *d);
extern void sub_080C31E8(void *a, void *b, s32 c, u32 d);
extern s32 sub_0806B2C8(void *a, void *b, void *c, void *d);
extern s32 sub_0806BBA4(void *a, void *b, void *c);
extern void sub_0806AB04(void *a, void *b, void *c, void *d);
extern s16 sub_08007B78(void *a, s32 b, s32 c);
extern s16 sub_08007C40(void *a, s32 b, s32 c);
extern s32 sub_08003740(void *a, void *b);
extern void sub_0806A884(void *a, void *b);
extern u16 sub_0806BCD8(void *a, void *b, void *c, void *d);
extern void sub_0806C6B0(void *a, void *b, void *c, void *d);
void sub_08062F10(void *a)
{
  void *r4 = a;
  u8 *new_var;
  u8 *new_var2;
  u8 *r7 = *((u8 **) (((u8 *) r4) + 0x6C));
  u8 *r5 = r7 + 4;
  void *r8 = *((void **) (((u8 *) r4) + 0x38));
  u8 *r6 = r7 + 4;
  s32 r9 = sub_0806C4B4(r6, r6);
  if (r9)
  {
    return;
  }
  do { sub_0806C5EC(r4, r8, r6, r6); } while (0);
  {
    u32 *p84 = (u32 *) (r7 + 0x84);
    u32 v = (*p84) + 1;
    *p84 = v;
    if (gMainWorkspace[0x14ED] == 0x33)
    {
      if (v == 0x78)
      {
        u32 v7c = *((u32 *) (r6 + 0x7C));
        if ((v7c == 0) || (v7c == 2))
        {
          void *res = sub_0806D2A0(r4, 0x34, 0x0A, 0x12);
          if (res)
          {
            *((u16 *) (((u8 *) res) + 0x7C)) = r9;
          }
          sub_0806A7AC(r8, r6, 0x54);
          *((u32 *) (r6 + 0x7C)) = 3;
        }
      }
      if ((*((u32 *) ((r7 + 4) + 0x7C))) == 3)
      {
        *((u32 *) (gMainWorkspace + 0x14FC)) = 1;
      }
    }
    else
      if ((*((u32 *) (r6 + 0x7C))) == 3)
    {
      sub_0806C49C(r8, r6);
    }
    else
      if ((*((u32 *) (0x10 + gMainWorkspace))) != 0)
    {
      sub_0806A7AC(r8, r6, 0x7F);
      *((u32 *) (r6 + 0x7C)) = 1;
    }
    else
      if (v == 0x12C)
    {
      if ((*((u32 *) (r6 + 0x7C))) == 0)
      {
        sub_0806A7AC(r8, r6, 1);
        *((u32 *) (r6 + 0x7C)) = 1;
      }
    }
  }
  if (sub_0806B3E8(r4, r8, r7 + 4, r6))
  {
    goto lab_6312A;
  }
  if (sub_0806B820(r4, r8, r7 + 4, r6))
  {
    goto lab_6312A;
  }
  if (sub_0806B104(r8, r7 + 4, r6))
  {
    if ((*((u32 *) (r5 + 0x68))) == 0)
    {
      do { do { do { sub_0806B280(r4, r8, r5, r6); } while (0); } while (0); } while (0);
      {
        s16 idx = *((s16 *) (((u8 *) r4) + 0x22));
        ((u8 *) r4)[(idx * 2) + 0x19] = 0;
        sub_080C31E8(((u8 *) r4) + 0x18, ((u8 *) r4) + 0x22, 7, D_08671BD0[0]);
      }
    }
    else
    {
      *((u32 *) (r5 + 0x68)) = 1;
      if (gMainWorkspace[0x14ED] != 0x35)
      {
        do { sub_0806A7AC(r8, r5, 7); } while (0);
      }
      else
      {
        sub_0806A7AC(r8, r5, 0x55);
      }
      {
        s16 idx = *((s16 *) (((u8 *) r4) + 0x22));
        ((u8 *) r4)[(idx * 2) + 0x19] = 0;
        sub_080C31E8(((u8 *) r4) + 0x18, ((u8 *) r4) + 0x22, 6, D_08671BD0[0]);
      }
    }
    goto lab_6312A;
  }
  new_var2 = r5 + 0x40;
  new_var = gCameraState;
  if ((*((u32 *) (gMainWorkspace + 0x24))) != 0)
  {
    if (((*((u16 *) (gMainWorkspace + 0x2A))) & 0x80) == 0)
    {
      goto check_b2c8;
    }
  }
  else
    if (((*((u16 *) (new_var + 0x146E))) & 0x80) == 0)
  {
    goto check_b2c8;
  }
  sub_0806A7AC(r8, r5, 4);
  *((u32 *) (r6 + 8)) = 0;
  *((u32 *) new_var2) = 2;
  {
    s16 idx = *((s16 *) (((u8 *) r4) + 0x22));
    ((u8 *) r4)[(idx * 2) + 0x19] = 0;
    sub_080C31E8(((u8 *) r4) + 0x18, ((u8 *) r4) + 0x22, 8, D_08671BD0[0]);
  }
  goto lab_6312A;
  check_b2c8:
  if (!sub_0806B2C8(r4, r8, r5, r6))
  {
    if (!sub_0806BBA4(r4, r8, r5))
    {
      u16 *pcc = (u16 *) (r5 + 0xCC);
      *pcc |= 8;
    }
  }

  lab_6312A:
  sub_0806AB04(r4, r8, r5, r6);

  if (((*((u32 *) (r5 + 0x40))) == 0) && ((*((u32 *) (r5 + 0x4C))) == 0))
  {
    sub_0806A7AC(r8, r5, 0x10);
    {
      s16 idx = *((s16 *) (((u8 *) r4) + 0x22));
      ((u8 *) r4)[(idx * 2) + 0x19] = 0;
      sub_080C31E8(((u8 *) r4) + 0x18, ((u8 *) r4) + 0x22, 3, D_08671BD0[0]);
    }
  }
  {
    u8 *map = D_02023130 + (gMainWorkspace[0x18A8] * 0x40);
    s32 off = 0x10000;
    if (sub_08007B78(map, *((s32 *) (r6 + 0)), (*((s32 *) (r6 + 4))) + off) == 0)
    {
      *((u32 *) (r5 + 0x78)) = 1;
    }
    else
      if (sub_08007C40(map, (*((s32 *) (r6 + 0))) - (*((s32 *) (r5 + 0x38))), (*((s32 *) (r6 + 4))) + off) != 0)
      {
        *((u32 *) (r5 + 0x78)) = 1;
      }
      else
        if (sub_08007C40(map, (*((s32 *) (r6 + 0))) + (*((s32 *) (r5 + 0x38))), (*((s32 *) (r6 + 4))) + off) != 0)
        {
          *((u32 *) (r5 + 0x78)) = 1;
        }
  }
  if (((((u8 *) r4)[0x18] == 4) && ((*((u32 *) (r5 + 0x78))) != 0)) && ((*((u32 *) (r5 + 0x7C))) == 0))
  {
    sub_0806A7AC(r8, r5, 3);
    *((u32 *) (r5 + 0x7C)) = 2;
  }
  sub_0806A884(r8, r6);
  {
    void *p28 = r5 + 0x28;
    if (sub_08003740(p28, r8) == 0)
    {
      do { do { sub_0806C49C(r8, r5);
      sub_08003740(p28, r8); } while (0); } while (0);
    }
  }
  {
    u16 rv = sub_0806BCD8(r4, r8, r5, r6);
    *((u32 *) (r5 + 0xC4)) = rv;
    if (rv != 0)
    {
      void *p28 = r5 + 0x28;
      sub_08003740(p28, r8);
      {
        s16 idx = *((s16 *) (((u8 *) r4) + 0x22));
        ((u8 *) r4)[(idx * 2) + 0x19] = 0;
        sub_080C31E8(((u8 *) r4) + 0x18, ((u8 *) r4) + 0x22, rv, D_08671BD0[0]);
      }
    }
  }
  sub_0806C6B0(r4, r8, r5, r6);
}
