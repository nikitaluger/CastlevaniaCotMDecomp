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

s32 divideInt(s32, s32);
s32 moduloInt(s32, s32);

void drawDecimalNumber(s32 arg0, s32 arg1, u16 arg2, u16 *arg3)
{
    s32 first = 0;
    s32 val = arg0;
    s32 count = arg1;
    u16 *p = arg3;
    u16 base = arg2;

    while (count != 0)
    {
        s32 rem = moduloInt(val, 10);
        val = divideInt(val, 10);
        if (first != 0 || val != 0 || rem != 0)
            *p = base + rem;
        else
            *p = rem;
        p--;
        count--;
        first = 1;
    }
}

void drawPaddedDecimal(s32 arg0, s32 arg1, u16 arg2, u16 *arg3)
{
    s32 val = arg0;
    s32 count = arg1;
    u16 *p = arg3;
    u16 base = arg2;

    if (count == 0)
        return;
    do
    {
        s32 rem = moduloInt(val, 10);
        val = divideInt(val, 10);
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
        s32 rem = moduloInt(val, 10);
        val = divideInt(val, 10);
        *p = (base + rem) & 0x3FF;
        p--;
    } while (val != 0);
}
