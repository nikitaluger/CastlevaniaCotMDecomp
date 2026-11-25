extern u32 D_030026B8;
extern u32 D_030026BC;
extern u32 D_030026C0[];
extern u8 D_030026A0;

/* Reset the two counters and clear the 16-entry table, then flag the entry
 * selected by the current index. */
void sub_080C3BB0(void)
{
    u32 index;
    u32 *ptr;
    u32 *table;
    u8 *curIndex;

    D_030026B8 = 0;
    D_030026BC = 0;

    index = 0;
    table = D_030026C0;
    curIndex = &D_030026A0;
    ptr = table;
    do
    {
        *ptr++ = 0;
        index++;
    } while (index <= 0xF);

    table[*curIndex] = 1;
}
