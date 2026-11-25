extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_0808E348(s32, s32, s32, s32);
extern void sub_080C2E68(void *, u8 *, s32);
extern void sub_080C31E0(void *, s32);
extern s32 sub_080C36E4(s32, s32);
extern s32 D_02027888;
extern u8 D_02025FF0[];

void sub_08095F34(u8 *arg0)
{
  u8 sp[0x4C];
  s32 c1;
  s32 c2;
  s32 c3;
  s32 *p;
  u8 *pt;
  s32 i;
  s32 idx;
  s32 r5;
  s32 r6;
  s32 a;
  s32 c;
  s32 d;
  s32 flag;
  s32 cond;
  s32 tc;
  u8 *q;
  u8 *src;
  u8 *pb;
  p = *((s32 **) (arg0 + 0x3C));
  src = (u8 *) 0x08100AD0;
  sub_080C2E68(sp + 0xC, src, 0x40);
  i = 0;
  pt = sp + 0x10;
  do
  {
    s32 off;
    idx = (D_02027888 * 2) + i;
    off = (idx % 8) * 8;
    q = sp + off;
    q += 0xC;
    r5 = *((volatile s32 *) q);
    {
      u8 *r6p = pt + off;
      r6 = *((s32 *) r6p);
    }
    c1 = 0xFFE80000;
    a = ((*p) + sub_0800583C(0x80000)) + ((r5 << 0x14) + c1);
    c2 = 0xFFFC0000;
    r6 = ((*(p + 1)) + sub_0800583C(0x80000)) + ((r6 << 0x12) + c2);
    {
      s32 f1 = sub_08005820(0x2000);
      s32 f2 = sub_080C36E4(D_02027888, 5) - 2;
      c = (f1 + 0x3000) * f2;
    }
    d = 0x8000 - sub_08005820(0x20000);
    cond = ((D_02027888 * 2) + i) & 3;
    flag = 1;
    if (cond)
    {
      flag = 0;
    }
    *((s32 *) (sp + 0)) = 0x3000;
    *((s32 *) (sp + 4)) = flag;
    *((s32 *) (sp + 8)) = 8;
    sub_0808E348(a, r6, c, d);
    i++;
  }
  while (i <= 1);
  pb = D_02025FF0;
  pb += 0x1898;
  idx = *((s32 *) pb);
  {
    s32 off = (idx % 8) * 8;
    q = sp + off;
    q += 0xC;
    r5 = *((volatile s32 *) q);
    {
      u8 *r6p = pt + off;
      r6 = *((s32 *) r6p);
    }
  }
  a = ((*p) + sub_0800583C(0x80000)) + ((r5 << 0x14) + c1);
  c3 = 0x40000;
  tc = *(p + 1) + sub_0800583C(0x80000);
  r6 = ((r6 << 0x13) + tc) + c3;
  sub_0808DBF8(a, r6, 8);
  if ((*((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19))) > 0x0C)
  {
    sub_080C31E0(arg0, *((s32 *) (arg0 + 0x24)));
  }
}
