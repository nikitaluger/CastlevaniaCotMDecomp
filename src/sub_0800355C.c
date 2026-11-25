extern s32 D_08671BF8;
extern void *sub_080C31DC(s32);

struct SpriteObj355C {
    u16 unk00;
    u16 unk02;
    u16 scaleX;
    u16 scaleY;
    u16 unk08;
    u8 padA[0x0A];
    s32 posX;
    s32 posY;
    s32 unk1C;
    u8 pad20[4];
    u32 gfxData;
    u16 frame;
    u8 palette;
    u8 unk2B;
};

/* Allocates and initializes a sprite/effect object at 1.0 scale and zero
 * position, with the default graphics table 0x0866CA0C and palette 0xC0;
 * returns NULL when the allocation fails. */
struct SpriteObj355C *sub_0800355C(void)
{
    struct SpriteObj355C *obj = sub_080C31DC(D_08671BF8);

    if (obj == 0)
        return 0;
    obj->unk00 = 0;
    obj->unk02 = 0;
    obj->posX = 0;
    obj->posY = 0;
    obj->unk1C = 0;
    obj->scaleX = 0x100;
    obj->scaleY = 0x100;
    obj->unk08 = 0;
    obj->gfxData = 0x0866CA0C;
    obj->frame = 0;
    obj->palette = 0xC0;
    obj->unk2B = 0;
    return obj;
}
