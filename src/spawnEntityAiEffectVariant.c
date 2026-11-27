/* Spawn a variant of an entity's scripted AI effect: allocate and seed a render
 * layer from the global tuning tables, install the cleanup handler and timer,
 * then advance the entity's script by one step. */
extern void startEffectTimer(void *, s32, void *);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s16 scalePercentSaturate16(u16, s32);
extern void releaseAiEffectGroup(void);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 gAiVariantAnimSequence;
extern u32 gAiVariantTimerData;
extern s32 gMainObjTimerCallbacks;

void spawnEntityAiEffectVariant(u8 *entity) {
    u32 zero;
    u32 two;
    u32 c;
    u8 *brain = *(u8 **)(entity + 0x6C);
    u8 *brainCtx = brain + 4;
    u8 *aux = *(u8 **)(entity + 0x38);
    u8 *cfg = gGameStatus;
    void *layer;
    struct AiVariantWorkSlot *ctx = (struct AiVariantWorkSlot *)brainCtx;

    layer = allocEffectPart();
    ctx->layer = layer;
    if (layer == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    zero = 0;
    *(u8 *)(layer + 1) = zero;
    {
        u8 *layerPtr = ctx->layer;
        two = 2;
        *(u8 *)(layerPtr + 2) = two;
    }
    *(u8 *)(ctx->layer + 3) = AI_VARIANT_LAYER_PRIORITY;
    *(u16 *)(ctx->layer + 4) = zero;
    *(u16 *)(ctx->layer + 6) = 6;
    *(u16 *)(ctx->layer + 8) = 6;
    *(u16 *)(ctx->layer + 0xA) = zero;
    *(u16 *)(ctx->layer + 0xC) = zero;
    *(u16 *)(ctx->layer + 0xE) = scalePercentSaturate16(*(u16 *)(cfg + 0x2DE), 0x64);
    {
        u8 *layerPtr = ctx->layer;
        *(void **)(layerPtr + 0x10) = aux;
        *(u16 *)(layerPtr + 0x16) = AI_VARIANT_LAYER_TIMER;
    }
    *(u16 *)(ctx->layer + 0x18) = AI_VARIANT_LAYER_TAIL;
    *(u32 *)(brainCtx + 0x18) = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&releaseAiEffectGroup;
    *(u32 *)(aux + 0x24) = (u32)&gAiVariantAnimSequence;
    startEffectTimer(brain + 0x30, 0, &gAiVariantTimerData);
    {
        u8 *base = gMainWorkspace;
        *(s32 *)(brain + 4) = *(s32 *)(base + 0x1728);
        *(s32 *)(brainCtx + 4) = *(s32 *)(base + 0x172C) + AI_VARIANT_WORK_Y_BIAS;
        *(u32 *)(brainCtx + 0x10) = AI_VARIANT_WORK_FLAGS;
        *(u8 *)(base + 0x14EC) = two;
        c = 0x80 << 3;
        *(u16 *)(aux + 4) = c;
        *(u16 *)(aux + 6) = c;
        *(u16 *)(aux + 8) = zero;
        *(u32 *)(aux + 0x1C) = AI_VARIANT_GFX_ID;
        *(u16 *)(aux + 0) = *(u16 *)(base + 0x18C2);
    }
    *(u32 *)(brainCtx + 0x4C) = *(u32 *)(entity + 0x7C);
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
    {
        s32 *scriptTable = &gMainObjTimerCallbacks;
        u8 *scriptPtr = entity + 0x18;
        _call_via_r2(scriptPtr, entity + 0x22, *scriptTable);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) + 1;
        scriptPtr += *(s16 *)(entity + 0x22) * 2;
        {
            u8 scriptId = *scriptPtr;
            _call_via_r1(entity, *(s32 *)(scriptId * 4 + *(u32 *)(entity + 0x14)));
        }
    }
}
