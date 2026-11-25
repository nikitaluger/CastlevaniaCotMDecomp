void sub_08005E80(s32);
extern u16 D_0866D1B8[];

/* Starts the music track selected for the entity's current phase: +0x18 is the
 * track row and +0x2C selects the row's first, second or third entry. */
void sub_080158BC(void *unused, void *entity)
{
    s32 phase = 0;
    s16 state = *(s16 *)((u8 *)entity + 0x2C);

    if (state > 0x7D)
        phase = 1;
    else if (state > 0x96)
        phase = 2;

    {
        u16 song = D_0866D1B8[*(s16 *)((u8 *)entity + 0x18) * 3 + phase];
        if (song)
            sub_08005E80(song);
    }
}
