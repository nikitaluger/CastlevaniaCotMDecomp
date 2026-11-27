void sub_08014668(u8 *arg0, s32 arg1) {
    s32 tmp;
    if (arg1 == 0)
        return;
    if (arg1 < 0) {
        tmp = 0xFFEF & *(u16 *)(arg0 + 2);
        *(u16 *)(arg0 + 2) = tmp;
    } else {
        tmp = 0x10 | *(u16 *)(arg0 + 2);
        *(u16 *)(arg0 + 2) = tmp;
    }
}
