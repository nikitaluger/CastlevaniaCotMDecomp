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

/* Script command: while the global sub-state is 1, clear the actor's current
 * script step byte and run the next command from the bytecode stream. */
void sub_08088FFC(void *arg0) {
    if (D_02025FF0.subState == 1) {
        void **streamTable;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = 0;
        streamTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*streamTable);
    }
}
