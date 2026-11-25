void sub_08000E98(s32, s32, s32, s32, s32);
void sub_080BBD80(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *p = *(void **)(self + 0x28);
    u8 *q = *(u8 **)((u8 *)p + 0x4C);
    s32 idx = *(s32 *)(self + 0x5C);
    if (idx != 0) {
        s8 v = *(s8 *)(q + 0x35);
        s32 x = ~v;
        s32 b = (s32)((u32)(x | -x) >> 31);
        s32 *arr;
        arr = (s32 *)0x08670690;
        sub_08000E98(1, arr[idx + b * 3], 0x0600BF80, 0x80, 0x10);
    }
}

void sub_080BB984(void *arg0, void *arg1) {
    u8 *a0 = (u8 *)arg0;
    u8 *a1 = (u8 *)arg1;
    u32 c = *(u32 *)(a1 + 0x68) + 1;
    *(u32 *)(a1 + 0x68) = c;
    if ((c & 0xF) == 0) {
        switch (c & 0x30) {
        case 0:
        case 0x10:
            *(u32 *)(a0 + 0x0C) += 0xFFFF0000;
            break;
        case 0x20:
        case 0x30:
            *(u32 *)(a0 + 0x0C) += 0x10000;
            break;
        }
    }
}
