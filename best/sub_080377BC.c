extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, s32, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void *allocSpriteConfigPart(void *, void *, void *);
extern void sub_08037E34(void);
extern void sub_08016664(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u8 D_080CEFF4[];
extern u8 gEffectGfxTable[];
extern u32 gMainObjTimerCallbacks[];

struct TwoLayerPart {
    u8 _0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;
    u32 f10;
    u8 _14[0x0C];
};

void sub_080377BC(u8 *obj) {
    u8 *sprite;
    u8 *work;
    u8 *anim;
    u8 *layerPtrs;
    u8 *layerAttrs;
    u8 *gfxAttrs;
    struct TwoLayerPart *part;
    s32 param;
    s32 zero;
    u8 *scrollTbl;
    u8 *frameCounterPtr;
    u8 *scrollXBase;
    u8 *scrollYBase;
    u32 scrollRow;
    u8 *stepClear;
    u8 *stepAdvance;
    u8 *stepWord;
    u8 *table;
    void *cleanupFn;

    param = *(s32 *)(obj + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL)
        goto fail;
    *(void **)(obj + 0x38) = sprite;
    allocWorkSlot(obj, 0, 0x5C, 0);
    if (*(u32 *)(obj + 0x3C) == 0)
        goto fail;
    *(u32 *)(sprite + 0x1C) = MULTI_PART_SPRITE_GFX_ID;
    work = *(u8 **)(obj + 0x3C);
    anim = work + 0x34;
    layerPtrs = work + 0x48;
    installUpdateHandler(obj, work, (void *)sub_08037E34);
    initWorkStateForKind(obj, sprite, work, param, 0x1C);
    zero = 0;
    *(u16 *)(work + 4) = 8;
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + *(s16 *)(work + 0x1C) * 0xC);
    setAnimationFrame(sprite, anim, 0, 1);
    allocSpriteConfigPart(obj, work, sprite);
    layerAttrs = D_080CEFF4;

    part = allocEffectPart();
    *(u32 *)(layerPtrs + 0xC) = (u32)part;
    if (part == NULL)
        goto fail;
    part->f1 = zero;
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->f2 = 8;
    param = 1;
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->f3 = param;
    gfxAttrs = gEffectGfxTable;
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->f4 = *(u16 *)(gfxAttrs + *(s16 *)(work + 0x1C) * 40 + 4);
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->f6 = *(u16 *)(layerAttrs + 0);
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->f8 = *(u16 *)(layerAttrs + 2);
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->fA = *(u16 *)(layerAttrs + 4);
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->fC = *(u16 *)(layerAttrs + 6);
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->fE = *(u16 *)(gfxAttrs + *(s16 *)(work + 0x1C) * 40 + 6);
    (*(struct TwoLayerPart **)(layerPtrs + 0xC))->f10 = (u32)sprite;
    layerAttrs = layerAttrs + 0x50;

    part = allocEffectPart();
    *(u32 *)(layerPtrs + 0x10) = (u32)part;
    if (part != NULL)
        goto init_second;

fail:
    sub_080C31E0(obj, *(void **)(obj + 0x24));
    return;

init_second:
    part->f1 = zero;
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->f2 = 8;
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->f3 = param;
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->f4 = *(u16 *)(gfxAttrs + *(s16 *)(work + 0x1C) * 40 + 4);
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->f6 = *(u16 *)(layerAttrs + 0);
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->f8 = *(u16 *)(layerAttrs + 2);
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->fA = *(u16 *)(layerAttrs + 4);
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->fC = *(u16 *)(layerAttrs + 6);
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->fE = *(u16 *)(gfxAttrs + *(s16 *)(work + 0x1C) * 40 + 6);
    (*(struct TwoLayerPart **)(layerPtrs + 0x10))->f10 = (u32)sprite;

    scrollTbl = gCameraState;
    frameCounterPtr = gMainWorkspace;
    frameCounterPtr += 0x18A8;
    scrollRow = ((u32)*frameCounterPtr + 1) * 0x40;
    scrollXBase = scrollTbl + 0x1278;
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 0x08) - ((*(u32 *)(scrollXBase + scrollRow) + 0x8000) & 0xFFFF0000);
    scrollRow = ((u32)*frameCounterPtr + 1) * 0x40;
    scrollYBase = scrollTbl + 0x127C;
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0x0C) - ((*(u32 *)(scrollYBase + scrollRow) + 0xFFFF8000) & 0xFFFF0000);

    sub_08016664(obj, 0);
    *(u16 *)(obj + 2) |= 0x1000;
    stepClear = (u8 *)(*(s16 *)(obj + 0x22) * 2 + obj + 0x19);
    *stepClear = zero;
    sub_080C31E4(obj + 0x18, obj + 0x22, gMainObjTimerCallbacks[0]);
    stepAdvance = (u8 *)(*(s16 *)(obj + 0x22) * 2 + obj + 0x19);
    *stepAdvance = *stepAdvance + 1;
    stepWord = (u8 *)(obj + 0x18 + *(s16 *)(obj + 0x22) * 2);
    table = *(u8 **)(stepWord + 4);
    cleanupFn = *(void **)(table + *stepWord * 4);
    sub_080C31E0(obj, cleanupFn);
}
