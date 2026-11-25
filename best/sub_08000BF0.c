extern u32 D_02004060[];

void sub_08000BF0(void)
{
    u32 *p = D_02004060;
    u32 *end = D_02004060 + 0x100;
    do
    {
        p[1] = 0;
        p += 2;
    } while (p < end);
}
