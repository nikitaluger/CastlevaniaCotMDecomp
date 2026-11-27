extern s32 updateObjectDisplayState(void *);
extern void advanceAnimTrack(void *, void *);
extern void setObjectAnimation(void *, void *, s32, s32);
extern s32 scaleByRandom(s32);
extern void sub_080C31E4(void *, void *, s32);

/* Action step: display the current animation frame; when it finishes, start
 * animation 0x28 with flag 1, store a random byte (0x28 + rand(0x28)) at +0x70,
 * clear the current script action byte and advance the script. */
void sub_080A9B98(void *arg0) {
    u8 *task = (u8*)arg0;
    void *sprite = *(void**)(task + 0x38);
    u8 *animState = (u8*)*(void**)(task + 0x3C) + 0x34;
    advanceAnimTrack(sprite, animState);
    if (*animState & 2) {
        s32 *scriptTable;
        u8 randByte;
        setObjectAnimation(sprite, animState, 0x28, 1);
        randByte = (u8)(scaleByRandom(0x28) + 0x28);
        {
            u8 *randField = task + 0x70;
            s32 zero = 0;
            *randField = randByte;
            *(u8*)(task + *(s16*)(task + 0x22) * 2 + 0x19) = (u8)zero;
        }
        scriptTable = (s32*)0x08671BB0;
        sub_080C31E4(task + 0x18, task + 0x22, *scriptTable);
    }
}
