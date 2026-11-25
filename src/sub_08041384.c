extern s32 sub_08014620(s32, s32, u16);
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

/* Spawn the actor's effect object 12 pixels above it (y - 0xC0000), then chain
 * to the actor's pending update callback. */
void sub_08041384(struct Actor *actor) {
    struct Pos *pos = actor->pos;

    sub_08014620(pos->x, pos->y + 0xFFF40000, 8);
    sub_080C31E0(actor, actor->update);
}
