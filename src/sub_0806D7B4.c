extern u8 D_02025368[];
extern void sub_0808D7BC(s32, s32, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 sub_08007B78(s32, s32, s32);

struct S_02025FF0_18A8 {
    u8 pad[0x18A8];
    u8 b;
};
extern struct S_02025FF0_18A8 D_02025FF0;
extern u8 D_02023130[];

struct Vec {
    s32 x;
    s32 y;
};

/* Add a 16-bit delta to the accumulator at sys+0x2D4, clamped to sys+0x2D6. */
void sub_0806D860(s16 delta)
{
    u8 *sys = D_02025368;
    s32 offset = 0x2D4;
    s16 *value = (s16 *)(sys + offset);
    s16 v = (s16)(*value + delta);
    *value = v;
    offset += 2;
    {
        s16 *limit = (s16 *)(sys + offset);
        s16 c = *limit;
        if (v > c)
        {
            *value = c;
        }
    }
}

/* Add `amount` to the 32-bit accumulator at sys+0x2C4 (clamped to sys+0x2C8),
 * then spawn a hit effect above `position`, using amount>>16 as its id. */
void sub_0806D7B4(struct Vec *position, s32 amount)
{
    u8 *sys = D_02025368;
    s32 *value = (s32 *)(sys + 0x2C4);
    s32 v = *value + amount;
    *value = v;
    {
        s32 *limit = (s32 *)(sys + 0x2C8);
        if (v > *limit)
        {
            *value = *limit;
        }
    }
    sub_0808D7BC(position->x, position->y + 0xFFE00000, amount >> 16, 2);
}

/* Add `percent` percent of the accumulator limit (at least 1.0) through
 * sub_0806D7B4. */
void sub_0806D77C(struct Vec *position, s32 percent)
{
    u8 *sys = D_02025368;
    s32 *limit = (s32 *)(sys + 0x2C8);
    s32 v = sub_080C364C(*limit, 100) * percent;
    if (v <= 0xFFFF)
    {
        v = 0x10000;
    }
    sub_0806D7B4(position, v);
}

/* Return 1 when a free map pixel is found within 8 pixels above `position`
 * (the pixel at the position itself must be solid), else 0. */
s32 sub_0806D654(struct Vec *position)
{
    s32 map = (s32)D_02023130 + ((u32)D_02025FF0.b << 6);
    s32 i;

    if ((u16)sub_08007B78(map, position->x, position->y) == 0)
    {
        return 0;
    }

    for (i = 0; i < 8; i++)
    {
        position->y += 0xFFFF0000;
        if ((u16)sub_08007B78(map, position->x, position->y) == 0)
        {
            return 1;
        }
    }

    return 0;
}
