void sub_080111D0(s32, s32, s32, s32);

void sub_08010FA4(s32 arg0, u8 *arg1, u16 *arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    s32 i = 0;
    u16 *p = arg2;
    if (!(p[0] & 0x8000)) {
        u16 mask = 0x8000;
        do {
            p += 2;
            i++;
        } while (!(p[0] & mask));
    }
    if (i > 0) {
        u16 *entry;
        i--;
        entry = arg2 + i * 2;
        *(u16 *)(arg1 + 2) = entry[0];
        *(u32 *)(arg1 + 4) = (u32)*(u16 *)(arg1 + 2) << 16;
        if (i > 0) {
            arg1[1] = i - 1;
        } else {
            arg1[1] = i + 1;
        }
        arg1[0] = arg6;
        sub_080111D0(arg0, (entry[1] << 3) + arg3, arg4, arg5);
    } else {
        s32 z1 = 0;
        s32 z0 = 0;
        *(u16 *)(arg1 + 2) = z0;
        *(u32 *)(arg1 + 4) = z0;
        arg1[1] = z1;
        arg1[0] = arg6 | 2;
    }
}
