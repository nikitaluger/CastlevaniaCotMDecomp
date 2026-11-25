void sub_0800FEDC(s32 arg0, u16 *arg1)
{
    if (arg0 == 0)
        return;
    do
    {
        *arg1 = 0;
        arg1--;
        arg0--;
    } while (arg0 != 0);
}

s32 sub_080C2F20(s32, s32);
s32 sub_080C2F24(s32, s32);

void sub_0800FE08(s32 arg0, s32 arg1, u16 arg2, u16 *arg3)
{
    s32 first = 0;
    s32 val = arg0;
    s32 count = arg1;
    u16 *p = arg3;
    u16 base = arg2;

    while (count != 0)
    {
        s32 rem = sub_080C2F24(val, 10);
        val = sub_080C2F20(val, 10);
        if (first != 0 || val != 0 || rem != 0)
            *p = base + rem;
        else
            *p = rem;
        p--;
        count--;
        first = 1;
    }
}

void sub_0800FDC8(s32 arg0, s32 arg1, u16 arg2, u16 *arg3)
{
    s32 val = arg0;
    s32 count = arg1;
    u16 *p = arg3;
    u16 base = arg2;

    if (count == 0)
        return;
    do
    {
        s32 rem = sub_080C2F24(val, 10);
        val = sub_080C2F20(val, 10);
        *p = rem + base;
        p--;
        count--;
    } while (count != 0);
}

void sub_0800FD84(s32 arg0, s32 arg1, u16 arg2, u16 *arg3)
{
    s32 val = arg0;
    u16 *p = arg3;
    u16 base = arg2;

    do
    {
        s32 rem = sub_080C2F24(val, 10);
        val = sub_080C2F20(val, 10);
        *p = (base + rem) & 0x3FF;
        p--;
    } while (val != 0);
}
