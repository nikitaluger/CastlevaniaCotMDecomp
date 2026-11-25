void sub_080C36E0(void)
{
}

s64 sub_080C395C(u32 arg0, u32 arg1, s32 arg2)
{
    u32 r0 = arg0;
    u32 r1 = arg1;
    if (arg2 != 0) {
        s32 t = 32 - arg2;
        if (t <= 0) {
            r0 = arg1 >> -t;
            r1 = 0;
        } else {
            r0 = (arg0 >> arg2) | (arg1 << t);
            r1 = arg1 >> arg2;
        }
    }
    return ((s64)r1 << 32) | r0;
}

s64 sub_080C3990(s32 arg0, s32 arg1)
{
    s32 r0 = -arg0;
    s32 r1 = -arg1;
    if (r0 != 0)
        r1 -= 1;
    return ((s64)r1 << 32) | (u32)r0;
}

void sub_080C39A8(u16 *arg0, s16 *arg1)
{
    u16 *p = arg0 + *arg1;
    (*p)++;
    p++;
    if (p < (u16 *)arg1) {
        do {
            *p = 0;
            p++;
        } while (p < (u16 *)arg1);
    }
}
