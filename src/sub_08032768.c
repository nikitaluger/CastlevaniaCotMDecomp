void stepAnimationTrack(s32, s32);
void sub_08011EE8(void *, s32, s32);
s32 checkActorViewBounds(s32, s32);
void sub_0803B0F8(void *, s32, void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Per-frame update of one object part: bail out when the target is off-screen,
 * otherwise run its motion update, apply its current animation frame, and once
 * the animation reaches phase 3 advance the object's remaining part script. */
void sub_08032768(void *arg0) {
    u8 *self = arg0;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *target = *(u8 **)(self + 0x3C);
    u8 *spriteData = target + 0x34;
    u8 *animState = target + 0x48;
    if (checkActorViewBounds((s32)gfx, (s32)target) == 1) return;
    sub_0803B0F8(target, (s32)gfx, animState, 0x080CEBD8);
    sub_08011EE8(target, 0x16C1, 0);
    stepAnimationTrack((s32)gfx, (s32)spriteData);
    if (*(u8 *)(animState + 4) == 3) {
        void **stepTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stepTable = (void **)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
    }
}
