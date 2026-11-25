extern s32 sub_080C36E0(void);

s32 sub_080C364C(u32 arg0, u32 arg1)
{
    u32 sign = arg0 ^ arg1;
    u32 q = 0;
    u32 m = 1;
    u32 t;

    if (arg1 == 0) goto div_zero;

    if ((s32)arg1 < 0) arg1 = -arg1;
    if ((s32)arg0 < 0) arg0 = -arg0;

    if (arg0 < arg1) goto done;

    t = 0x10000000;
shift4_loop:
    if (arg1 >= t) goto shift1_loop;
    if (arg1 >= arg0) goto shift1_loop;
    arg1 <<= 4;
    m <<= 4;
    goto shift4_loop;

shift1_loop:
    t <<= 3;
shift1_loop2:
    if (arg1 >= t) goto sub_loop;
    if (arg1 >= arg0) goto sub_loop;
    arg1 <<= 1;
    m <<= 1;
    goto shift1_loop2;

sub_loop:
    if (arg0 < arg1) goto check_half;
    arg0 -= arg1;
    q |= m;

check_half:
    t = arg1 >> 1;
    if (arg0 < t) goto check_quarter;
    arg0 -= t;
    q |= m >> 1;

check_quarter:
    t = arg1 >> 2;
    if (arg0 < t) goto check_eighth;
    arg0 -= t;
    q |= m >> 2;

check_eighth:
    t = arg1 >> 3;
    if (arg0 < t) goto next_iter;
    arg0 -= t;
    q |= m >> 3;

next_iter:
    if (arg0 == 0) goto done;
    m >>= 4;
    if (m == 0) goto done;
    arg1 >>= 4;
    goto sub_loop;

done:
    arg0 = q;
    if ((s32)sign < 0) arg0 = -arg0;
    return arg0;

div_zero:
    sub_080C36E0();
    return 0;
}
