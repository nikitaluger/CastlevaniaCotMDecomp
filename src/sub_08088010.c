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

void sub_080C31E4(void *, void *, s32); /* _call_via_r2 */
void sub_08003A6C(void *, s32, s32); /* initialize a sub-script runner */
void sub_08003740(void *, void *); /* step a sub-script runner */

/* Script command: once the global game state is 0x11, initialize the actor's
 * sub-script runner with handler table 0x085063F8, step it against the actor's
 * sprite, clear the current step's byte and run the next command. */
void sub_08088010(void *arg0) {
    void *work = *(void **)((u8 *)arg0 + 0x6C);
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    if (D_02025FF0.state == 0x11) {
        void *runner = (u8 *)work + 0x20;
        sub_08003A6C(runner, 0, 0x085063F8);
        sub_08003740(runner, sprite);
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *stream = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stream);
        }
    }
}
