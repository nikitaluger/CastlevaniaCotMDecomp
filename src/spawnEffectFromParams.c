extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void sub_0805D90C(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

/* Render layer allocated by allocEffectPart and hung off the effect's work state. */
struct EffectGfx {
    u8 mode;          /* 0x00: playback mode */
    u8 renderKind;    /* 0x01 */
    u8 layer;         /* 0x02 */
    u8 priority;      /* 0x03 */
    u16 gfxIndex;     /* 0x04: tile id */
    u16 affine0;      /* 0x06 */
    u16 affine1;      /* 0x08 */
    u16 affine2;      /* 0x0A */
    u16 affine3;      /* 0x0C */
    u16 palette;      /* 0x0E */
    u32 sprite;       /* 0x10: allocated sprite object */
    u16 tail;         /* 0x14 */
};
/* Effect work state stored in the entity's slot at +0x3C. */
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;
    s32 worldY;
    u32 radiusA;
    u32 radiusB;
    u32 spawning;
    s16 kind;
    u8 _1E[4];
    s16 animSlot;
    u32 updateCb;
    struct EffectGfx *gfx;
    u8 _2C[0x48 - 0x2C];
    u32 ext;
};
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22 - 4];
    s16 index;
    u8 _24[0x38 - 0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 _40[0x4C - 0x40];
    s32 worldX;
    s32 worldY;
    u8 _54[0x6C - 0x54];
    u16 kind;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable gCameraState;
extern s16 gParamEffectAnimFrames[];
extern u8 gParamEffectAnimData[];

/* Spawn a graphics effect from a script entity's parameter block at +0x4C: its
 * world coordinates and low nibble select the animation frame, then a static
 * descriptor and extension layout are installed before the script is resumed. */
void spawnEffectFromParams(struct MainObj *entity)
{
    u8 *params;
    u8 *sprite;
    struct OwnerEffect *work;
    u8 *animState;
    short two;
    u8 *layer;
    u8 *ext;
    u32 zero;
    u8 *gameState;
    u8 *scrollRows;
    u8 *scriptPtr;
    s32 *timerCallbackWord;

    params = ((u8 *)entity) + 0x4C;
    sprite = allocSpriteObject();
    work = NULL;
    layer = NULL;
    animState = NULL;
    if (((sprite == NULL) || ((entity->object = sprite, allocWorkSlot((u8 *)entity, 0, PARAM_EFFECT_WORK_SLOT, 0), work = entity->effect, work == NULL))) || ((animState = ((u8 *)work) + 0x34, work->updateCb = *((u32 *)(((u8 *)entity) + 0x24)), *((u32 *)(((u8 *)entity) + 0x24)) = (u32)sub_0805D90C, work->spawning = 1, work->worldX = entity->worldX, work->worldY = *((s32 *)(params + 4)), initSpriteGraphics(sprite, animState, (s32)gParamEffectAnimData), setAnimationFrame(sprite, animState, gParamEffectAnimFrames[(*((u16 *)(params + 8))) & PARAM_EFFECT_VARIANT_MASK], 1), layer = allocEffectPart(), work->gfx = (struct EffectGfx *)layer, layer == NULL)))
    {
        sub_080C31E0((u8 *)entity, *((s32 *)(((u8 *)entity) + 0x24)));
        return;
    }
    zero = 0;
    ((struct EffectGfx *)layer)->renderKind = PARAM_EFFECT_TYPE;
    work->gfx->layer = PARAM_EFFECT_LAYER;
    work->gfx->priority = zero;
    work->gfx->gfxIndex = zero;
    work->gfx->affine0 = 5;
    work->gfx->affine1 = 5;
    work->gfx->affine2 = zero;
    work->gfx->affine3 = PARAM_EFFECT_ANIM3;
    work->gfx->palette = zero;
    two = 2;
    work->gfx->sprite = (u32)sprite;
    work->gfx->tail = zero;
    *((u16 *)sprite) |= gMainWorkspace.flags;
    *((u32 *)(sprite + 0x1C)) = PARAM_EFFECT_GFX_ID;
    gameState = (u8 *)(&gMainWorkspace);
    scrollRows = (u8 *)(&gCameraState);
    {
        u32 k = BEHAVIOR_SCROLL_X_OFFSET;
        *((u32 *)(sprite + 0x14)) = work->worldX - (((*((u32 *)((scrollRows + k) + (((*((u8 *)(gameState + BEHAVIOR_WORKSPACE_COUNTER))) + 1) << 6)))) + BEHAVIOR_SCROLL_BIAS_X) & BEHAVIOR_FRAC_MASK);
    }
    {
        u32 k = BEHAVIOR_SCROLL_Y_OFFSET;
        *((u32 *)(sprite + 0x18)) = work->worldY - (((*((u32 *)((scrollRows + k) + (((*((u8 *)(gameState + BEHAVIOR_WORKSPACE_COUNTER))) + 1) << 6)))) + BEHAVIOR_SCROLL_BIAS_Y) & BEHAVIOR_FRAC_MASK);
    }
    ext = ((u8 *)work) + 0x48;
    *((u32 *)(((u8 *)work) + 0x14)) = PARAM_EFFECT_FLAG_A;
    *((u32 *)(ext + 4)) = zero;
    ((u16 *)ext)[1] = 8;
    *((u16 *)ext) = PARAM_EFFECT_ATTR << two;
    *((u32 *)(ext + 8)) = PARAM_EFFECT_EXT_ID;
    if (((*((u16 *)(params + 8))) & PARAM_EFFECT_VARIANT_MASK) == PARAM_EFFECT_SPECIAL)
    {
        *((u32 *)(((u8 *)work) + 0x14)) = PARAM_EFFECT_FLAG_B;
        *((u32 *)(ext + 8)) = zero;
    }
    entity->flags |= EFFECT_SPRITE_READY;
    *((u8 *)((u8 *)entity + 0x19 + two * entity->index)) = zero;
    timerCallbackWord = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    scriptPtr = ((u8 *)entity) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)entity) + 0x22, *timerCallbackWord);
    *((u8 *)((u8 *)entity + 0x19 + 2 * entity->index)) = *((u8 *)((u8 *)entity + 0x19 + 2 * entity->index)) + 1;
    scriptPtr += entity->index * 2;
    sub_080C31E0((u8 *)entity, *((s32 *)((*((u32 *)(((u8 *)entity) + 0x14))) + (4 * (*scriptPtr)))));
}
