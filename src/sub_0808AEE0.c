extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);

struct S_02025368 {
    u8 _0[0x94];
    u16 unk94;
};

struct S_02025FF0 {
    u8 _0[0x10];
    s32 unk10;
    u8 _1[0x1728 - 0x14];
    u32 unk1728;
};

struct P2A { u8 pad[0x2A]; u8 f2A; };

extern struct S_02025368 D_02025368;
extern struct S_02025FF0 D_02025FF0;

/* Advance the entity's state timer and sprite flags, refresh its camera-relative
 * position, set a global mode when a position threshold is crossed, and dispatch
 * the next script step unless a global state id matches. */
void sub_0808AEE0(void *entity)
{
    u8 *self;
    u8 *state;
    u8 *sprite;
    u8 *pos;
    struct S_02025368 *globals;

    self = (u8 *)entity;
    state = *(u8 **)(self + 0x6C);
    sprite = *(u8 **)(self + 0x38);
    pos = state + 4;
    globals = &D_02025368;

    *(s32 *)(pos + 0x2C) = *(s32 *)(pos + 0x2C) + 1;
    sub_08003740(state + 0x20, sprite);

    if (*(u32 *)(pos + 0x2C) & 2)
        ((struct P2A *)sprite)->f2A |= 0x40;
    else
        ((struct P2A *)sprite)->f2A &= 0xBF;

    sub_0806D588(sprite, pos);

    if ((u32)(D_02025FF0.unk1728 + 0xFFC80000) <= 0x100000)
        D_02025FF0.unk10 = 0x10;

    if (globals->unk94 != 0x10D)
        sub_080C31E0(self, *(void **)(self + 0x24));
}
