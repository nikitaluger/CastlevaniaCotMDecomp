s32 sub_08011344(s32, s32, s32, s32);
s32 stepAnimationTrack(s32, s32);
s32 sub_08011EE8(void *, s32, s32);
s32 setSpriteFlipForDirection(s32, s32);
s32 sub_0803B0D8(void *, void *, s32);
s32 sub_0803B0F8(void *, s32, void *, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Entity update: derive a facing-dependent displacement and pose (using the
 * table at 0x080CEF80), advance the physics step and apply the animation to
 * the sprite; when the pose counter reaches 3, force animation 9 and clear the
 * script-phase byte. */
void sub_08036278(void *entity) {
    void *self = entity;
    s32 sprite;
    void *component;
    s32 animator;
    void *pose;
    s32 *soundTable;
    s32 idx;

    sprite = *(s32 *)((u8 *)self + 0x38);
    component = *(void **)((u8 *)self + 0x3C);
    animator = (s32)((u8 *)component + 0x34);
    pose = (void *)((u8 *)component + 0x48);
    sub_0803B0D8(component, pose, 0x4000);
    sub_0803B0F8(component, sprite, pose, 0x080CEF80);
    sub_08011EE8(component, 0x16C1, 0);
    stepAnimationTrack(sprite, animator);
    setSpriteFlipForDirection(sprite, *(s32 *)((u8 *)component + 0x10));
    if (*(u8 *)((u8 *)pose + 4) == 3) {
        sub_08011344(sprite, animator, 9, 0);
        idx = *(s16 *)((u8 *)self + 0x22) * 2 + (s32)self;
        *(u8 *)(idx + 0x19) = 0;
        soundTable = (s32 *)0x08671BB0;
        sub_080C31E4((void *)((u8 *)self + 0x18), (void *)((u8 *)self + 0x22), *soundTable);
    }
}
