extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_08013C5C(void *, s32);
extern void sub_08013C8C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern void sub_080142C0(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BDC;

void sub_08052F10(u8 *arg0) {
    s32 a = *(s32 *)(arg0 + 0x38);
    u8 *p = *(u8 **)(arg0 + 0x3C);
    u8 *r7 = p + 0x34;

    if (sub_080141AC(a, p) == 1) {
        return;
    }
    sub_08013C5C(arg0, a);
    if (sub_08013558(a, p, *(void **)(p + 0x28)) != 0) {
        sub_08013978(arg0, *(void **)(p + 0x28));
    }
    sub_080142C0(arg0, *(void **)(p + 0x28));
    if (*(u16 *)p & 1) {
        u8 *q0 = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        if (*(u8 *)(q0 + 0x1A) != 1) {
            sub_08013AC4(arg0);
            sub_08005E80(0x85);
            {
                u8 *q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
                u8 zero = 0;
                *(u8 *)(q + 0x1B) = zero;
                { void **fnaddr = &D_08671BDC;
                  sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, *fnaddr); }
            }
        }
    }
    if (sub_08013B5C(a, p) == 0) {
        *(void **)(arg0 + 0x14) = (void *)0x0866E680;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        {
            u8 *q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            q[0x19] = (u8)(q[0x19] + 1);
        }
        {
            s32 idx = (*(s16 *)(arg0 + 0x22)) * 2;
            u8 *base = arg0 + 0x18;
            u8 b = *(base + idx);
            void **tbl = *(void **)(arg0 + 0x14);
            void *v = tbl[b];
            sub_080C31E0(arg0, v);
        }
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
        if (*(u16 *)(arg0 + 0x02) & 0x8000) {
            return;
        }
        sub_080113A8(a, r7);
    }
    sub_08013C8C(arg0, a);
}
