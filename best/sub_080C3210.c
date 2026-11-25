void _call_via_r12(void) {
}

void sub_080C3210(void) {
}

s32 sub_080C30B8(u8 *arg0, u8 *arg1, s32 arg2) {
    while (arg2-- != -1) {
        if (*arg0++ != *arg1++)
            return (s32)arg1 - 1;
    }
    return 0;
}

void sub_080C3060(u8 *arg0, u8 *arg1, s32 arg2) {
    while (arg2-- != -1) {
        *arg1++ = *arg0++;
    }
}
