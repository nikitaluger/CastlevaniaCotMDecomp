struct GameState {
    u8 _0[0x10];
    u32 scriptId;
    u32 state;
    u8 _1[4];
    u32 subState;
    u8 _2[0x1824];
    u32 flags;
};
extern struct GameState D_02025FF0;

void sub_080C31E4(void *, void *, s32); /* advance the actor's bytecode stream */
void sub_08003A6C(void *, s32, s32);    /* initialize a sub-script runner */
void sub_0806D588(void *, void *);      /* sync a sprite to its 3D position */

/* Script command: while the global sub-state is 1, reinitialize the effect's
 * animation runner with handler table 0x085096C4, give it a per-frame x delta
 * of 0.5 (0x8000 in 16.16), clear the script step and run the next command;
 * then sync the sprite to the effect position. */
void sub_08088F40(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *motion = *(u8 **)(self + 0x6C);
    u8 *pos = motion + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *stream;
    if (D_02025FF0.subState == 1) {
        sub_08003A6C(motion + 0x20, 0, 0x085096C4);
        *(u32 *)(pos + 8) = 0x8000;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stream = (u32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stream);
    }
    sub_0806D588(sprite, pos);
}
