/* Entity update: refresh the sprite's visibility flag, then when this
 * entity's sequence timer reaches 0x1E start an animation, clear an effect
 * field, play a sound, reset the timer and install the next callback. */
extern void setSpriteFacingToTarget(void *, s32);
extern void forceAnimationFrame(void *, void *, s32, s32);
extern void setEffectBehavior(s32, s32);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0809A404(void *entity) {
    u8 *self = (u8 *)entity;
    void *sprite = *(void **)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *anim = state + 0x34;
    u8 *fx = state + 0x48;
    setSpriteFacingToTarget(sprite, *(s32 *)(state + 8));
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        forceAnimationFrame(sprite, anim, 9, 0);
        setEffectBehavior(*(s32 *)(fx + 8), 0);
        sub_08005E80(0x163);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *cbTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *cbTable);
        }
    }
}
