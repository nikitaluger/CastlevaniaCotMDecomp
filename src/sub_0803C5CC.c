extern void moveEntityWithCollision(void *, s32);
extern void sub_080C31E0(void *, s32);

/* Movement/animation state driven by moveEntityWithCollision. The status halfword at
 * +0x02 is nonzero once the current movement step has finished. */
struct MoveState {
    u16 f0;
    u16 status;
};

struct Actor {
    u8 _0[0x24];
    s32 update;              /* 0x24: pending update callback, invoked via sub_080C31E0 */
    u8 _28[0x14];
    struct MoveState *move;  /* 0x3C: movement/animation state */
};

/* Advance the actor's movement by one step (0x16C1); when the movement reports
 * completion, chain to the actor's pending update callback. */
void sub_0803C5CC(struct Actor *actor) {
    struct MoveState *move = actor->move;

    moveEntityWithCollision(move, 0x16C1);
    if (move->status != 0) {
        sub_080C31E0(actor, actor->update);
    }
}
