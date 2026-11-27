void sub_080C31E0(void *, void *);

void sub_08040200(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7) {
    u8 *obj = a1;
    u8 *r4 = a4;
    u8 *r6 = a6;
    obj[0x19] = obj[0x19] + 1;
    r4 = r4 + *(s16 *)(r6 + 0x22) * 2;
    sub_080C31E0(r6, *(void **)(*(void **)(r4) + *(u32 *)(r6 + 0x14)));
}
