extern void stepAnimationTrack(s32, s32);
extern void setAnimationFrame(s32, s32, s32, s32);
extern s32 scaleByRandom(s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks[];

/* Effect update: advances the sprite animation, and when the sprite reaches
 * state 13 applies gravity, switches it to animation 0x11 and gives it a random
 * upward launch speed before advancing the script. */
void sub_080A42D8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    stepAnimationTrack((s32)sprite, (s32)anim);
    if (*(u16 *)(sprite + 0x28) == 0xD) {
        s32 zero;
        u8 *animDef;
        *(s32 *)(work + 0xC) += 0xFFEC0000;
        animDef = *(u8 **)(work + 0x28);
        zero = 0;
        animDef[1] = 5;
        setAnimationFrame((s32)sprite, (s32)anim, 0x11, 0);
        *(s32 *)(work + 0x14) = -(scaleByRandom(0xC000) + 0x6000);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        {
            s32 *scriptHandlers = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
        }
    }
}
