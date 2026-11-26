struct SpriteLayer
{
  u8 _0;
  u8 type;
  u8 layer;
  u8 priority;
  u16 attr0;
  u16 attr1;
  u16 attr2;
  u16 attr3;
  u16 attr4;
  u16 attr5;
  u32 sprite;
  u16 tail;
};
struct GfxState
{
  u8 _0[8];
  s32 x;
  s32 y;
  u32 z;
  u32 velX;
  u32 velY;
  s16 kind;
  u8 _1E[4];
  s16 animSlot;
  u32 savedHandler;
  struct SpriteLayer *spriteDef;
};
struct SpawnParams
{
  u8 _0[4];
  s16 *coords;
};
struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x22-4];
  s16 scriptStep;
  u8 _24[0x38-0x24];
  u8 *sprite;
  struct GfxState *gfxState;
  u8 _40[0x4C-0x40];
  s16 posX;
  u8 _4E[6];
  s16 posY;
  u8 _56[0x6C-0x56];
  u16 flipFlag;
  u8 _6E[0xAC-0x6E];
  struct SpawnParams *spawnParams;
};
struct GameState { u8 _0[0x18A8]; u8 mapIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GameState gMainWorkspace;
struct ScrollState { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollState gCameraState;
struct AttrEntry { u16 attr0; s16 motion; u16 attr1; u8 _6[0x14-6]; };
extern struct AttrEntry gSpriteKindTable[];
extern u16 gKind5ELayerAttrs[];
struct AuxState { u32 worldY; u32 unused; u32 flip; };
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern s32 signOf(s32);
extern void setSpriteFlip(u8 *, u32);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 *gMainObjTimerCallback;
extern u8 gSpriteAnimDataTable[];

/* Builds a kind-0x5E sprite from the entity's spawn parameters: allocates its
 * sprite and work state, fills one render layer, places it against the camera
 * scroll, sets its flip from its world X, registers it as a script object, then
 * advances the entity's script. */
void spawnKind5ESpriteFromParams(struct Entity *entity) {
    struct SpawnParams *spawn = entity->spawnParams;
    u8 *sprite;
    struct GfxState *gfxState;
    u8 *animState;
    struct SpriteLayer *spriteDef;
    s32 animSlot;
    u32 zero;
    u8 *camera;

    sprite = allocSpriteObject();
    gfxState = NULL;
    spriteDef = NULL;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x58, 0), gfxState = entity->gfxState, gfxState == NULL) ||
        (animState = (u8 *)gfxState + 0x34, gfxState->savedHandler = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = 0x0804F645,
         zero = 0,
         gfxState->kind = SPRITE_KIND_SPAWN_PARAM,
         gfxState->velY = gSpriteKindTable[gfxState->kind].motion,
         gfxState->x = spawn->coords[0] << 16, gfxState->y = spawn->coords[1] << 16,
         animSlot = findKindIndex(SPRITE_KIND_SPAWN_PARAM), gfxState->animSlot = animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + gfxState->kind * 0xC), spriteDef = allocEffectPart(), gfxState->spriteDef = (struct SpriteLayer *)spriteDef, spriteDef == NULL)) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    gfxState->spriteDef->type = zero;
    gfxState->spriteDef->layer = 8;
    gfxState->spriteDef->priority = 1;
    gfxState->spriteDef->attr0 = gSpriteKindTable[gfxState->kind].attr0;
    gfxState->spriteDef->attr1 = gKind5ELayerAttrs[0];
    gfxState->spriteDef->attr2 = gKind5ELayerAttrs[1];
    gfxState->spriteDef->attr3 = gKind5ELayerAttrs[2];
    gfxState->spriteDef->attr4 = gKind5ELayerAttrs[3];
    gfxState->spriteDef->attr5 = gSpriteKindTable[gfxState->kind].attr1;
    gfxState->spriteDef->sprite = (u32)sprite;
    gfxState->spriteDef->tail = zero;
    {
        s32 spriteAttr = (*(u16 *)sprite & 0xC00) |
                (((*(s16 *)((u8 *)gfxState + 0x22) << 6) + 0x200) |
                 ((*(u16 *)((u8 *)gfxState + 0x22) + 8) << 12));
        *(u16 *)sprite = spriteAttr;
        *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlag;
    }
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 offset = 0x1278; *(u32 *)(sprite + 0x14) = gfxState->x - ((*(u32 *)(camera + offset + ((gMainWorkspace.mapIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(sprite + 0x18) = gfxState->y - ((*(u32 *)(camera + offset + ((gMainWorkspace.mapIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    {
        struct AuxState *auxState = (struct AuxState *)((u8 *)gfxState + 0x48);
        auxState->worldY = gfxState->y;
        auxState->unused = zero;
        auxState->flip = signOf(gfxState->x) > 0 ? 0 : 0x8000;
        setAnimationFrame(sprite, animState, 0, 1);
        setSpriteFlip(sprite, auxState->flip);
    }
    registerScriptObject((u8 *)entity, 0);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) = zero;
    {
        u8 *scriptData;
        s32 *timerTable;
        timerTable = (s32 *)0x08671BB0;
        scriptData = (u8 *)entity + 0x18;
        sub_080C31E4(scriptData, (u8 *)entity + 0x22, *timerTable);
        *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) = *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) + 1;
        scriptData = scriptData + 2 * entity->scriptStep;
        sub_080C31E0((u8 *)entity, *(u32 *)(*(u32 *)((u8 *)entity + 0x14) + 4 * *(u8 *)scriptData));
    }
}
