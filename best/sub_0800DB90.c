extern void sub_08005E80(s32);
extern void sub_0800EC20(s32);
extern void sub_0800ECF8(void);
extern void sub_0800EDAC(s32);
extern void sub_0800EF3C(u8);
extern void sub_0800F040(void);
extern void sub_0800F124(u8);
extern void sub_0800F1D8(u8, u8);
extern void sub_0800F3C8(u8, s32);
extern s32 sub_0800FF3C(u8);
extern void sub_0806D930(s32);
extern void sub_080C2E68(s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 D_02025368[];
extern u8 D_020278D0[];
extern const u8 D_060072B2[];
extern u32 D_08671BC0;
extern u32 D_08671BD0;
struct E_arg
{
  u8 _0[0x14];
  u32 f14;
  u8 f18;
  u8 f19;
  u8 _1A[6];
  s16 f22;
};

void sub_0800DB90(struct E_arg *arg0)
{
  u8 *b1 = D_02025368;
  u8 *b2 = D_020278D0;
  s8 *pidx = (s8 *) (b2 + 0x6A);
  s8 idx = *pidx;
  u8 t4;
  u8 sel;
  u32 tmp;
  u8 *e;

  t4 = *(u8 *) (b2 + (0x73 + (s8) (*(u8 *) (b2 + 0x6B + idx))) + (idx << 5));
  if ((u8) idx <= 2)
  {
    sub_08005E80(0x137);
    if (t4 != 0)
    {
      u8 *p = b1 + 0x384;
      p[t4]--;
      switch (*pidx)
      {
        case 0:
          sel = 0x306;
          break;

        case 1:
          sel = 0x307;
          break;

        case 2:
          sel = 0x308;
          break;

      }
      p[b1[sel]]++;
    }
    else
    {
      switch (*pidx)
      {
        case 0:
          (b1 + 0x384)[b1[0x306]]++;
          b2[0x42] = t4;
          break;

        case 1:
          (b1 + 0x384)[b1[0x307]]++;
          b2[0x43] = t4;
          break;

        case 2:
          (b1 + 0x384)[b1[0x308]]++;
          b2[0x44] = t4;
          break;

      }
    }
    sub_080C2E68((s32) (b1 + 0x2C4), (s32) b2, 0x48);
    sub_0806D930((s32) (b1 + 0x2C4));
  }
  else
  {
    if (idx == 3)
    {
      if (sub_0800FF3C(t4) != 0)
      {
        (b1 + 0x384)[t4]--;
        sub_08005E80(0x137);
      }
      else
      {
        sub_08005E80(0x140);
      }
      sub_0806D930((s32) (b1 + 0x2C4));
      sub_080C2E68((s32) b2, (s32) (b1 + 0x2C4), 0x48);
    }
  }
  sub_0800F124((u8) idx);
  if (idx == 1)
  {
    sub_0800F124(2);
  }
  else
  {
    if (idx == 2)
    {
      sub_0800F124(1);
    }
  }
  b2[0x69] = (b2[0x69] + 1) & 1;
  sub_0800F1D8((u8) idx, b2[0x69]);
  sub_0800F3C8(b2[0x69], 0);
  sub_0800F040();
  sub_0800ECF8();
  sub_0800EC20((s32) D_060072B2);
  t4 = b2[0xF3 + idx];
  if (t4 != 0)
  {
    sub_0800EDAC(0);
    sub_0800EF3C(*(u8 *) (b2 + (0x73 + (s8) (*(u8 *) (b2 + 0x6B + idx))) + (idx << 5)));
    e = (u8 *) arg0 + (arg0->f22 * 2);
    e[0x19] = 0;
    sub_080C31E4((u8 *) arg0 + 0x18, (u8 *) arg0 + 0x22, D_08671BC0);
    e = (u8 *) arg0 + (arg0->f22 * 2);
    e[0x19]++;
    tmp = *((u8 *) arg0 + (0x18 + (arg0->f22 * 2)));
    sub_080C31E0(arg0, *(u32 *) (arg0->f14 + (tmp << 2)));
  }
  else
  {
    if (*(u32 *) (b2 + 0x48) != 0)
    {
      sub_080C31E0(*(void **) (b2 + 0x48), *(u32 *) (*(u32 *) (b2 + 0x48) + 0x24));
    }
    *(u32 *) (b2 + 0x48) = t4;
    sub_0800EDAC(1);
    sub_0800EF3C(0xFF);
    e = (u8 *) arg0 + (arg0->f22 * 2);
    e[0x19] = t4;
    sub_080C31E8((u8 *) arg0 + 0x18, (u8 *) arg0 + 0x22, 1, D_08671BD0);
    e = (u8 *) arg0 + (arg0->f22 * 2);
    e[0x19]++;
    tmp = *((u8 *) arg0 + (0x18 + (arg0->f22 * 2)));
    sub_080C31E0(arg0, *(u32 *) (arg0->f14 + (tmp << 2)));
  }
}
