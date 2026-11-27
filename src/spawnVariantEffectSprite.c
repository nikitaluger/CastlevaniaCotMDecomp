extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, s32, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrameAndRecord(void *, void *, void *, u32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u8 gVariantSpawnKindTable[];
extern u8 gVariantAnimFrameTable[];
extern u8 gEffectLayerAttrTable[];
extern u32 gScriptStepCallbackTable[];

/* Small render layer allocated from the effect pool for a spawned sprite. */
struct SubEffect {
    u8 mode; u8 kind; u8 layer; u8 priority;                              /* 0x00-0x03 */
    u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette; /* 0x04-0x0E */
    u32 object;                                                          /* 0x10 */
};
/* Effect work state at entity+0x3C. Field names keep the original byte offsets. */
struct Part {
    u8 _0[8];
    u32 x; u32 y;                           /* 0x08, 0x0C */
    u8 _10[0x0C];
    s16 kind;                               /* 0x1C: sprite kind selecting the graphics */
    u8 _1E[0x0A];
    struct SubEffect *effect;               /* 0x28 */
    u8 _2C[8];
    u8 animStart;                           /* 0x34 */
};
/* 20-byte animation definition in gSpriteKindTable. */
struct AnimDef { u16 gfxIndex; u16 _2; u16 palette; u8 _6[0x0E]; };
extern struct AnimDef gSpriteKindTable[];

/* Spawn a variant-driven sprite and render layer for an entity: initialise the
 * work state and graphics from the variant tables, place the sprite in screen
 * space using the camera scroll, mark the entity ready and dispatch its script. */
void spawnVariantEffectSprite(u8 *entity) {
    u8 *sprite;
    struct Part *work;
    u8 *animator;
    u8 *frameReq;
    struct SubEffect *effect;
    s32 sourceRef;
    u8 *layerAttrs;
    u8 *kindTable;
    u8 *frameTable;
    u8 *variantPtr;
    u8 *camera, *frameCounterPtr, *scrollX, *scrollY;
    u32 scrollIdx;

    sourceRef = *(s32 *)(entity + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(void **)(entity + 0x38) = sprite;
    allocWorkSlot(entity, 0, 0x50, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    work = *(struct Part **)(entity + 0x3C);
    animator = (u8 *)work + 0x34;
    frameReq = (u8 *)work + 0x48;
    installUpdateHandler(entity, (u8 *)work, (void *)sub_08014290);
    kindTable = gVariantSpawnKindTable;
    variantPtr = entity + 0x4C;
    initWorkStateForKind(entity, sprite, (u8 *)work, sourceRef, *(s16 *)(kindTable + *variantPtr * 4));
    initSpriteGraphics(sprite, animator, (s32)gSpriteAnimDataTable + *(s16 *)((u8 *)work + 0x1C) * 0xC);
    frameTable = gVariantAnimFrameTable;
    setAnimationFrameAndRecord(sprite, animator, frameReq, *(u16 *)(frameTable + *variantPtr * 2));
    layerAttrs = gEffectLayerAttrTable;
    effect = allocEffectPart();
    work->effect = effect;
    if (effect == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(entity, *(void **)(entity + 0x24));
    return;

body:
    effect->kind = 5;
    work->effect->layer = 8;
    work->effect->priority = 1;
    {
        sourceRef = 0;
        work->effect->gfxIndex = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].gfxIndex;
        work->effect->anim0 = *(u16 *)(layerAttrs + 0);
        work->effect->anim1 = *(u16 *)(layerAttrs + 2);
        work->effect->anim2 = *(u16 *)(layerAttrs + 4);
        work->effect->anim3 = *(u16 *)(layerAttrs + 6);
        work->effect->palette = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].palette;
    }
    work->effect->object = (u32)sprite;
    {
        camera = gCameraState;
        frameCounterPtr = gMainWorkspace;
        frameCounterPtr += 0x18A8;
        scrollIdx = ((u32)*frameCounterPtr + 1) * 0x40;
        scrollX = camera + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(scrollX + scrollIdx) + 0x8000) & 0xFFFF0000);
        scrollIdx = ((u32)*frameCounterPtr + 1) * 0x40;
        scrollY = camera + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(scrollY + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    registerScriptObject(entity, 0);
    {
        u16 flags = *(u16 *)(entity + 2);
        flags |= 0x1000;
        *(u16 *)(entity + 2) = flags;
    }
    *(u8 *)((u32)(*(s16 *)(entity + 0x22) * 2) + (u32)entity + 0x19) = (u8)sourceRef;
    {
        u32 *scriptOps = (u32 *)gScriptStepCallbackTable;
        u8 *scriptSlots = entity + 0x18;
        sub_080C31E4(scriptSlots, entity + 0x22, *scriptOps);
        {
            u8 *stepTimePtr = (u8 *)((u32)(*(s16 *)(entity + 0x22) * 2) + (u32)entity + 0x19);
            *stepTimePtr = (u8)(*stepTimePtr + 1);
            stepTimePtr = scriptSlots;
            stepTimePtr += *(s16 *)(entity + 0x22) * 2;
            {
                u8 opcode = *stepTimePtr;
                void *nextHandler = ((void **)*(void **)(entity + 0x14))[opcode];
                sub_080C31E0(entity, nextHandler);
            }
        }
    }
}
