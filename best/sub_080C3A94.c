void sub_080C3A94(u16 *arg0, s16 *arg1) {
    u16 *end;
    u16 *p;
    u16 *q;
    u32 off;
    end = (u16 *)arg1;
    off = (u32)(*arg1) * 2 + 2;
    p = (u16 *)((u8 *)arg0 + off);
    if (p < end) {
        q = p;
        *q = *q - 1;
        q++;
        if (q < end) {
            u16 zero = 0;
            do {
                *q = zero;
                q++;
            } while (q < end);
        }
    }
}
