/* Actor work state: actor+0x3C points at the work block, and +0x48 into it is
 * a small timer block whose halfword +6 counts down. */
struct TimerState {
    u8 pad[6];
    u16 counter;
};

/* Tick the actor's work-block counter at +0x4E down by one frame. */
void sub_08055518(void *actor) {
    struct TimerState *state;

    state = (struct TimerState *)(*(u8 **)((u8 *)actor + 0x3C) + 0x48);
    state->counter = (u16)(state->counter - 1);
}
