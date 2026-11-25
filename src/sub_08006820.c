s32 sub_080067B8(void);
extern u8 D_020227EC[];

/* Negates the 24-bit value at offset 0x44 of each 0x48-byte table entry in
 * [first,last], but only when integrating those entries stayed in range. */
void sub_08006820(s32 first, s32 last)
{
    if (sub_080067B8() != 0)
    {
        s32 idx = first;
        if (idx <= last)
        {
            u8 *table = D_020227EC;
            s32 offset = (idx << 3) + idx;
            offset <<= 3;
            offset += 0x44;
            {
                s32 *value = (s32 *)(table + offset);
                do
                {
                    *value = -*value;
                    value += 0x12;
                    idx++;
                } while (idx <= last);
            }
        }
    }
}
