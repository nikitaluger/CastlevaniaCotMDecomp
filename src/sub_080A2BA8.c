extern void sub_08005E80(u16 songId);
extern void *sub_0808DBF8(s32, s32, u16);
extern void sub_080C31E0(void *, s32);

/* Actor position block (16.16 fixed point). */
struct Pos {
    u8 _0[8];
    s32 x;    /* 0x08 */
    s32 y;    /* 0x0C */
};

struct Actor {
    u8 _0[0x24];
    s32 update;       /* 0x24: pending update callback, invoked via sub_080C31E0 */
    u8 _28[0x14];
    struct Pos *pos;  /* 0x3C: position block */
};

/* Play sound 0x189, spawn an effect object at the actor's own position with
 * parameter 8, then chain to the actor's pending update callback. */
void sub_080A2BA8(struct Actor *actor) {
    struct Pos *pos = actor->pos;

    sub_08005E80(0x189);
    sub_0808DBF8(pos->x, pos->y, 8);
    sub_080C31E0(actor, actor->update);
}
