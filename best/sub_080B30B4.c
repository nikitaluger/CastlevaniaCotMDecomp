extern s32 sub_08005820(s32);
extern void sub_080B3048(s32, s32, u16);
void sub_080B30B4(s32 arg0, s32 arg1, void *arg2) {
  s32 t = ~arg0;
  u32 sign = ((u32) (-t) | (u32) t) >> 31;
  s32 off = arg1 * 0x10 + (sign << 5);
  s32 base = 0x081028FC;
  s32 *pbase = &base;
  s32 base2 = 0x0810293C;
  u8 *p2 = (u8 *) arg2;
  s32 v1 = *(s32 *) (base + off);
  s32 v2 = *(s32 *) (base + off + 4);
  s32 sum1 = *(s32 *) (p2 + 8) + v1;
  s32 r9 = sub_08005820(v2 - v1) + sum1;
  s32 v3, v4, sum2, r8v, off2, v6, v5, v7;
  base = *pbase;
  { s32 b8 = base + 8;
    s32 a3 = off + b8;
    s32 bc = base + 0xC;
    s32 a4 = off + bc;
    v3 = *(s32 *) a3;
    v4 = *(s32 *) a4; }
  sum2 = *(s32 *) (p2 + 0xC) + v3;
  r8v = sub_08005820(v4 - v3) + sum2;
  off2 = sign << 3;
  v6 = *(s32 *) (base2 + off2);
  v5 = *(s32 *) (base2 + off2 + 4);
  v7 = sub_08005820(v5 - v6) + v6;
  sub_080B3048(r9, r8v, (u16) v7);
}
