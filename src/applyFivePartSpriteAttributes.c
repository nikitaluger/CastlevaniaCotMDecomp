struct SpriteAttrs { u8 pad[6]; u16 attr0, attr1, attr2, attr3; };
struct SpriteSet { u8 pad[0x28]; struct SpriteAttrs * volatile primary; };
extern u16 D_080CFE3C[];
extern u16 D_080CFE6C[];
extern u16 D_080CFE94[];

/* Copies sprite-attribute groups from a base table or one of two style-specific
 * tables into the five attribute slots of an object's sprite set. */
void applyFivePartSpriteAttributes(void *arg0, void *arg1) {
    struct SpriteSet *set = *(struct SpriteSet **)((u8*)arg0 + 0x3C);
    struct SpriteAttrs *dest = (struct SpriteAttrs *)((u8*)set + 0x48);
    u16 *attrs = D_080CFE3C;
    s32 sources[5];
    s32 *fill;
    s32 addr;
    u16 style;
    struct SpriteAttrs *primary;
    u16 firstAttr;
    s32 * volatile *src;
    struct SpriteAttrs * volatile *dst;
    s32 i, offset;
    s32 *fill7;
    s32 *fillD;
    s32 addr7, addrD;

    addr = (s32)attrs + 0x28;
    fill = &sources[4];
    do { *fill = addr; addr -= 8; fill--; } while ((s32)fill >= (s32)sources);

    style = *(u16 *)((u8*)arg1 + 0x28);
    switch (style) {
    case 7:
        primary = set->primary; firstAttr = attrs[0]; dest = (struct SpriteAttrs *)((u8*)dest + 0x3C);
        offset = 0x20; addr7 = (s32)D_080CFE6C + offset;
        fill7 = &sources[4];
        do { *fill7 = addr7; addr7 -= 8; fill7--; } while ((s32)fill7 >= (s32)sources);
        break;
    case 0xD:
        primary = set->primary; firstAttr = attrs[0]; dest = (struct SpriteAttrs *)((u8*)dest + 0x3C);
        offset = 0x20; addrD = (s32)D_080CFE94 + offset;
        fillD = &sources[4];
        do { *fillD = addrD; addrD -= 8; fillD--; } while ((s32)fillD >= (s32)sources);
        break;
    default:
        primary = set->primary; firstAttr = attrs[0]; dest = (struct SpriteAttrs *)((u8*)dest + 0x3C);
        break;
    }
    primary->attr0 = firstAttr;
    set->primary->attr1 = attrs[1];
    set->primary->attr2 = attrs[2];
    set->primary->attr3 = attrs[3];

    src = (s32 * volatile *)sources;
    dst = (struct SpriteAttrs * volatile *)dest;
    for (i = 4; i >= 0; i--) {
        (*dst)->attr0 = ((u16 *)*src)[0];
        (*dst)->attr1 = ((u16 *)*src)[1];
        (*dst)->attr2 = ((u16 *)*src)[2];
        (*dst++)->attr3 = ((u16 *)*src++)[3];
    }
}
