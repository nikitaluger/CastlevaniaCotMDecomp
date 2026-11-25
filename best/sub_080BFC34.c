void sub_080BFC34(s32 unused, u8 *p)
{
    s32 n = p[2];
    n--;
    p[2] = n;
    *(u32 *)(p + 0x40) = *(u32 *)(p + 0x44 + n * 4);
}
