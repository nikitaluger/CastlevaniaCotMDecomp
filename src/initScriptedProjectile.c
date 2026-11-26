extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void unregisterChildObject(u8 *);
extern void setAttackHitbox(u8 *, void *);
extern void releaseEntityState(void);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);

extern struct ScriptedEffectWorkspace gMainWorkspace;
extern struct ScriptedEffectScroll gCameraState;
extern struct ScriptedEffectKindEntry gEffectGfxTable[];
extern u16 gScriptedSpriteAffineParams[];
extern u8 gSpriteAnimDataTable[];

/* Allocates an entity's sprite, work block and render part for the simple
 * scripted projectile, initialises its graphics, position and attack hitbox,
 * then dispatches the script's next command. Allocation failures fall back to
 * the entity's previous handler. */
void initScriptedProjectile(struct ProjectileSpawnEntity *entity) {
    u8 *sprite;
    struct ScriptedEffectWork *work;
    u8 *animState;
    u8 *partPtr;
    s32 kindIndex;
    u32 gfxFlags;
    u32 zero;
    u32 one;
    u8 *scrollTable;
    s32 *scriptOps;

    sprite = allocSpriteObject();
    if (sprite == NULL) { unregisterChildObject((u8 *)entity); _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24)); return; }
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x48, 0);
    work = entity->work;
    if (work == NULL) { unregisterChildObject((u8 *)entity); _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24)); return; }
    animState = (u8 *)work + 0x34;
    work->updateCb = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)releaseEntityState;
    zero = 0;
    work->kind = SPRITE_KIND_PROJECTILE;
    one = 1;
    work->state = one;
    work->worldX = entity->spawnX << 16;
    work->worldY = entity->spawnY << 16;
    kindIndex = findKindIndex(SPRITE_KIND_PROJECTILE);
    work->animSlot = kindIndex;
    if ((s32)(kindIndex << 16) < 0) { _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24)); return; }
    initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    partPtr = allocEffectPart();
    work->layer = (struct ScriptedEffectLayer *)partPtr;
    if (partPtr == NULL) { _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24)); return; }

    work->layer->kind = zero;
    work->layer->layer = 8;
    work->layer->priority = one;
    work->layer->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->layer->anim0 = gScriptedSpriteAffineParams[0];
    work->layer->anim1 = gScriptedSpriteAffineParams[1];
    work->layer->anim2 = gScriptedSpriteAffineParams[2];
    work->layer->anim3 = gScriptedSpriteAffineParams[3];
    work->layer->palette = gEffectGfxTable[work->kind].palette;
    work->layer->object = (u32)sprite;
    work->layer->tail = zero;
    gfxFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = gfxFlags;
    *(u16 *)sprite = gfxFlags | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    scrollTable = (u8 *)&gCameraState;
    { u32 xOff = 0x1278; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(scrollTable + xOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 yOff = 0x127C; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(scrollTable + yOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)(sprite + 0x28) = 0x29;
    setAttackHitbox(sprite, work);
    entity->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = zero;
    scriptOps = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptOps);
}
