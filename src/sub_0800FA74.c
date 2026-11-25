/*
 * Screen transition: enable the effect on the object's sprite, point it at the
 * transition tile map, switch on 50% alpha blending and set the sprite's
 * scroll offset from the map row of the current entry.
 */
struct ScreenEffects {
    u8 pad[4];
    u16 blendControl;  /* BLDCNT: 0x3F40 = alpha blend on all layers */
    u16 blendAlpha;    /* BLDALPHA: 0x0808 = EVA 8 / EVB 8 */
};
extern struct ScreenEffects D_03000830;
extern u8 D_020278D0[];  /* map state: entry index at +0x6A, two row tables at +0x6B and +0x6F */
extern u8 D_086427B4[];  /* tile map of the transition */

struct Sprite {
    u8 pad0[2];
    u16 flags;
    u8 pad4[0x10];
    s32 offsetX;
    s32 offsetY;
    u8 pad1c[8];
    u32 tiles;
    u8 pad28[2];
    u8 state;  /* 0x40 = effect active */
};

void sub_0800FA74(void *arg0)
{
    struct Sprite *sprite;
    s8 *map;
    s8 *rowA;
    s8 *rowB;
    s32 entry;
    s32 rowDiff;
    s32 row;

    sprite = *(struct Sprite **)((u8 *)arg0 + 0x38);
    sprite->state |= 0x40;
    sprite->tiles = (u32)D_086427B4;
    D_03000830.blendControl = 0x3F40;
    D_03000830.blendAlpha = 0x0808;
    sprite->flags |= 0x0400;

    map = (s8 *)D_020278D0;
    rowA = map + 0x6A;
    entry = *rowA;
    rowA++;
    row = rowA[entry];
    rowB = map + 0x6F;
    rowDiff = row - rowB[entry];
    sprite->offsetX = (rowDiff & 1) * 0x700000;
    sprite->offsetY = ((u32)rowDiff >> 1) << 0x13;
}
