extern void sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern s32 sub_08007B3C(void *, s32, s32);
extern s32 sub_08007B78(void *, s32, s32);
extern s32 sub_0806865C(void *, void *, void *, void *);
extern s32 sub_08068704(void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void sub_0806C49C(void *, void *);
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_0806DD94(void);
extern void sub_0806AB04(void *, void *, void *, void *);
extern s32 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, u16, void *);
struct G_25FF0
{
  u8 _0[0x24];
  u32 f24;
  u16 f28;
  u16 f2A;
  u8 _2C[0x14AC - 0x2C];
  u32 f14AC;
  u8 _14B0[0x14ED - 0x14B0];
  u8 f14ED;
  u8 _14EE[0x18A8 - 0x14EE];
  u8 f18A8;
};
struct G_25368
{
  u8 _0[0x3BC];
  u16 f3BC;
  u16 f3BE;
  u8 _3C0[2];
  u16 f3C2;
};
struct G_21E90
{
  u8 _0[0x146C];
  u16 f146C;
  u16 f146E;
};
extern struct G_25FF0 D_02025FF0;
extern struct G_25368 D_02025368;
extern struct G_21E90 D_02021E90;
extern u8 D_02023130[];
extern u8 D_084A67AC[];
extern u8 D_084A67C0[];
extern u8 D_084A67F4[];
extern void *D_08671BD0;
void sub_08067CCC(u8 *arg0)
{
  u8 *p = *((u8 **) (arg0 + 0x6C));
  u8 *r7 = p + 4;
  u8 *new_var3;
  void *r10 = *((void **) (arg0 + 0x38));
  u8 *r8 = r7;
  u8 *var_r4;
  struct G_25FF0 *new_var4;
  u8 *new_var5;
  s32 temp_r0_2;
  s32 temp_r1;
  u16 temp_r6;
  u8 temp_r6_3;
  s32 temp_r6_2;
  u16 temp_r0_3;
  volatile int new_var;
  u8 *new_var2;
  if (sub_0806C4B4(r8, r8) != 0)
  {
    return;
  }
  sub_0806C5EC(arg0, r10, r8, r8);
  if (D_02025FF0.f24 != 0)
  {
    if (!(D_02025FF0.f28 & D_02025368.f3BC))
    {
      goto block_7;
    }
    goto block_6;
  }
  if (D_02021E90.f146C & D_02025368.f3BC)
  {
    block_6:
    var_r4 = r7 + 0x28;

    sub_08003A6C(var_r4, 0, D_084A67C0);
    *((s32 *) (r7 + 0xB8)) = 0;
    *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = 0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x26, D_08671BD0);
    goto end;
  }
  block_7:
  if (D_02025FF0.f24 != 0)
  {
    if (!(D_02025FF0.f28 & D_02025368.f3BE))
    {
      goto block_20;
    }
    goto block_12;
  }

  if (!(D_02021E90.f146C & D_02025368.f3BE))
  {
    goto block_20;
  }
  block_12:
  if (D_02025FF0.f24 != 0)
  {
    new_var4 = &D_02025FF0;
    if (!((*new_var4).f2A & 0x80))
    {
      goto block_20;
    }
    goto block_16;
  }

  new_var3 = arg0 + 0x22;
  if (D_02021E90.f146E & 0x80)
  {
    new_var2 = D_02023130;
    new_var2 = new_var2 + ((*new_var4).f18A8 << 6);
    block_16:
    if (((!(0x1000 & sub_08007B3C(new_var2, *((s32 *) r7), (*((s32 *) (r7 + 4))) + 0x10000))) && (!sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), (*((s32 *) r7)) - (*((s32 *) (r7 + 0x38))), (*((s32 *) (r7 + 4))) + 0x10000))) && ((temp_r6 = 0x1000 & sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), (*((s32 *) r7)) + (*((s32 *) (r7 + 0x38))), (*((s32 *) (r7 - (-4)))) + 0x10000), temp_r6 == 0)))
    {
      *((s32 *) (r8 + 4)) += 0x20000;
      *((s32 *) (r7 + 0x40)) = temp_r6;
      *((s32 *) (r7 + 0x4C)) = 1;
      var_r4 = r7 + 0x28;
      sub_08003A6C(var_r4, 0, D_084A67F4);
      new_var5 = arg0 + 0x18;
      new_var = (u8) temp_r6;
      *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = new_var;
      sub_080C31E8(new_var5, arg0 + 0x22, 0x23, D_08671BD0);
    }
    else
    {
      goto block_20;
    }

  }
  else
  {
    block_20:
    temp_r0_2 = sub_0806865C(arg0, r10, r7, r8);

    var_r4 = r7 + 0x28;
    if (temp_r0_2 != 0)
    {
      goto end;
    }
    else
      if (sub_08068704(r10, r7, r8) != 0)
    {
      *((s32 *) (r7 + 0x68)) = 1;
      sub_08003A6C(var_r4, 0, D_084A67AC);
      *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = (u8) temp_r0_2;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x25, D_08671BD0);
    }
    else
    {
      if ((*new_var4).f24 != 0)
      {
        if (!(D_02025FF0.f28 & D_02025368.f3C2))
        {
          goto block_29;
        }
        goto block_28;
      }
      if (D_02021E90.f146C & D_02025368.f3C2)
      {
        if (1)
        {
        }
        block_28:
        sub_0806DD94();

      }
      else
      {
        block_29:
        if ((*new_var4).f24 != 0)
        {
          if (!(D_02025FF0.f2A & 0x40))
          {
            goto block_35;
          }
          goto block_33;
        }

        if (D_02021E90.f146E & 0x40)
        {
          block_33:
          if ((0x3F & sub_08007B78(D_02023130 + (D_02025FF0.f18A8 << 6), *((s32 *) r7), (*((s32 *) (r7 + 4))) + 0x10000)) == 0x15)
          {
            *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = 0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x2F, D_08671BD0);
          }
          else
          {
            goto block_35;
          }

        }
        else
        {
          block_35:
          if ((*new_var4).f24 != 0)
          {
            if (!(D_02025FF0.f2A & 0x40))
            {
              goto block_42;
            }
            goto block_39;
          }

          if (D_02021E90.f146E & 0x40)
          {
            block_39:
            if (((0x3F & sub_08007B78(D_02023130 + ((*new_var4).f18A8 << 6), *((s32 *) r7), (*((s32 *) (r7 + 4))) + 0x10000)) == 0x14) && ((temp_r1 = (*new_var4).f14AC, temp_r1 == 0)))
            {
              *(((u8 *) (((*((s16 *) new_var3)) * 2) + ((u32) arg0))) + 0x19) = (u8) temp_r1;
              sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x30, D_08671BD0);
            }
            else
            {
              goto block_42;
            }

          }
          else
          {
            block_42:
            *((u16 *) (r7 + 0xCC)) = 8 | (*((u16 *) (r7 + 0xCC)));

          }
        }
      }
    }
    var_r4 = r7 + 0x28;
  }
  end:
  sub_0806AB04(arg0, r10, r7, r8);

  if ((*((s32 *) (r7 + 0x40))) == 0)
  {
    ;
    if ((*((s32 *) (r7 + 0x4C))) == 0)
    {
      sub_08003A6C(var_r4, 0, D_084A67F4);
      *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = (u8) (*((s32 *) (r7 + 0x4C)));
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x23, D_08671BD0);
    }
  }
  sub_0806A884(r10, r8);
  temp_r6_3 = D_02025FF0.f14ED;
  if ((temp_r6_3 == 0) && ((*((u8 *) (arg0 + 0x18))) == 0x24))
  {
    sub_0806C49C(r10, r7);
    *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = temp_r6_3;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 4, D_08671BD0);
  }
  sub_08003740(var_r4, r10);
  *((s32 *) (r7 + 0xC4)) = (temp_r0_3 = (u16) sub_0806BCD8(arg0, r10, r7, r8));
  if (temp_r0_3 != 0)
  {
    sub_08003740(var_r4, r10);
    *(((u8 *) (((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0))) + 0x19) = 0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, *((s32 *) (r7 + 0xC4)), D_08671BD0);
  }
  sub_0806C6B0(arg0, r10, r7, r8);
}

