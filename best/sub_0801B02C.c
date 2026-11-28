extern s32 getSpriteFacingSign(void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *sub_0801C454(void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E4(void *, void *, u32);

struct GfxLayer {
    u8 mode;
    u8 renderKind;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 affine0;
    u16 affine1;
    u16 affine2;
    u16 affine3;
    u16 palette;
    u32 sprite;
    u16 tail;
};
struct AnimState { u8 _0[0x34]; struct GfxLayer *gfx; };
struct AnimEntry { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x20]; };
extern struct AnimEntry gEffectGfxTable[];
extern u16 D_080CE680[];

void sub_0801B02C(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    u8 *field = *(u8 **)(self + 0x3C);
    u8 *anim = field + 0x34;
    u8 *state = field + 0x48;
    s32 val;

    setAnimationFrame(sprite, anim, 5, 0);
    if (!(*(u8 *)anim & 2))
        return;

    if (getSpriteFacingSign(sprite) < 0)
        val = *(s32 *)(field + 8) - 0x240000;
    else
        val = *(s32 *)(field + 8) + 0x240000;

    *(u32 *)(state + 0x30) = (u32)sub_0801C454(self, val, *(s32 *)(field + 0xC) - 0x280000);
    *(u16 *)(state + 0x16) = 0x78;
    ((struct AnimState *)state)->gfx = (struct GfxLayer *)allocEffectPart();
    if (((struct AnimState *)state)->gfx == NULL)
        return;

    { ((struct AnimState *)state)->gfx->renderKind = 0;
    ((struct AnimState *)state)->gfx->layer = 8;
    ((struct AnimState *)state)->gfx->priority = 1;
    ((struct AnimState *)state)->gfx->gfxIndex = gEffectGfxTable[*(s16 *)(field + 0x1C)].baseTile;
    ((struct AnimState *)state)->gfx->affine0 = D_080CE680[0];
    ((struct AnimState *)state)->gfx->affine1 = D_080CE680[1];
    ((struct AnimState *)state)->gfx->affine2 = D_080CE680[2];
    ((struct AnimState *)state)->gfx->affine3 = D_080CE680[3];
    do { ((struct AnimState *)state)->gfx->palette = gEffectGfxTable[*(s16 *)(field + 0x1C)].extra; ((struct AnimState *)state)->gfx->sprite = (u32)sprite; } while (0);
    }
    ((struct AnimState *)state)->gfx->tail = 0;

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *cb = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *cb);
    }
}
