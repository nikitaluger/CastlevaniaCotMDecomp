extern u8 gGameStatus[];
extern void sub_0808D7BC(s32, s32, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 sub_08007B78(s32, s32, s32);

struct S_02025FF0_18A8 {
    u8 pad[0x18A8];
    u8 mapIndex;
};
extern struct S_02025FF0_18A8 gMainWorkspace;
extern u8 gTilemapPages[];

struct Vec {
    s32 x;
    s32 y;
};

/* Adds a signed delta to the clamped 16-bit field at gGameStatus+0x2D4 and
 * caps it at the maximum stored at +0x2D6. */
void sub_0806D860(s16 delta) {
    u8 *base = gGameStatus;
    s32 offset = 0x2D4;
    s16 *p = (s16 *)(base + offset);
    s16 v = (s16)(*p + delta);
    *p = v;
    offset += 2;
    {
        s16 *cap = (s16 *)(base + offset);
        s16 c = *cap;
        if (v > c)
        {
            *p = c;
        }
    }
}

/* Adds a 16.16 amount to the effect budget at gGameStatus+0x2C4, clamps it to
 * the cap at +0x2C8, then spawns a scripted effect above pos (amount>>16 is
 * the effect definition id). */
void sub_0806D7B4(struct Vec *pos, s32 amount) {
    u8 *base = gGameStatus;
    s32 *p = (s32 *)(base + 0x2C4);
    s32 v = *p + amount;
    *p = v;
    {
        s32 *cap = (s32 *)(base + 0x2C8);
        if (v > *cap)
        {
            *p = *cap;
        }
    }
    sub_0808D7BC(pos->x, pos->y + 0xFFE00000, amount >> 16, 2);
}

/* Scales amount by the cap at gGameStatus+0x2C8 divided by 100, with a minimum
 * of one whole unit (0x10000), then applies it through sub_0806D7B4. */
void spawnScaledEffect(struct Vec *pos, s32 amount) {
    u8 *base = gGameStatus;
    s32 *cap = (s32 *)(base + 0x2C8);
    s32 v = divInt32(*cap, 100) * amount;
    if (v <= 0xFFFF)
    {
        v = 0x10000;
    }
    sub_0806D7B4(pos, v);
}

/* If the map attribute under pos is set, lifts pos in 1.0 steps (up to eight)
 * until it clears; returns 1 on a successful lift, 0 otherwise. */
s32 sub_0806D654(struct Vec *pos) {
    s32 base = (s32)gTilemapPages + ((u32)gMainWorkspace.mapIndex << 6);
    s32 i;

    if ((u16)sub_08007B78(base, pos->x, pos->y) == 0)
    {
        return 0;
    }

    for (i = 0; i < 8; i++)
    {
        pos->y += 0xFFFF0000;
        if ((u16)sub_08007B78(base, pos->x, pos->y) == 0)
        {
            return 1;
        }
    }

    return 0;
}
