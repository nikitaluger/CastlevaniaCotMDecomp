/* Copies the current demo track's two configuration words from the static table
 * into the sprite setup data, then sets a 20-byte region of demo state to 1. */
void sub_0808B584(u32 *spriteData)
{
    u8 *demoState = (u8 *)0x02025358;
    s32 i;
    u32 *entry;
    u8 *fillBase;
    s32 fillValue;

    i = (demoState[0x0C] & 0x0F) * 0x1C;
    entry = (u32 *)0x080E6988 + (i >> 2);
    spriteData[0] = entry[1];
    spriteData[1] = entry[2];

    i = 0;
    fillBase = demoState + (0xC7 << 2);
    fillValue = 1;
    do
    {
        s32 offset = i << 2;
        s32 nextI = i + 1;
        s32 count;
        u8 *p;
        offset = offset + i;
        offset = offset << 1;
        count = 9;
        offset = offset + (s32)fillBase;
        p = (u8 *)(offset + 9);
        do
        {
            *p = (u8)fillValue;
            p--;
            count--;
        } while (count >= 0);
        i = nextI;
    } while (i <= 1);
}
