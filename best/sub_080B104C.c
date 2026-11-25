extern s32 sub_08005820(u8);
extern void sub_080C31E8(u8 *, u8 *, s32, s32);
extern s32 D_02025FF0[];
extern u8 D_081026C8[];
extern u16 D_081026E8[];
extern s32 D_08671BD8[];
void sub_080B104C(u8 *arg0)
{
    u8 *p = *(u8 **)(arg0 + 0x3C);
    u8 *d = p + 0x48;
    u8 *tbl = D_081026C8;
    u8 v;
    s32 k;
    s32 idx;
    v = tbl[d[6] * 4];
    k = sub_08005820(v) + 1;
    idx = k + d[6] * 4;
    d[4] = tbl[idx];
    if (*(s32 *)(p + 8) > 0x01000000) {
        if (D_02025FF0[0x5D3] <= 0x002FFFFF) { d[4] = 0; goto after_zero; }
    }
    if (*(s32 *)(p + 8) <= 0x00FFFFFF) {
        if (D_02025FF0[0x5D3] > 0x01D00000) { d[4] = 0; goto after_zero; }
    }
after_zero:
    if (*(s32 *)(p + 8) <= 0x00FFFFFF) {
        if (D_02025FF0[0x5D3] <= 0x002FFFFF) { d[4] = 1; goto done; }
    }
    if (*(s32 *)(p + 8) > 0x01000000) {
        if (D_02025FF0[0x5D3] > 0x01D00000) d[4] = 1;
    }
done:
    v = (1 << d[4]) | d[6];
    d[6] = v;
    if (v == 7) d[6] = 0;
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x17) = 0;
    { s32 *gp = D_08671BD8; sub_080C31E8(arg0 + 0x18, arg0 + 0x22, D_081026E8[d[4]], gp[0]); }
}
