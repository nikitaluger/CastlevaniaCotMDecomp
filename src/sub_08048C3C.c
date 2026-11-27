s32 nextRandomWord();
s32 sub_08005E80(s32);
s32 sub_08049200(void *, void *, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
extern void *gMainObjTimerCallbacks;

/* Script tick: cue a sound on the first slot, cycle a counter that spawns a
 * radial burst, nudge the enemy horizontally per the slot flag, then finish
 * the slot once its timer reaches the fixed end value. */
void sub_08048C3C(void *arg0) {
    void *enemy;
    void *actor;
    void *enemyState;
    s32 zero;
    s32 stepCount;
    void **paramPtr;

    actor = *(void **)((u8 *)arg0 + 0x38);
    enemy = *(void **)((u8 *)arg0 + 0x3C);
    enemyState = (u8 *)enemy + 0x48;
    if (*(u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + (u8 *)arg0 + 0x19) == 1) {
        sub_08005E80(0x80);
    }
    zero = 0;
    *(u16 *)((u8 *)actor + 0x28) = zero;
    stepCount = *(s32 *)((u8 *)enemyState + 0x18) + 1;
    *(s32 *)((u8 *)enemyState + 0x18) = stepCount;
    if (stepCount == 3) {
        *(s32 *)((u8 *)enemyState + 0x18) = zero;
        sub_08049200(arg0, enemy, nextRandomWord() & 0xF, 1);
    }
    if (2 & *(u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + (u8 *)arg0 + 0x19)) {
        *(s32 *)((u8 *)enemy + 8) += 0x80 << 10;
    } else {
        *(s32 *)((u8 *)enemy + 8) += 0xFFFE0000;
    }
    if (*(u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + (u8 *)arg0 + 0x19) == 0x28) {
        *(s32 *)((u8 *)enemy + 0x14) = 0;
        *(s32 *)((u8 *)enemy + 0x10) = 0;
        sub_08005E80(0x8A);
        *(u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + (u8 *)arg0 + 0x19) = 0;
        paramPtr = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *(s32 *)paramPtr);
    }
}
