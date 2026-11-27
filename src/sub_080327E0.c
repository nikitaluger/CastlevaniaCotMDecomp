extern s32 checkActorViewBounds(void *, void *);
extern void sub_0803B0F8(void *, void *, void *, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* When the sprite/work hit-test is not active, refresh the pose from the
 * action table, play sound 0x16C1, start the animation, and — if the sprite's
 * state at +0x28 is 8 — clear the current script step and advance it. */
void sub_080327E0(void *entity) {
    void *entityCopy;
    void *sprite;
    void *work;
    void *pose;
    void *animator;
    s32 *scriptFn;
    entityCopy = entity;
    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    animator = (u8 *)work + 0x34;
    pose = (u8 *)work + 0x48;
    if (checkActorViewBounds(sprite, work) != 1) {
        sub_0803B0F8(work, sprite, pose, (void *)0x080CEBD8);
        sub_08011EE8(work, 0x16C1, 0);
        stepAnimationTrack(sprite, animator);
        if (*(u16 *)((u8 *)sprite + 0x28) == 8) {
            *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
            scriptFn = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptFn);
        }
    }
}
