void sub_08018410(void *arg0) {
    u8 *base;
    void **p;
    void *q;
    s32 i;
    base = *(u8 **)((u8 *)arg0 + 0x3C);
    p = (void **)(base + 0x80);
    i = 9;
    do {
        q = *p;
        if (q != 0) {
            *(u16 *)((u8 *)q + 0x64) |= 1;
            *p = 0;
        }
        p++;
        i--;
    } while (i >= 0);
}
