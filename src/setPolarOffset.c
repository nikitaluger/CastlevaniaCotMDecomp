extern s32 _call_via_r1(s32, s32);
extern u64 sub_080C37B4(s32, s32, s32, s32);

/* Polar to cartesian: look up sin(angle+0x4000)=cos(angle) and sin(angle) from
 * the sine function pointed to by 0x08671BFC, scale each by length with the
 * 64-bit multiply helper, and store the results at out+0x10 and out+0x14. */
void setPolarOffset(u8 *out, s32 angle, s32 length) {
    s32 *sinFn;
    s32 trig, trigHi, lenLow, lenHigh;
    volatile s32 len, lenHi;
    u32 x, y;
    sinFn = (s32 *)0x08671BFC;
    trig = _call_via_r1(angle + 0x4000, *sinFn);
    trigHi = trig >> 31;
    len = length;
    lenHi = length >> 31;
    lenLow = len;
    lenHigh = lenHi;
    x = (u32)(sub_080C37B4(trig, trigHi, lenLow, lenHigh) >> 16);
    trig = _call_via_r1(angle, *sinFn);
    trigHi = trig >> 31;
    lenLow = len;
    lenHigh = lenHi;
    y = (u32)(sub_080C37B4(trig, trigHi, lenLow, lenHigh) >> 16);
    *(u32 *)(out + 0x10) = x;
    *(u32 *)(out + 0x14) = y;
}
