#define Q19 (*(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x19))
struct Arg0
{
  u8 _0[4];
  s32 f04;
  u8 _8[0x1A];
  s16 f22;
  u8 _24[0x14];
  u32 f38;
  u32 f3C;
};
struct A6
{
  u8 _0[4];
  u16 f04;
  u16 f06;
};
struct P6
{
  u8 _0[8];
  u32 f08;
  u32 f0C;
  u32 f10;
  u8 _14[0x14];
  void *f28;
  u8 _2C[0x1C];
  u32 f48;
  u16 f4C;
  u8 f4E;
  u8 f4F;
};
extern s32 sub_08005820(s32);
extern void sub_08005E80(s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_0809C5C0(void *, s32, s32);
extern void sub_0809C840(void *, void *);
extern s32 sub_080C2F24(u8, s32);
extern s32 sub_080C31E0(u16, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void *D_08671BB0;
void sub_0809B05C(struct Arg0 *arg0)
{
  struct A6 *a;
  int new_var;
  struct P6 *p;
  u8 *p34;
  u8 *r7;
  u8 q;
  u32 flag;
  s32 *g;
  a = (struct A6 *) arg0->f38;
  p = (struct P6 *) arg0->f3C;
  p34 = ((u8 *) p) + 0x34;
  r7 = ((u8 *) p) + 0x48;
  if ((*((u8 *) (r7 + 7))) == 0)
  {
    sub_0809C840(arg0, a);
  }
  sub_080113A8(a, p34);
  new_var = 24;
  sub_0801165C(p, 0);
  *((u16 *) (r7 + 4)) = (*((u16 *) (r7 + 4))) + 0x217;
  g = (s32 *) 0x08671BFC;
  p->f0C = p->f48 - (sub_080C31E0(*((u16 *) (r7 + 4)), *g) << 3);
  *((u8 *) (r7 + 6)) = (*((u8 *) (r7 + 6))) + 1;
  if (((*((u8 *) (r7 + 6))) & 0x7F) == 0)
  {
    p->f10 = -p->f10;
  }
  q = Q19;
  flag = *((u8 *) (r7 + 7));
  if ((q == 0x2D) && (flag == 0))
  {
    a->f04 = 0xC0;
    a->f06 = 0xC0;
    sub_08011368(a, p34, 0, 0);
    goto lab_136;
  }
  if (Q19 > 0x2D)
  {
    if ((flag << new_var) != 0)
    {
      goto lab_13C;
    }
    a->f04 = a->f04 - 8;
    a->f06 = a->f06 - 8;
    if (((s16) a->f04) <= 0x80)
    {
      a->f04 = 0x100;
      a->f06 = 0x100;
      sub_08011368(a, p34, 4, 1);
      *((u8 *) (r7 + 7)) = 1;
      sub_08005E80(0x169);
    }
  }
  lab_136:
  if ((*((u8 *) (r7 + 7))) != 0)
  {
    lab_13C:
    if (sub_080C2F24(Q19, 0x18) == 0)
    {
      sub_0809C5C0(arg0, p->f08 + sub_08005820(0x40000), p->f0C + 0x200000);
    }

    if (sub_080C2F24(Q19, 0x18) == 0xC)
    {
      sub_0809C5C0(arg0, p->f08 - sub_08005820(0x40000), p->f0C + 0x200000);
    }
  }

  g = (s32 *) 0;
  arg0->f04 = arg0->f04 - 1;
  if (arg0->f04 == 0)
  {
    *((u8 *) (r7 + 7)) = 0;
    *((u8 *) (((u8 *) p->f28) + 1)) = 0;
    a->f04 = 0x80;
    a->f06 = 0x80;
    sub_08011368(a, p34, 0, 0);
    Q19 = 0;
    {
      void **fnaddr = &D_08671BB0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, (s32) (*fnaddr));
    }
  }
}

