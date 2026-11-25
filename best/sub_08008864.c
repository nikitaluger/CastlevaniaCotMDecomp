void sub_08005E80(s32);
void sub_08006044(s32, s32, s32, s32, void *);
void sub_080060C4(s32, s32, s32, s32);
unsigned char sub_08007FE0(void);
void sub_080102F0(s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_080C0384(void);
extern u8 D_02021E90[];
extern u32 D_08671BD0;
struct S_03000830
{
  u8 pad[4];
  u16 f4;
  u16 f6;
};
extern struct S_03000830 D_03000830;
void sub_08008864(void *arg0)
{
  u16 *new_var2;
  u32 *p3C;
  u32 r4;
  u32 v;
  u32 r0;
  u32 r3;
  u16 w2;
  u16 w3;
  u32 r6;
  u32 r4v;
  u8 *r4b;
  u8 b;
  u8 r5;
  s32 s;
  u8 *q1;
  u8 *q2;
  u8 *q3;
  u32 *pp1;
  int new_var;
  u32 *pp2;
  u32 *pp3;
  u8 *r7;
  r7 = (u8 *) arg0;
  p3C = *((u32 **) (r7 + 0x3C));
  r4 = p3C[2];
  if (r4 != 0)
  {
    goto loc_88CC;
  }
  v = *((u32 *) (r7 + 0x04));
  v = v + 1;
  *((u32 *) (r7 + 0x04)) = v;
  if (v > 0x1A4)
  {
    goto loc_8892;
  }
  q1 = D_02021E90;
  q1 = q1 + 0x146C;
  w2 = *((u16 *) q1);
  r0 = 0x08;
  r0 &= w2;
  if (r0 != 0)
  {
    goto loc_8892;
  }
  goto loc_89DC;
  loc_8892:
  sub_080060C4(0, 0x0C, 0, (s32) sub_080C0384);

  s = *((s16 *) (r7 + 0x22));
  s = s << 1;
  *((u8 *) ((((u32) s) + ((u32) r7)) + 0x19)) = (u8) r4;
  pp1 = &D_08671BD0;
  sub_080C31E8(r7 + 0x18, r7 + 0x22, 0x05, *pp1);
  goto loc_89DC;
  loc_88CC:
  r3 = *((u32 *) (r7 + 0x4C));

  q2 = D_02021E90;
  q2 = q2 + 0x1470;
  new_var2 = &(*((u16 *) q2));
  w2 = *new_var2;
  r0 = w2 & 0x30;
  if (r0 == 0x30)
  {
    goto loc_8904;
  }
  r0 = 0x20;
  r0 = w2 & r0;
  if (r0 == 0)
  {
    goto loc_88EA;
  }
  *((u32 *) (r7 + 0x4C)) = 0;
  loc_88EA:
  w2 = *new_var2;

  r0 = 0x10;
  r0 &= w2;
  if (r0 == 0)
  {
    goto loc_88F8;
  }
  *((u32 *) (r7 + 0x4C)) = 1;
  loc_88F8:
  r0 = *((u32 *) (r7 + 0x4C));

  if (r0 == r3)
  {
    goto loc_8904;
  }
  sub_08005E80(0x153);
  loc_8904:
  q3 = D_02021E90;

  q3 = q3;
  q3 += 0x146C;
  w2 = *((u16 *) q3);
  r0 = 0x09;
  r0 &= w2;
  if (r0 == 0)
  {
    goto loc_89DC;
  }
  r0 = *((u32 *) (r7 + 0x4C));
  if (r0 == 0)
  {
    goto loc_8930;
  }
  if (r0 == 1)
  {
    goto loc_899C;
  }
  goto loc_89DC;
  loc_8930:
  D_03000830.f4 = 0x00FF;

  r6 = 0;
  r4v = 0xC1 << 1;
  sub_08005E80(r4v);
  sub_08006044(0, r4v, 0x06, 0, sub_080C0384);
  *((u32 *) 0x020278D0) = 6;
  r4b = (u8 *) 0x02025FF0;
  b = r4b[0x08];
  sub_080102F0(b);
  r5 = r4b[0x08];
  sub_08007FE0();
  r4b[0x08] = r5;
  s = *((s16 *) (r7 + 0x22));
  s = s << 1;
  *((u8 *) ((((u32) s) + ((u32) r7)) + 0x19)) = (u8) r6;
  pp2 = &D_08671BD0;
  sub_080C31E8(r7 + 0x18, r7 + 0x22, 0x07, *pp2);
  goto loc_89DC;
  loc_899C:
  sub_08005E80(0x73);

  sub_08006044(0, 0x73, 0x0C, 0, sub_080C0384);
  sub_080060C4(0, 0x0C, 0, (s32) sub_080C0384);
  s = *((s16 *) (r7 + 0x22));
  ;
  new_var = 0x22;
  *((u8 *) ((((u32) (s << 1)) + ((u32) r7)) + 0x19)) = 0;
  pp3 = &D_08671BD0;
  sub_080C31E8(r7 + 0x18, r7 + new_var, 0x05, *pp3);
  loc_89DC:
  return;

}
