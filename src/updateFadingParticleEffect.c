extern u32 nextRandomWord(void);              /* pseudo-random number */
extern s32 randomSignedOffset(s32);                /* random in [0, arg) */
extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void spawnVariant2Effect(s32, s32, s32);     /* spawn a particle at x, y */
extern void sub_08098428(s32, s32);          /* scale OBJ palettes by arg1/0x10000 */
extern s32 sub_080C31E0(s32, s32);           /* call the sine table entry */
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080C0384;

/* Shared game state block: a state request at 0x10 and the current mode at 0x40. */
struct S_02025FF0 { u8 _0[0x10]; s32 state; u8 _14[0x2C]; s32 mode; };
extern struct S_02025FF0 gMainWorkspace;

/* Update an expanding/rotating effect: drift the linked body sideways, fade its
 * palettes out, and while alive spray particles at random angles around it;
 * when the fade ends request state 8, and in mode 3 retune the audio player,
 * clear this effect's script byte and dispatch its next handler. */
void updateFadingParticleEffect(void *effect) {
    void *bodyWork = *(void**)((u8*)effect+0x3C);
    void *fadeState = (u8*)bodyWork + 0x48;
    void *childObj = *(void**)((u8*)effect+0x4C);
    s32 fadeLevel;
    s32 *callbackSlot;
    u8 zero;
    u8 *childAnimFlag;
    if (2 & *((u8*)effect + *(s16*)((u8*)effect+0x22)*2 + 0x19)) {
        *(s32*)((u8*)bodyWork+8) = *(s32*)((u8*)bodyWork+8) + 0x10000;
    } else {
        *(s32*)((u8*)bodyWork+8) = *(s32*)((u8*)bodyWork+8) + 0xFFFF0000;
    }
    sub_08098428(0x30, *(s32*)((u8*)fadeState+0x0C));
    fadeLevel = *(s32*)((u8*)fadeState+0x0C) + 0xFFFFFEC0;
    *(s32*)((u8*)fadeState+0x0C) = fadeLevel;
    if (fadeLevel < 0) *(s32*)((u8*)fadeState+0x0C) = 0;
    if (*(s32*)((u8*)fadeState+0x0C) == 0 && *((u8*)fadeState+8) == 0) {
        *((u8*)fadeState+8) = 1;
        gMainWorkspace.state = 8;
    }
    if (!(1 & *((u8*)effect + *(s16*)((u8*)effect+0x22)*2 + 0x19))) {
        s32 spread = randomSignedOffset(0x380000);
        u32 angle = nextRandomWord() & 0xFFFF;
        s32 *sinTable = (s32*)TRIG_FUNC_TABLE;
        s32 x = *(s32*)((u8*)bodyWork+8) + ((spread >> 8) * (sub_080C31E0(angle + 0x4000, *sinTable) >> 8));
        spawnVariant2Effect(x, *(s32*)((u8*)bodyWork+0x0C) + ((spread >> 8) * (sub_080C31E0(angle, *sinTable) >> 8)) + 0x100000, 8);
    }
    if (gMainWorkspace.mode == 3) {
        sub_08005FC4(0, 0x186, 3, 0, &sub_080C0384);
        childAnimFlag = (u8*)childObj + 0x34;
        zero = 0;               /* match: keep a zero value live in a register */
        *childAnimFlag = 1;
        *((u8*)effect + *(s16*)((u8*)effect+0x22)*2 + 0x19) = zero;
        callbackSlot = (s32*)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        sub_080C31E4((u8*)effect+0x18, (u8*)effect+0x22, *callbackSlot);
    }
}
