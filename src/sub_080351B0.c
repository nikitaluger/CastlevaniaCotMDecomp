/*
 * Actor script step: keep the idle animation running, and at step 0x0F aim the
 * actor at the player, clear the step counter and advance the script.
 */
extern s32 sub_08005910(s32 dy, s32 dx);  /* direction angle of a vector */
extern void stepAnimationTrack(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct PlayerPos {
    u8 pad[0x174C];
    u32 x;
    u32 y;
};
extern struct PlayerPos gMainWorkspace;

void sub_080351B0(u8 *self) {
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    u8 *move = work + 0x48;

    stepAnimationTrack(sprite, animator);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x0F) {
        s32 dy = gMainWorkspace.y - *(s32 *)(work + 0x0C);
        s32 dx = gMainWorkspace.x - *(s32 *)(work + 0x08);
        *(s32 *)(move + 4) = sub_08005910(dy, dx);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *stepCallback = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *stepCallback);
        }
    }
}
