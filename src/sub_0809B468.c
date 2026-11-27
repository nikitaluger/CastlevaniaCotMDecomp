extern void moveEntityWithCollision(void *, s32);
extern void sub_080C31E0(void *, s32);

/* The status halfword at +0x02 is set once the current movement step finishes. */
struct MoveState {
    u16 f0;
    u16 status;
};

struct Actor {
    u8 _0[0x24];
    s32 update;              /* 0x24: pending update callback, invoked via sub_080C31E0 */
    u8 _28[0x14];
    struct MoveState *move;  /* 0x3C: movement/animation state */
    u8 _40[0x2C];
    s32 step;                /* 0x6C: movement step parameter */
};

/* Advance the actor's movement by the scripted step; when the movement reports
 * completion, chain to the actor's pending update callback. */
void sub_0809B468(struct Actor *actor)
{
    struct MoveState *move = actor->move;

    moveEntityWithCollision(move, actor->step);
    if (move->status != 0)
    {
        sub_080C31E0(actor, actor->update);
    }
}
