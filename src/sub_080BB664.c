extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);

/* In game mode 4 (gMainWorkspace word 16), play songs 0x1AF and 0x1B0, clear this
 * script step's sub-counter and advance the script through the 0x08671BB0
 * callback. */
void sub_080BB664(void *arg0) {
    u8 *actor = (u8 *)arg0;
    s32 *modeWord = (s32 *)0x02025FF0;
    s32 *advanceCb;
    if (modeWord[0x10] == 4) {
        sub_08005E80(0x1AF);
        sub_08005E80(0x1B0);
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        advanceCb = (s32 *)0x08671BB0;
        sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
    }
}
