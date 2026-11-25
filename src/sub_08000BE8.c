/* Marks a heap block free by clearing the low flags byte of its header word,
 * which sits immediately before the block's data pointer. */
void sub_08000BE8(u8 *block)
{
    *(block - 4) = 0;
}

extern u32 D_02004060[];

void sub_08000BF0(void)
{
    u32 *p = D_02004060;
    u32 *end = D_02004060 + 0x100;
    if (p < end)
    {
        do
        {
            p[1] = 0;
            p += 2;
        } while (p < end);
    }
}

void *sub_08000C0C(void *arg0)
{
    u32 *p = D_02004060;
    u32 *end = D_02004060 + 0x100;
    while (p < end)
    {
        if (p[1] == 0)
        {
            p[1] = (u32)arg0;
            p[0] = 0;
            return p;
        }
        p += 2;
    }
    return 0;
}

s32 sub_08000BA4(u8 *arg0, u32 arg1)
{
    u32 words = (arg1 + 3) >> 2;
    u32 bytes = words << 2;
    u32 *hdr = (u32 *)(arg0 - 4);
    s32 size = *hdr >> 8;
    if ((u32)size < bytes)
        return -1;
    {
        s32 remain = size - bytes - 4;
        if (remain > 0)
        {
            u8 *next = (u8 *)hdr + bytes + 4;
            *next = 0;
            *(u32 *)next |= (u32)remain << 8;
            *hdr = (*hdr & 0xFF) | (words << 10);
        }
    }
    return (s32)(*hdr >> 8);
}
