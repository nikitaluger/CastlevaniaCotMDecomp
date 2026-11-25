extern s32 sub_080059DC(s32, s32);
extern s32 sub_080C2F20(s32, s32);
inline int inline_fn(s32 arg0)
{
  return arg0 + 0x0C;
}

void sub_080A8374(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
  s32 A;
  s32 B;
  s32 D;
  u32 i;
  s32 off1;
  s32 off2;
  s32 *r8;
  s32 r9base;
  s32 r6;
  s32 r7;
  s32 r4;
  s32 r5;
  s32 r0;
  s32 r1;
  s32 r2;
  s32 r3;
  s32 C;
  s32 t;
  A = arg0;
  B = arg1;
  C = arg2;
  D = arg3;
  r9base = arg6;
  *((s32 *) (r9base + 0x04)) = 0;
  *((s32 *) (r9base + 0x08)) = 0;
  *((s32 *) (r9base + 0x0C)) = 0;
  i = 1;
  r8 = (s32 *) (r9base + 0x04);
  off1 = 0;
  off2 = 0x14;
  while (1)
  {
    t = sub_080059DC(A, B);
    r6 = sub_080059DC(t, C);
    r7 = 0x800;
    if (i <= 6)
    {
      r7 = 0x1200;
    }
    r4 = sub_080C2F20(r7 * A, r6) << 8;
    r5 = sub_080C2F20(r7 * B, r6) << 8;
    r0 = sub_080C2F20(C * r7, r6) << 8;
    r1 = *r8;
    r1 = r1 + r4;
    r8[5] = r1;
    r1 = r9base + 0x08;
    r2 = r1 + off2;
    r1 = r1 + off1;
    r1 = *((s32 *) r1);
    ;
    *((s32 *) r2) = r1 + r5;
    r1 = inline_fn(r9base);
    ;
    r1 = r1 + off1;
    r1 = *((s32 *) r1);
    r1 = r1 + r0;
    *((s32 *) (r1 + off2)) = r1;
    A = A + D;
    B = B + arg4;
    C = C + arg5;
    r8 = (s32 *) (((u8 *) r8) + 0x14);
    off1 = off1 + 0x14;
    off2 = off2 + 0x14;
    i = i + 1;
    if (i > 7)
    {
      break;
    }
  }

}

