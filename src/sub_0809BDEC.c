extern void sub_0809BE60(void);
/* Global gfx/effect state: +4 highlight colour, +6 packed fade weight. */
struct IO_830 { u8 pad[4]; u16 highlight; u16 fadeWeight; };
extern struct IO_830 gCrossfadeGfxState;
/* Sprite attribute word: +2 flags. */
struct F2 { u8 pad[2]; u16 flags; };

/* Begin a screen fade: set flag 0x400 on this actor's sprite and on every
 * sprite in the chained list, set the global highlight colour, start the fade
 * weight at 0x10, mark the actor with flag 0x800 and install the fade step. */
void sub_0809BDEC(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *link;
    struct F2 *sprite;
    u8 *next;
    struct IO_830 *gfx;
    void *fadeStep;

    sprite = *(struct F2 **)(*(u8 **)((u8 *)arg0 + 0x28) + 0x38);
    sprite->flags |= 0x400;
    link = *(u8 **)(self + 0x28);
    next = *(u8 **)(link + 0x30);
    gfx = &gCrossfadeGfxState;
    fadeStep = sub_0809BE60;
    while (next)
    {
        struct F2 *nextSprite = *(struct F2 **)(next + 0x38);
        if (nextSprite)
            nextSprite->flags |= 0x400;
        next = *(u8 **)(next + 0x2C);
    }
    gfx->highlight = 0x3F40;
    self[0x5C] = 0x10;
    self[0x60] = 0;
    gfx->fadeWeight = self[0x5C];
    *(u16 *)(self + 2) |= 0x800;
    *(u16 *)(self + 0x22) = 0;
    *(void **)(self + 0x14) = fadeStep;
}
