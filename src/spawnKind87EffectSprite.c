extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;
extern struct FixedEffectKindEntry gEffectGfxTable[];
extern u16 gKind87EffectAffineParams[];
extern u32 gKind87EffectParamTable[];
extern u8 gSpriteAnimDataTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void releaseKind87Effect(void);
extern void sub_0801D11C(u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

/* Builds a kind-0x87 effect sprite for an entity: allocates its sprite and work
 * state, fills a render part from the kind tables, places it against the camera
 * scroll, starts its animation, then advances the script. */
void spawnKind87EffectSprite(struct FixedEffectEntity *entity) {
    u8 *sprite;
    struct FixedEffectState *state;
    u8 *gfxInit;
    u8 *spriteLayer;
    s32 animSlot;
    u32 spriteAttr;
    u32 zero;
    u8 *camera;
    u8 *effectData;
    u8 *scriptEntry;
    s32 *callbackPtr;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        sub_0801D11C((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x5C, 0);
    state = entity->state;
    if (state == NULL) {
        sub_0801D11C((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    gfxInit = (u8 *)state + 0x34;
    state->savedHandler = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)releaseKind87Effect;
    state->kind = SPRITE_KIND_KIND87_EFFECT;
    zero = 0;
    state->f18 = 1;
    state->worldX = entity->posX << 16;
    state->worldY = entity->posY << 16;
    animSlot = findKindIndex(SPRITE_KIND_KIND87_EFFECT);
    state->animSlot = animSlot;
    if ((s32)(animSlot << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + state->kind * 0xC);
    spriteLayer = allocEffectPart();
    state->spriteLayer = (struct FixedEffectSpriteLayer *)spriteLayer;
    if (spriteLayer == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }

    state->spriteLayer->active = zero;
    state->spriteLayer->param2 = 8;
    state->spriteLayer->param3 = 1;
    state->spriteLayer->gfxIndex = gEffectGfxTable[state->kind].gfxIndex;
    state->spriteLayer->anim0 = gKind87EffectAffineParams[0];
    state->spriteLayer->anim1 = gKind87EffectAffineParams[1];
    state->spriteLayer->anim2 = gKind87EffectAffineParams[2];
    state->spriteLayer->anim3 = gKind87EffectAffineParams[3];
    state->spriteLayer->palette = gEffectGfxTable[state->kind].palette;
    state->spriteLayer->object = (u32)sprite;
    state->spriteLayer->timer = zero;
    spriteAttr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(camera + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(camera + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    effectData = (u8 *)state + 0x48;
    *(u32 *)(effectData + 0) = (u32)state->worldX;
    *(u32 *)(effectData + 4) = (u32)state->worldY;
    *(u32 *)(effectData + 0x10) = (u32)((s32)entity->effectParam * 12 + (s32)gKind87EffectParamTable);
    setAnimationFrame(sprite, gfxInit, 0x1A, 0x00);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) = zero;
    callbackPtr = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    scriptEntry = (u8 *)entity + 0x18;
    sub_080C31E4(scriptEntry, (u8 *)entity + 0x22, *callbackPtr);
    ++*(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19);
    scriptEntry += 2 * entity->scriptStep;
    sub_080C31E0((u8 *)entity, *(s32 *)(*(u32 *)((u8 *)entity + 0x14) + (u32)*scriptEntry * 4));
}
