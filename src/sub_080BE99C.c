extern s32 divideInt(void *, s32);
extern s32 moduloInt(void *, s32);
extern void sub_08098534(s32, s32, s32);
extern u8 D_081031D8[];

void sub_080BE99C(void *arg0) {
    s32 sp0[4];
    s32 sp10[4];
    s32 *p10;
    u32 i;
    u32 j;
    u32 off;
    u8 *table;
    u32 color;

    i = 0;
    p10 = sp10;
    do
    {
        sp0[i] = divideInt(arg0, 8) - (s32)i;
        p10[i] = moduloInt(arg0, 8) + (s32)(i * 8);
        i++;
    } while (i <= 3);

    i = 0;
    table = D_081031D8;
    do
    {
        j = 0;
        off = i * 4;
        do
        {
            u32 val = *(u32 *)((u8 *)sp0 + off);
            if (val <= 0xF)
            {
                u32 v16 = val * 0x10;
                color = ((u32)table[j + v16] << 5) + 0x0600A000;
                sub_08098534(*(s32 *)((u8 *)p10 + off), color, 0x20);
            }
            j++;
        } while (j <= 0xF);
        i++;
    } while (i <= 3);
}
