s32 sub_08011344(s32, s32, s32, s32);
s32 sub_080113A8(s32, s32);
s32 sub_08011EE8(void *, s32, s32);
s32 sub_08014668(s32, s32);
s32 sub_0803B0D8(void *, void *, s32);
s32 sub_0803B0F8(void *, s32, void *, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Entity update: derive a facing-dependent displacement and pose (using the
 * table at 0x080CF04C), advance the physics step and apply the animation to
 * the sprite; when the pose counter reaches 3, force animation 9 and clear the
 * script-phase byte. */
void sub_08037C18(void *entity) {
    s32 animator;
    void *component;
    s32 sprite;
    s32 *soundTable;
    void *pose;

    sprite = *(s32 *)((u8 *)entity + 0x38);
    component = *(void **)((u8 *)entity + 0x3C);
    animator = component + 0x34;
    pose = component + 0x48;
    sub_0803B0D8(component, pose, 0x4000);
    sub_0803B0F8(component, sprite, pose, 0x080CF04C);
    sub_08011EE8(component, 0x16C1, 0);
    sub_080113A8(sprite, animator);
    sub_08014668(sprite, *(s32 *)((u8 *)component + 0x10));
    if (*(u8 *)((u8 *)pose + 4) == 3) {
        sub_08011344(sprite, animator, 9, 0);
        *(s8 *)((s8 *)(*(s16 *)((u8 *)entity + 0x22) * 2 + entity) + 0x19) = 0;
        soundTable = (s32 *)0x08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *soundTable);
    }
}
