extern s32 sub_08005910(u32, u32);
extern s32 sub_080C31E0(s32, s32);
extern void *D_08671BFC;

u32 sub_080059DC(s32 arg0, s32 arg1) {
    s32 v0 = arg0 < 0 ? -arg0 : arg0;
    s32 v1 = arg1 < 0 ? -arg1 : arg1;
    s32 r2 = 0x10;
    s32 r5, r8, r3;
    u32 res;

    if ((u32)v0 < (u32)v1) {
        if (v0 & 0xFF800000) {
            do {
                r2 -= 1;
                v0 = (u32)v0 >> 1;
                v1 = (u32)v1 >> 1;
            } while (v0 & 0xFF800000);
        }
    } else {
        while (v1 & 0xFF800000) {
            r2 -= 1;
            v0 = (u32)v0 >> 1;
            v1 = (u32)v1 >> 1;
        }
    }
    r5 = sub_08005910((u32)v1, (u32)v0);
    {
        void **fnaddr = &D_08671BFC;
        r8 = sub_080C31E0(r5 + 0x4000, (s32)*fnaddr);
        r3 = sub_080C31E0(r5, (s32)*fnaddr);
    }
loop:
    if (r2 == 0) goto after;
    if ((v0 & 0xFFFF0000) == 0 && (v1 & 0xFFFF0000) == 0) goto after;
    v0 = (u32)v0 >> 1;
    v1 = (u32)v1 >> 1;
    r2 -= 1;
    goto loop;
after:
    if (r2 > 0) {
        res = (((u32)(r8 * v0) >> 1) + ((u32)(r3 * v1) >> 1)) >> (r2 - 1);
    } else {
        res = ((u32)(r8 * v0) + (u32)(r3 * v1)) >> r2;
    }
    return res;
}
