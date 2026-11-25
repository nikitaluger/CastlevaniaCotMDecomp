extern void sub_08097F88(int, void *, void *, u32);
extern void sub_080BE550(u32, int, void *);
extern void sub_08098748(void *);
extern void sub_080BE8B8(u32);
extern void sub_080142C0(void *, u32);
extern void sub_08013AC4(void *);
extern void sub_08007E24(int);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E0(void *, u32);
extern int sub_08013B5C(void *, void *);
extern void sub_08098764(void *, void *, void *);
extern void sub_080BB828(void *, void *, void *);
extern void sub_08098338(int, void *);
extern void sub_08013C8C(void *, void *);
extern u8 D_086705B8;
extern u32 D_08671BB0[];
struct S8
{
  u32 w[5];
  u8 _p0[0x20 - 0x14];
  u32 f20;
  u8 _p1[0x34 - 0x24];
  u32 f34;
  u32 f38;
  u32 f3C;
};
struct S6
{
  u16 f00;
  u8 _p0[0x18 - 2];
  u32 f18;
  u8 _p1[0x22 - 0x1C];
  u16 f22;
  u8 _p2[0x28 - 0x24];
  u32 f28;
  u8 _p3[0x48 - 0x2C];
  struct S8 sub;
};
struct S9
{
  u16 f00;
};
struct S5
{
  u8 _p0[0x14];
  u32 f14;
  u8 arr[0x22 - 0x18];
  s16 f22;
  u8 _p1[0x38 - 0x24];
  u32 f38;
  u32 f3C;
  u8 _p2[0x4C - 0x40];
  u32 f4C;
};
void sub_080B9C28(struct S5 *r5)
{
  struct S9 *r9;
  struct S6 *r6;
  struct S8 *r8;
  void *r10;
  u32 tmp0;
  u32 tmp1;
  unsigned int r4;
  u32 *r7;
  u32 w;
  r9 = (struct S9 *) r5->f38;
  r6 = (struct S6 *) r5->f3C;
  r8 = &r6->sub;
  r10 = (void *) r5->f4C;
  tmp0 = r9->f00 & 0x0FFF;
  tmp1 = r6->f22 + 8;
  tmp1 <<= 12;
  tmp0 |= tmp1;
  r9->f00 = (u16) tmp0;
  sub_08097F88(3, r9, r6, r6->f28);
  if (r8->f3C != 1)
  {
    if (r6->f18 <= r8->f38)
    {
      r8->f3C = 1;
      sub_080BE550(r8->f20, 0, r6);
      sub_08098748(r10);
      sub_080BE8B8(r8->f34);
    }
  }
  sub_080142C0(r5, r6->f28);
  r4 = 0;
  r7 = (u32 *) r8;
  for (; r4 <= 4; r4++)
  {
    w = *(r7++);
    sub_080142C0(r5, w);
  }

  if (r6->f00 & 1)
  {
    u32 *r7p;
    u32 p;
    sub_08013AC4(r5);
    sub_08007E24(0xBC);
    *((u8 *) (((u8 *) r6->f28) + 1)) = 0;
    r4 = 0;
    r7p = (u32 *) r8;
    for (; r4 <= 4; r4++)
    {
      p = *(r7p++);
      ((u8 *) p)[1] = 0;
    }

    {
      u8 *b;
      b = (u8 *)((u32)(*(s16 *)((u8 *)r5 + 0x22)) * 2 + (u32)r5);
      *(u8 *)(b + 0x19) = 0;
    }
    sub_080C31E4((u8 *)r5 + 0x18, (u8 *)r5 + 0x22, D_08671BB0[0]);
    {
      u8 *b;
      b = (u8 *)((u32)(*(s16 *)((u8 *)r5 + 0x22)) * 2 + (u32)r5);
      *(u8 *)(b + 0x19) = *(u8 *)(b + 0x19) + 1;
    }
    {
      u8 *p18;
      u8 byte;
      s32 idx;
      idx = (s32)(s16)(*(s16 *)((u8 *)r5 + 0x22)) * 2;
      p18 = (u8 *)r5;
      p18 += 0x18;
      p18 += idx;
      byte = *p18;
      sub_080C31E0(r5, *(s32 *)((u32)(byte * 4) + *(u32 *)((u8 *)r5 + 0x14)));
    }
  }
  else
  {
    int res;
    res = sub_08013B5C(r9, r6);
    if (res == 0)
    {
      u8 *p18;
      u8 byte;
      s32 idx;
      r5->f14 = (u32) (&D_086705B8);
      r5->f22 = r5->f22 + 1;
      {
        u8 *b;
        b = (u8 *)((u32)(*(s16 *)((u8 *)r5 + 0x22)) * 2 + (u32)r5);
        *(u8 *)(b + 0x19) = *(u8 *)(b + 0x19) + 1;
      }
      idx = (s32)(s16)(*(s16 *)((u8 *)r5 + 0x22)) * 2;
      p18 = (u8 *)r5;
      p18 += 0x18;
      p18 += idx;
      byte = *p18;
      sub_080C31E0(r5, *(s32 *)((u32)(byte * 4) + *(u32 *)((u8 *)r5 + 0x14)));
      r5->f22 = r5->f22 - 1;
    }
    sub_08098764(r9, r6, r10);
    sub_080BB828(r10, r6, r8);
    sub_08098338(0x19, r9);
    sub_08013C8C(r5, r9);
  }
}
