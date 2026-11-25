void sub_08009C5C(void *arg0)
{
    u8 *x = *(u8 **)((u8 *)arg0 + 0x38);
    s8 v = *(s8 *)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x5C);
    s32 tmp;

    if (v != 0)
    {
        x += 0x2A;
        tmp = 0xBF & x[0];
        x[0] = (u8)tmp;
    }
    else
    {
        x += 0x2A;
        tmp = 0x40 | x[0];
        x[0] = (u8)tmp;
    }
}
