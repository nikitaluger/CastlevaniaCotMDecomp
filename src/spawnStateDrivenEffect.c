extern u16 gStateEffectAffineParams[];
/* Spawns a state-selected attack/effect entity: allocates the sprite and its descriptor,
 * sets its animation, world position and sprite attributes, then advances the parent's
 * state index and calls the parent's state callback. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_08032290(void);
extern void sub_080322B0(u8 *, void *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, void *);

extern struct ScriptedEffectWorkspace gMainWorkspace;
extern struct ScriptedEffectScroll gCameraState;
extern struct StateDrivenEffectKindEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern void *gMainObjTimerCallback;

void spawnStateDrivenEffect(struct StateDrivenEffectEntity *entity) {
    u8 *sprite;
    struct AttackEffectWork *work;
    u8 *gfxInit;
    u8 *spriteDefPtr;
    s32 animSlot;
    u32 attrs;
    u32 zero;
    u32 one;
    u8 *camera;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x48, 0);
    work = entity->state;
    if (work == NULL) goto fail;
    gfxInit = (u8 *)work + 0x34;
    work->updateFn = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_08032290;
    work->kind = entity->kind;
    zero = 0;
    one = 1;
    work->param = one;
    work->x = entity->spawnX << 16;
    work->y = entity->spawnY << 16;
    animSlot = findKindIndex(work->kind);
    work->slot = animSlot;
    if ((animSlot << 16) < 0) goto fail;
    initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    spriteDefPtr = allocEffectPart();
    work->spriteDef = (struct AttackEffectSpriteDef *)spriteDefPtr;
    if (spriteDefPtr == NULL) goto fail;
    goto body;
fail:
    sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
    return;
body:
    work->spriteDef->active = zero;
    work->spriteDef->param2 = 8;
    work->spriteDef->param3 = one;
    work->spriteDef->gfxA = gEffectGfxTable[work->kind].gfxA;
    work->spriteDef->affine0 = gStateEffectAffineParams[0];
    work->spriteDef->affine1 = gStateEffectAffineParams[1];
    work->spriteDef->affine2 = gStateEffectAffineParams[2];
    work->spriteDef->affine3 = gStateEffectAffineParams[3];
    work->spriteDef->gfxB = gEffectGfxTable[work->kind].gfxB;
    work->spriteDef->sprite = (u32)sprite;
    work->spriteDef->timer = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = MULTI_PART_SPRITE_GFX_ID;
    camera = (u8 *)&gCameraState;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(camera + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(camera + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)(sprite + 0x28) = EFFECT_SPRITE_STATE_INITIAL;
    if (entity->direction > 0) *(u16 *)(sprite + 2) |= SPRITE_OAM_FLIP_X;
    sub_080322B0(sprite, (u8 *)work);
    entity->flags |= THREAD_FLAG_WAIT_SPRITE;
    *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = zero;
    {
        void **callbackTable = &gMainObjTimerCallback;
        u8 *cmdPtr = (u8 *)entity + 0x18;
        sub_080C31E4(cmdPtr, (u8 *)entity + 0x22, *callbackTable);
        {
            u8 *stateBytePtr = (u8 *)(*(s16 *)((u8 *)entity + 0x22) * 2);
            u8 *scriptBytePtr = cmdPtr;
            u8 scriptIndex;
            void *callback;
            stateBytePtr += (u32)entity;
            stateBytePtr[0x19]++;
            scriptBytePtr += *(s16 *)((u8 *)entity + 0x22) * 2;
            scriptIndex = *scriptBytePtr;
            callback = ((void **)*(void **)((u8 *)entity + 0x14))[scriptIndex];
            sub_080C31E0((u8 *)entity, callback);
        }
    }
}
