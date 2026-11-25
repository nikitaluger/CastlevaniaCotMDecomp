extern void sub_080C36E0(void);

u32 sub_080C3824(u32 arg0, u32 arg1) {
    if (arg1 != 0) {
        u32 s = 1, q = 0;
        if (arg0 >= arg1) {
            u32 t = 1, tmp;
            t <<= 28;
loop_3:
            if (arg1 < t && arg1 < arg0) { arg1 <<= 4; s <<= 4; goto loop_3; }
            t <<= 3;
loop_7:
            if (arg1 < t && arg1 < arg0) { arg1 <<= 1; s <<= 1; goto loop_7; }
loop_10:
            if (arg0 >= arg1) { arg0 -= arg1; q |= s; }
            tmp = arg1 >> 1; if (arg0 >= tmp) { arg0 -= tmp; q |= s >> 1; }
            tmp = arg1 >> 2; if (arg0 >= tmp) { arg0 -= tmp; q |= s >> 2; }
            tmp = arg1 >> 3; if (arg0 >= tmp) { arg0 -= tmp; q |= s >> 3; }
            if (arg0 != 0) {
                s >>= 4;
                if (s != 0) { arg1 >>= 4; goto loop_10; }
            }
        }
        return q;
    }
    sub_080C36E0();
    return 0;
}
