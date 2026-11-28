extern void *spawnVariant2Effect(s32, s32, u16);
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

/* Spawn the actor's variant-2 effect object 16 pixels above it (y - 0x100000),
 * then chain to the actor's pending update callback. */
void sub_080479C0(struct Actor *actor) {
    struct Pos *pos = actor->pos;

    spawnVariant2Effect(pos->x, pos->y + 0xFFF00000, 8);
    sub_080C31E0(actor, actor->update);
}
