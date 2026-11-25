/* Fixed-point offset frame referenced by a sprite. */
struct Frame {
    u16 id;
    u16 flipFlags;          /* bit 0x10: flip X, bit 0x20: flip Y */
    u8 _pad4[0x14 - 0x04];
    s32 x;                  /* fixed-point X offset */
    s32 y;                  /* fixed-point Y offset */
};

/* Sprite slot in the list at D_020202A8; the fields at 0x24..0x2E shadow the
 * earlier attributes for double-buffered updates. */
struct Sprite {
    u8 flags;               /* +0x00; bit 0x40 = position refreshed */
    u8 attr1;               /* +0x01 */
    u8 _pad2[2];
    u16 attr4;              /* +0x04 */
    u16 attr6;              /* +0x06 */
    u16 attr8;              /* +0x08 */
    u16 baseX;              /* +0x0A */
    u16 baseY;              /* +0x0C */
    u16 attrE;              /* +0x0E */
    struct Frame *frame;    /* +0x10 */
    u8 _pad14[2];
    u16 attr16;             /* +0x16 */
    u8 _pad18[2];
    s16 offsetX;            /* +0x1A */
    s16 offsetY;            /* +0x1C */
    u8 _pad1E[2];
    struct Sprite *next;    /* +0x20 */
    u8 shadowFlags;         /* +0x24 */
    u8 _pad25;
    u16 shadowAttr6;        /* +0x26 */
    u16 shadowAttr8;        /* +0x28 */
    u16 shadowAttr4;        /* +0x2A */
    u16 shadowAttrE;        /* +0x2C */
    u16 shadowAttr16;       /* +0x2E */
    s16 screenX;            /* +0x30 */
    s16 screenY;            /* +0x32 */
};

extern struct Sprite *D_020202A8;
extern s32 D_020202AC;
extern s32 D_020202B0;

/* Walk the sprite list, converting each frame's fixed-point offsets into pixel
 * coordinates (applying the X/Y flip to the base position), mark the sprite as
 * refreshed, copy its attributes into the shadow fields, then clear the two
 * list bookkeeping globals. */
void sub_08016324(void)
{
    struct Sprite *sprite = D_020202A8;

    if (sprite != 0)
    {
        do
        {
            struct Frame *frame0;
            struct Frame *frame;
            s32 xFixed;
            s32 fixed;

            frame0 = sprite->frame;
            xFixed = frame0->x;
            frame = frame0;
            if (xFixed < 0) xFixed += 0xFFFF;
            sprite->offsetX = xFixed >> 16;

            fixed = frame->y;
            if (fixed < 0) fixed += 0xFFFF;
            sprite->offsetY = fixed >> 16;

            sprite->flags |= 0x40;

            if (frame->flipFlags & 0x10)
            {
                fixed = frame->x;
                if (fixed < 0) fixed += 0xFFFF;
                sprite->screenX = (fixed >> 16) - sprite->baseX;
            }
            else
            {
                fixed = frame->x;
                if (fixed < 0) fixed += 0xFFFF;
                sprite->screenX = (fixed >> 16) + sprite->baseX;
            }

            if (frame->flipFlags & 0x20)
            {
                fixed = frame->y;
                if (fixed < 0) fixed += 0xFFFF;
                sprite->screenY = (fixed >> 16) - sprite->baseY;
            }
            else
            {
                fixed = frame->y;
                if (fixed < 0) fixed += 0xFFFF;
                sprite->screenY = (fixed >> 16) + sprite->baseY;
            }

            sprite->shadowFlags = sprite->attr1;
            sprite->shadowAttr6 = sprite->attr6;
            sprite->shadowAttr8 = sprite->attr8;
            sprite->shadowAttr4 = sprite->attr4;
            sprite->shadowAttrE = sprite->attrE;
            sprite->shadowAttr16 = sprite->attr16;

            sprite = sprite->next;
        } while (sprite != 0);
    }

    D_020202AC = 0;
    D_020202B0 = 0;
}
