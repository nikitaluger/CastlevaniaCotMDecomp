extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_0801131C(void *, void *, void *);
extern void sub_08011344(void *, void *, s32, s32);
extern s32 sub_08013C2C(void);
extern void sub_08014288(void *, void *, void *);
extern void sub_08014290(void);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u16 D_080CEC8C[];
extern u32 D_08671BB0[];
struct TBL2
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x20];
};
extern struct TBL2 D_080CBDD0[];
void sub_08033518(u8 *arg0)
{
  u8 *p;
  u8 *sprite;
  u8 *p34;
  void *res;
  u8 zero;
  s16 idx;
  s32 r22;
  u8 *a18;
  u16 *tbl2;
  sprite = sub_0800355C();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((u8 **) (arg0 + 0x38)) = sprite;
  sub_0800168C(arg0, 0, 0x4C, 0);
  if ((*((u8 **) (arg0 + 0x3C))) == NULL)
  {
    if (p)
    {
      goto fail;
    }
    else
    {
      goto fail;
    }
  }
  *((s32 *) (sprite + 0x1C)) = 0x8000000A;
  p = *((u8 **) (arg0 + 0x3C));
  p34 = p + 0x34;
  sub_08014288(arg0, p, &sub_08014290);
  zero = 0;
  *((u16 *) (p + 0x1C)) = 0x15;
  r22 = sub_08013C2C();
  *((u16 *) (p + 0x22)) = r22;
  if ((r22 << 16) < 0)
  {
    goto fail;
  }
  sub_0801131C(sprite, p34, (void *) 0x080CD4FC);
  sub_08011344(sprite, p34, 0x12, 0);
  tbl2 = D_080CEC8C;
  res = sub_08016190();
  *((void **) (p + 0x28)) = res;
  if (res == NULL)
  {
    goto fail;
  }
  goto success;
  fail:
  sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));

  return;
  success:
  *((u8 *) (((u8 *) res) + 1)) = zero;

  *((u8 *) ((*((u8 **) (p + 0x28))) + 2)) = 8;
  *((u8 *) ((*((u8 **) (p + 0x28))) + 3)) = 1;
  idx = *((s16 *) (p + 0x1C));
  *((u16 *) ((*((u8 **) (p + 0x28))) + 4)) = D_080CBDD0[idx].f4;
  *((u16 *) ((*((u8 **) (p + 0x28))) + 6)) = *((u16 *) (((u8 *) tbl2) + 0));
  *((u16 *) ((*((u8 **) (p + 0x28))) + 8)) = *((u16 *) (((u8 *) tbl2) + 2));
  *((u16 *) ((*((u8 **) (p + 0x28))) + 0xA)) = *((u16 *) (((u8 *) tbl2) + 4));
  *((u16 *) ((*((u8 **) (p + 0x28))) + 0xC)) = *((u16 *) (((u8 *) tbl2) + 6));
  idx = *((s16 *) (p + 0x1C));
  *((u16 *) ((*((u8 **) (p + 0x28))) + 0xE)) = D_080CBDD0[idx].f6;
  *((void **) ((*((u8 **) (p + 0x28))) + 0x10)) = sprite;
  {
    u8 *pt = D_02021E90;
    u8 *pb = D_02025FF0;
    u8 *base1;
    u8 *base2;
    u32 k;
    pb += 0x18A8;
    k = (((u32) (*pb)) + 1) * 0x40;
    base1 = pt + 0x1278;
    {
      s32 v = (*((s32 *) (base1 + k))) + 0x8000;
      {
        s32 mask = 0xFFFF0000;
        *((s32 *) (sprite + 0x14)) = (*((s32 *) (p + 8))) - (v & mask);
      }
    }
    k = (((u32) (*pb)) + 1) * 0x40;
    base2 = pt + 0x127C;
    {
      s32 v = (*((s32 *) (base2 + k))) + 0xFFFF8000;
      {
        s32 mask2 = 0xFFFF0000;
        *((s32 *) (sprite + 0x18)) = v & mask2;
        *((s32 *) (sprite + 0x18)) = (*((s32 *) (p + 0xC))) - (*((s32 *) (sprite + 0x18)));
      }
    }
  }
  *((u16 *) (arg0 + 2)) = (*((u16 *) (arg0 + 2))) | 0x1000;
  {
    u8 *q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    q[0x19] = zero;
  }
  {
    u32 *d = &D_08671BB0;
    a18 = arg0 + 0x18;
    sub_080C31E4(a18, arg0 + 0x22, *d);
  }
  {
    u8 *q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + arg0);
    q[0x19] = (u8) (q[0x19] + 1);
  }
  a18 += (*((s16 *) (arg0 + 0x22))) * 2;
  {
    u8 b = *a18;
    sub_080C31E0(arg0, *((void **) ((b * 4) + (*((u32 *) (arg0 + 0x14))))));
  }
}

