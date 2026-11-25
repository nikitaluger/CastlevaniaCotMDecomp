void *sub_08001534(u32 arg0, u8 *arg1)
{
    u32 mask;
    u32 key;
    u8 *p;
    u8 *end;

    mask = 0x3FFF;
    key = arg0 & mask;
    p = arg1 + 0xBC;
    end = *(u8 **)0x02025B74;
    if (p < end)
    {
        u32 m = mask;
        u8 *e = end;
        do
        {
            if ((*(u16 *)p & m) == key)
                return p;
            p += 0xBC;
        } while (p < e);
    }
    return 0;
}
