extern u16 gCrossfadeGfxState[];

/* Advance the object's counter, reset its timing fields, then queue the
 * sound command (0x142, 0x10) in the audio registers at gCrossfadeGfxState+4. */
void sub_080094D8(void *state) {
    u32 *words = (u32 *)state;

    words[1] = words[1] + 1;
    words[3] = 1;
    words[4] = 0x10;
    words[5] = 0;
    gCrossfadeGfxState[2] = 0x142;
    gCrossfadeGfxState[3] = 0x10;
}
