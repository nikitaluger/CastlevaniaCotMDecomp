void sub_080C3B0C(u16 *arg0, u16 *arg1, s32 arg2, u16 arg3)
{
    u16 *p = (u16 *)((u8 *)arg0 + ((s16)arg2 * 2));
    *p = arg3;
    p++;
    if (p < arg1) {
        do {
            *p = 0;
            p++;
        } while (p < arg1);
    }
}

void sub_080C3B28(u16 *arg0, s16 *arg1, u16 arg2)
{
    if (*arg1 > 0) {
        u16 *p = arg0 + *arg1 - 1;
        *p = arg2;
        p++;
        if (p < (u16 *)arg1) {
            do {
                *p = 0;
                p++;
            } while (p < (u16 *)arg1);
        }
    }
}

void sub_080C3AE8(u16 *arg0, s16 *arg1, u16 arg2)
{
    u16 *p = arg0 + *arg1;
    *p = arg2;
    p++;
    if (p < (u16 *)arg1) {
        do {
            *p = 0;
            p++;
        } while (p < (u16 *)arg1);
    }
}

void sub_080C3B54(u16 *arg0, s16 *arg1, u16 arg2)
{
    u16 *p = arg0 + *arg1 + 1;
    if (p < (u16 *)arg1) {
        *p = arg2;
        p++;
        if (p < (u16 *)arg1) {
            do {
                *p = 0;
                p++;
            } while (p < (u16 *)arg1);
        }
    }
}
