/* Creates the sprite for a script-driven entity: allocate the render object and
 * its work state, install the animation selected by the owner's kind and frame
 * selector, place it in camera-relative screen space, then consume the current
 * script step and dispatch its handler. A failed allocation instead runs the
 * cleanup callback saved at owner+0x24. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
extern struct ScriptEntityWorkspace gMainWorkspace;
extern struct ScriptEntityCamera gCameraState;
extern u8 gSpriteAnimDataTable[];
extern s16 gScriptedSpriteFrameTable[];

void createScriptedEntitySprite(struct ScriptEntitySpriteOwner *owner) {
    u8 *sprite;
    struct ScriptEntitySpriteWork *work;
    u8 *animTrack;
    s32 kindSlot;
    u32 oamAttrs;
    u8 *camera;
    s32 *callbackEntry;
    s16 frameIndex;

    sprite = allocSpriteObject();
    work = NULL;
    animTrack = NULL;
    kindSlot = 0;
    if ((sprite == NULL) ||
        (owner->sprite = sprite, allocWorkSlot((u8 *)owner, 0, SCRIPT_ENTITY_SPRITE_WORK_SIZE, 0), work = owner->work, work == NULL) ||
        (animTrack = (u8 *)work + 0x34, work->kind = owner->kind,
         work->worldX = owner->spawnX << 16, work->worldY = owner->spawnY << 16,
         kindSlot = findKindIndex(work->kind), work->kindSlot = kindSlot, ((s32)(kindSlot << 16) < 0))) {
        _call_via_r1((u8 *)owner, *(s32 *)((u8 *)owner + 0x24));
        return;
    }
    initSpriteGraphics(sprite, animTrack, (s32)gSpriteAnimDataTable + work->kind * SCRIPT_ENTITY_ANIM_STRIDE);
    frameIndex = *(s16 *)((u8 *)owner + 0x7C);
    setAnimationFrame(sprite, animTrack, gScriptedSpriteFrameTable[frameIndex], 0);

    oamAttrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamAttrs;
    *(u16 *)sprite = oamAttrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = SCRIPT_ENTITY_SPRITE_GFX_ID;
    work->paramA = owner->paramA;
    work->paramB = owner->paramB;
    camera = (u8 *)&gCameraState;
    { u32 scrollOff = SCRIPT_ENTITY_SCROLL_X_OFFSET; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(camera + scrollOff + ((gMainWorkspace.frameCounter + 1) << SCRIPT_ENTITY_SCROLL_SHIFT)) + SCRIPT_ENTITY_BIAS_X) & SCRIPT_ENTITY_FRAC_MASK); }
    { u32 scrollOff = SCRIPT_ENTITY_SCROLL_Y_OFFSET; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(camera + scrollOff + ((gMainWorkspace.frameCounter + 1) << SCRIPT_ENTITY_SCROLL_SHIFT)) + SCRIPT_ENTITY_BIAS_Y) & SCRIPT_ENTITY_FRAC_MASK); }
    owner->flags |= SCRIPT_ENTITY_SPRITE_READY;
    *(u8 *)((u8 *)owner + 2 * owner->stepIndex + 0x19) = 0;
    callbackEntry = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    _call_via_r2((u8 *)owner + 0x18, (u8 *)owner + 0x22, *callbackEntry);
}
