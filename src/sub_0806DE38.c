extern u8 gGameStatus[];
extern u16 D_080E0ADA[];
extern void sub_08005E80(void);

/* Alternates between the two sound IDs in D_080E0ADA according to the parity of
 * the counter at state+0x90; a zero ID means "play nothing". The selected ID is
 * still in r0 when sub_08005E80 is called, so it becomes that function's songId. */
void sub_0806DE38(void) {
    u8 *state;
    s32 soundIndex;
    s32 counter;
    u16 *soundIds;
    state = gGameStatus;
    soundIds = D_080E0ADA;
    state += 0x90;
    counter = *(s32 *)state;
    soundIndex = counter - (counter / 2) * 2;
    if (soundIds[soundIndex] != 0) {
        sub_08005E80();
    }
}
