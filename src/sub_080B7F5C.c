extern void sub_080C31E4(void *, void *, s32);
extern void sub_080148D8(s32, s32);

/* Script step: refresh the sprite's flag-0x10 from the value at work+8, then,
 * when the current action byte is 4, clear the move-state byte at +9 and the
 * action byte and advance the script. */
void sub_080B7F5C(void *arg0) {
    u8 *actor = (u8*)arg0;
    s32 sprite = *(s32*)(actor + 0x38);
    void *work = *(void **)(actor + 0x3C);
    u8 *moveState = (u8*)work + 0x48;
    s32 *advanceCb;
    sub_080148D8(sprite, *(s32*)((u8*)work + 8));
    if (*(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) == 4) {
        *(u8*)(moveState + 9) = 0;
        *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) = 0;
        advanceCb = (s32*)0x08671BB0;
        sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
    }
}
