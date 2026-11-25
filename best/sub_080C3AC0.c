void sub_080C3AC0(u8 *arg0, s16 *arg1) {
    u8 *p;
    p = arg0 + (*arg1 * 2);
    *(u16 *)p -= 1;
    *(u8 *)p = 0;
    p += 2;
    if ((u32)p < (u32)arg1) {
        do {
            *(u16 *)p = 0;
            p += 2;
        } while ((u32)p < (u32)arg1);
    }
}
