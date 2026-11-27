extern u16 gAnimatedEffectAffineParams[];
/* Spawn an animated effect sprite for an entity: allocate the sprite and its
 * work state, set the animation from the fixed tables, place the sprite against
 * the scrolling camera, optionally mirror it, then dispatch the next script step. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_0802D658(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct SpriteAttribs { u8 _0; u8 kind; u8 subPriority; u8 shape; u16 baseTile; u16 tile0; u16 tile1; u16 tile2; u16 tile3; u16 extra; u32 object; u16 timer; };
struct EntityState { u8 _0[8]; s32 x; s32 y; u32 _10; u32 _14; u32 active; s16 animId; u8 _1E[4]; s16 variant; u32 updateCallback; struct SpriteAttribs *attribs; u8 _2C[0x48-0x2C]; s32 lifetime; s32 counter; };
struct Entity {
    u8 _0[2];
    u16 flags;                  /* 0x02 */
    u8 _4[0x22-4];
    s16 step;                   /* 0x22 */
    u8 _24[0x38-0x24];
    u8 *sprite;                 /* 0x38 */
    struct EntityState *state;  /* 0x3C */
    u8 _40[0x4C-0x40];
    s16 spawnX;                 /* 0x4C */
    u8 _4E[6];
    s16 spawnY;                 /* 0x54 */
    u8 _56[0x5C-0x56];
    s16 direction;              /* 0x5C: > 0 mirrors the sprite */
    u8 _5E[0x6C-0x5E];
    u16 animId;                 /* 0x6C */
};
struct GlobalStateA { u8 _0[0x18A8]; u8 cameraIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA gMainWorkspace;
struct GlobalStateB { u8 _0[0x1278]; u32 coordX; u32 coordY; };
extern struct GlobalStateB gCameraState;
struct AnimTable { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x28-8]; };
extern struct AnimTable gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];

void spawnAnimatedEntityEffect(struct Entity *entity) {
    u8 *sprite;
    struct EntityState *work;
    u8 *anim;
    u8 *effectBytes;
    s32 animSlot;
    u32 oamAttr;
    u32 zero;
    u32 one;
    u8 *cameraBase;
    s32 *stepTable;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, ANIMATED_EFFECT_WORK_SLOT_SIZE, 0);
    work = entity->state;
    if (work == NULL) goto fail;
    anim = (u8 *)work + 0x34;
    work->updateCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0802D658;
    work->animId = entity->animId;
    zero = 0;
    one = 1;
    work->active = one;
    work->x = entity->spawnX << 16;
    work->y = entity->spawnY << 16;
    animSlot = findKindIndex(work->animId);
    work->variant = animSlot;
    if ((animSlot << 16) < 0) goto fail;
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->animId * 0xC);
    effectBytes = allocEffectPart();
    work->attribs = (struct SpriteAttribs *)effectBytes;
    if (effectBytes == NULL) goto fail;
    goto body;
fail:
    sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
    return;
body:
    work->attribs->kind = zero;
    work->attribs->subPriority = 8;
    work->attribs->shape = one;
    work->attribs->baseTile = gEffectGfxTable[work->animId].baseTile;
    work->attribs->tile0 = gAnimatedEffectAffineParams[0];
    work->attribs->tile1 = gAnimatedEffectAffineParams[1];
    work->attribs->tile2 = gAnimatedEffectAffineParams[2];
    work->attribs->tile3 = gAnimatedEffectAffineParams[3];
    work->attribs->extra = gEffectGfxTable[work->animId].extra;
    work->attribs->object = (u32)sprite;
    work->attribs->timer = zero;
    oamAttr = (*(u16 *)sprite & 0xC00) |
              (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
               ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamAttr;
    *(u16 *)sprite = oamAttr | gMainWorkspace.gfxFlag;
    *(u32 *)(sprite + 0x1C) = CHILD_SPRITE_GFX_ID;
    cameraBase = (u8 *)&gCameraState;
    { u32 scrollOffset = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOffset = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    if (entity->direction > 0) *(u16 *)(sprite + 2) |= SPRITE_OAM_FLIP_X;
    *(u16 *)(sprite + 0x28) = ANIMATED_EFFECT_ANIM_STEP;
    entity->flags |= CHILD_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->step + 0x19) = zero;
    stepTable = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *stepTable);
}
