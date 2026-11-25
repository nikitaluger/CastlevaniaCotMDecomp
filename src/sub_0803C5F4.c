extern void *sub_0805FAEC(u32 a, s32 b);
extern u32 D_02027860;

/* Spawn `count` objects from the pool rooted at D_02027860; each gets its
 * slot index modulo four, four s32 coordinates, two bytes and a direction
 * sign taken from bit 4 of params[1]. */
void sub_0803C5F4(u32 count, u16 *params, u8 mode, u8 subMode, s32 coord0, s32 coord1, s32 coord2, s32 coord3)
{
    s32 direction;
    u32 i;
    u32 bit;

    bit = params[1] & 0x10;
    direction = 1;
    direction = -direction;
    if (bit)
        direction = 1;

    i = 0;
    if (i < count) {
        u32 *poolRoot = &D_02027860;
        do {
            u8 *object = (u8 *)sub_0805FAEC(*poolRoot, 0xFB);
            if (object != 0) {
                u8 slot = i & 3;
                u8 *slotField = object + 0x8C;
                *slotField = slot;
                *(s32 *)(object + 0x4C) = coord0;
                *(s32 *)(object + 0x5C) = coord1;
                *(s32 *)(object + 0x6C) = coord2;
                *(s32 *)(object + 0x7C) = coord3;
                object[0x90] = mode;
                object[0x94] = subMode;
                object[0x98] = direction;
            }
            i++;
        } while (i < count);
    }
}
