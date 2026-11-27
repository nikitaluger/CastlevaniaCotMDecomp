s32 stepAnimationTrack(s32, s32);
s32 sub_08011EE8(void *, s32, s32);
s32 setSpriteFlipForDirection(s32, s32);
s32 sub_0803B0D8(void *, void *, s32);
s32 sub_0803B0F8(void *, s32, void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Entity update: derive a facing-dependent displacement and pose (table at
 * 0x080CEDFC), advance the physics step and animation, then apply the pose;
 * when the pose counter reaches 3, clear the script-phase byte and fire the
 * callback at 0x08671BB0. */
void sub_08033DC0(void *entity) {
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    void *component = *(void **)((u8 *)entity + 0x3C);
    void *animator = (u8 *)component + 0x34;
    void *pose = (u8 *)component + 0x48;
    sub_0803B0D8(component, pose, 0x4000);
    sub_0803B0F8(component, sprite, pose, 0x080CEDFC);
    sub_08011EE8(component, 0x16C1, 0);
    stepAnimationTrack(sprite, (s32)animator);
    setSpriteFlipForDirection(sprite, *(s32 *)((u8 *)component + 0x10));
    if (*(u8 *)((u8 *)pose + 4) == 3) {
        *((s8 *)(((s16 *)((u8 *)entity + 0x22))[0] * 2 + (u8 *)entity + 0x19)) = 0;
        {
            s32 *soundTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *soundTable);
        }
    }
}
