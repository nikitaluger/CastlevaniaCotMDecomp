extern u8 gGameStatus[];
extern u16 D_080E0AC8[];
extern s32 signedRemainder(s32, s32);
extern void sub_08005E80(void);

/* Play one of nine alternate sound IDs from D_080E0AC8, selected by the counter
 * at state+0x90 modulo 9; a zero ID means "play nothing". The selected ID is
 * still in r0 when sub_08005E80 is called, so it becomes that function's songId. */
void sub_0806DE0C(void) {
    u8 *state;
    u16 *soundIds;
    s32 counter;
    s32 soundIndex;
    state = gGameStatus;
    soundIds = D_080E0AC8;
    state += 0x90;
    counter = *(s32 *)state;
    soundIndex = signedRemainder(counter, 9);
    if (soundIds[soundIndex] != 0) {
        sub_08005E80();
    }
}
