extern u8 gCameraState[];

/* Rewind both write cursors of the tile/name-table buffer (0x1448 and 0x144C)
 * to its start at 0x1450, clear the row counter to 0 and tick the buffer's
 * update counter. */
s32 sub_0806032C(void)
{
    u8 *state = gCameraState;
    *(u32 *)(state + 0x1448) = *(u32 *)(state + 0x1450);
    *(u32 *)(state + 0x144C) = *(u32 *)(state + 0x1450);
    state[0x1443] = 0;
    (*(u32 *)(state + 0x1454))++;
    return 0;
}
