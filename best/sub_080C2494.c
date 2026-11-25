extern s32 sub_080C1764(void *work);

s32 sub_080C2494(s32 a, s32 b, s32 c, s32 d, volatile s32 e)
{
    s32 buf[5];
    volatile s32 *pd = &d;
    volatile s32 *pe = &e;
    s32 dv = *pd;
    s32 ev = *pe;

    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = dv;
    buf[4] = ev;
    return sub_080C1764(buf);
}
