static void sub_080C39CC(u16 *arg0, s16 *arg1) {
    s16 idx = *arg1;
    if (idx > 0) {
        u16 *p = arg0 + (idx - 1);
        *p = *p + 1;
        p++;
        if (p < (u16 *)arg1) {
            do {
                *p = 0;
                p++;
            } while (p < (u16 *)arg1);
        }
    }
}
