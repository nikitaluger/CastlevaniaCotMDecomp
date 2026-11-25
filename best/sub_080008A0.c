void sub_080008A0(u8 *arg0, u32 arg1) {
    u8 *p;
    s32 pad;
    u32 n = arg1;
    if (n <= 3) {
        p = arg0;
        if (n != 0) { do { *p = 0; p++; n--; } while (n != 0); }
    } else {
        pad = ((u32)(arg0 + 4) & ~3U) - (u32)arg0;
        n -= pad;
        p = arg0;
        if (pad != 0) { do { *p = 0; p++; pad--; } while (pad != 0); }
        pad = n >> 2;
        if (pad != 0) { do { *(u32 *)p = 0; p += 4; pad--; } while (pad != 0); }
        pad = n & 3;
        if (pad != 0) { do { *p = 0; p++; pad--; } while (pad != 0); }
    }
}
