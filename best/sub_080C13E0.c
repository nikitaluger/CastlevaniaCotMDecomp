void sub_080C13E0(void *arg0) {
    u8 *p = (u8 *)arg0;
    u8 v;
    p[0x1A] = 0;
    p[0x16] = 0;
    v = p[0x18];
    if (v == 0) v = 0x0C; else v = 0x03;
    v |= p[0x00];
    p[0x00] = v;
}
