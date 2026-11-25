extern void sub_080B0698(void *, s32, s32, u16);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern s32 D_08671BFC;
extern u8 D_081022A0[];
extern s32 D_08671BB0;

void sub_080ADA98(u8 *arg0) {
    u8 *r6 = arg0;
    u8 *r7 = *(u8 **)(r6 + 0x3C);
    u8 *r5 = r7 + 0x48;
    s32 *lit = &D_08671BFC;
    s32 r9 = sub_080C31E0(*(s32 *)(r6 + 0x6C), *lit) >> 8;
    s32 r8 = sub_080C31E0(*(s32 *)(r6 + 0x6C) + 0x4000, *lit) >> 8;
    u32 r4 = 0;
    u8 *tbl = D_081022A0;
    s16 idx;
    u8 t;
    s32 r1, r0, val;
    u32 *p;
    u32 wp;
    s32 a, b;
    u16 c;
    do {
        idx = *(s16 *)(r6 + 0x22);
        t = r6[idx * 2 + 0x19];
        r1 = t - 1;
        r0 = r1 << 3;
        r0 = r0 - r1;
        r0 = r0 + r4;
        r0 = r0 << 2;
        val = *(s32 *)(tbl + r0) >> 8;
        a = *(s32 *)(r7 + 8) + r8 * val;
        b = *(s32 *)(r7 + 0xC) + r9 * val;
        p = (u32 *)r5;
        wp = *p;
        p++;
        r5 = (u8 *)p;
        c = (u16)*(s32 *)(r6 + 0x6C);
        sub_080B0698((void *)wp, a, b, c);
        r4++;
    } while (r4 <= 6);
    idx = *(s16 *)(r6 + 0x22);
    if (r6[idx * 2 + 0x19] == 0x16) {
        u8 *p18, *p22;
        s32 *pd;
        r6[idx * 2 + 0x19] = 0;
        pd = &D_08671BB0;
        p18 = r6 + 0x18;
        p22 = r6 + 0x22;
        sub_080C31E4(p18, p22, (void *)*pd);
    }
}
