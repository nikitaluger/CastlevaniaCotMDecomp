extern u32 D_08671BD0;
s32 sub_080113A8(void *a, void *b, void *c, s32 d);
s32 copyPoseAttrs(void *a, void *b);
s32 sub_080C31E8(void *a, void *b, s32 c, s32 d);

void sub_08037CA4(void *a) {
    u8 *pa = (u8 *)a;
    void *r8p;
    void *p3C;
    u8 *r4;
    u8 *r2;
    s32 r3;
    s32 r5;
    s32 r6;
    s32 idx;
    s32 s;
    void *p;
    void *t;
    r8p = *(void **)(pa + 0x38);
    p3C = *(void **)(pa + 0x3C);
    r4 = (u8 *)p3C + 0x34;
    r2 = (u8 *)p3C + 0x48;
    r3 = 0;
    sub_080113A8(r8p, r4, r2, r3);

    if ((*(u8 *)r4 & 0x02) != 0) {
        u32 *pp;
        t = *(void **)(r2 + 0x0C);
        *(u8 *)((u8 *)t + 1) = 0;
        t = *(void **)(r2 + 0x10);
        *(u8 *)((u8 *)t + 1) = 0;
        s = *(s16 *)(pa + 0x22);
        s = s << 1;
        p = (void *)(pa + s);
        *(u8 *)((u8 *)p + 0x19) = 0;
        pp = &D_08671BD0;
        sub_080C31E8(pa + 0x18, pa + 0x22, 0, *pp);
    } else {
        r5 = 1;
        r6 = 0;
        idx = *(u16 *)((u8 *)r8p + 0x28);
        idx -= 14;
        if (idx <= 43) {
            switch (idx) {
                case 0: r3 = 0; r5 = 0; break;
                case 4: r3 = 1; break;
                case 9: r3 = 2; break;
                case 14: r3 = 3; break;
                case 19: r3 = 4; break;
                case 24: r3 = 5; break;
                case 28: r3 = 6; break;
                case 33: r3 = 7; break;
                case 38: r3 = 8; break;
                case 43: r3 = 9; r6 = 1; break;
                default: r3 = 0; break;
            }
        } else {
            r3 = 0;
        }
        t = *(void **)(r2 + 0x0C);
        *(u8 *)((u8 *)t + 1) = (u8)r5;
        t = *(void **)(r2 + 0x10);
        *(u8 *)((u8 *)t + 1) = (u8)r6;
        t = *(void **)(r2 + 0x0C);
        copyPoseAttrs(t, (void *)((u8 *)0x080CEFF4 + r3 * 8));
    }
}
