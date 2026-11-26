struct GameState {
    u8 _0[0x10];
    u32 scriptId;
    u32 state;
    u8 _1[4];
    u32 subState;
    u8 _2[0x1824];
    u32 flags;
};
extern struct GameState gMainWorkspace;

void sub_080C31E4(void *, void *, s32); /* advance the actor's bytecode stream */
void sub_08003740(void *, void *);      /* step a sub-script runner */
void sub_0806D588(void *, void *);      /* sync a sprite to its 3D position */

/* Moves the effect's 16.16 x position by its per-frame delta; once it passes
 * 180.0, switch the global sub-state to 2, clear the current script step and
 * run the next command; then tick the animation runner and sync the sprite to
 * the effect's position. */
void sub_08088F9C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *motion = *(u8 **)(self + 0x6C);
    u8 *pos = motion + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    s32 x = *(s32 *)(motion + 4) + *(s32 *)(pos + 8);
    *(s32 *)(motion + 4) = x;
    if (x > 0xB3FFFF) {
        gMainWorkspace.subState = 2;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            u32 *stream = (u32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *stream);
        }
    }
    sub_08003740(motion + 0x20, sprite);
    sub_0806D588(sprite, pos);
}
