void sub_08051CE8(void *arg0) {
    void *first;
    void *t0;
    void *v3;
    u8 *a;
    u8 val;
    first = *(void **)((u8 *)arg0 + 0x30);
    if (first != NULL) {
        a = (u8 *)first;
        a += 0x70;
        *a = 1;
        t0 = *(void *volatile *)((u8 *)first + 0x2C);
        v3 = t0;
        if (t0 != NULL) {
            val = 1;
            do {
                t0 = v3;
                *(u8 *)((u8 *)t0 + 0x70) = val;
                t0 = *(void *volatile *)((u8 *)t0 + 0x2C);
                v3 = t0;
            } while (t0 != NULL);
        }
    }
}
