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
  u8 _2C[0x1C];
  u32 auxState;
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
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 mapIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct S_02021E90 gCameraState;
struct AttrEntry { u16 attr0; s16 motion; u16 attr1; u8 _6[0x14-6]; };
extern struct AttrEntry gSpriteKindTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern s32 signOf(s32);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08029098(void);
extern u32 *gScriptStepCallbackTable;
extern u8 gSpriteAnimDataTable[];
extern u16 gKindZeroLayerAttrs[];

/* Builds a kind-0 sprite object: allocates its sprite and work state, fills one
 * render layer from the kind tables, places the sprite at the entity's own
 * coordinates with camera-relative scrolling, registers it as a script object,
 * then advances the entity's script. */
void initKindZeroSpriteObject(struct Entity *entity) {
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
    animSlot = 0;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x54, 0), gfxState = entity->gfxState, gfxState == NULL) ||
        (animState = (u8 *)gfxState + 0x34, gfxState->savedHandler = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = 0x08029099,
         gfxState->kind = 0, zero = 0, gfxState->velY = gSpriteKindTable[gfxState->kind].motion,
         gfxState->x = entity->posX << 16, gfxState->y = entity->posY << 16,
         animSlot = findKindIndex(gfxState->kind), gfxState->animSlot = (s16)animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + gfxState->kind * 0xC), spriteDef = allocEffectPart(), gfxState->spriteDef = spriteDef, spriteDef == NULL)) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    gfxState->spriteDef->type = (u8)zero;
    gfxState->spriteDef->layer = 8;
    gfxState->spriteDef->priority = 1;
    gfxState->spriteDef->attr0 = gSpriteKindTable[gfxState->kind].attr0;
    gfxState->spriteDef->attr1 = gKindZeroLayerAttrs[0];
    gfxState->spriteDef->attr2 = gKindZeroLayerAttrs[1];
    gfxState->spriteDef->attr3 = gKindZeroLayerAttrs[2];
    gfxState->spriteDef->attr4 = gKindZeroLayerAttrs[3];
    gfxState->spriteDef->attr5 = gSpriteKindTable[gfxState->kind].attr1;
    gfxState->spriteDef->sprite = (u32)sprite;
    gfxState->spriteDef->tail = (u16)zero;
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
        u32 *auxState = (u32 *)((u8 *)gfxState + 0x48);
        if (signOf(gfxState->x) > 0)
            *(u16 *)(sprite + 2) = (u16)(*(u16 *)(sprite + 2) | 0x10);
        auxState[0] = (u32)gfxState->x;
        auxState[1] = (u32)gfxState->y;
        auxState[2] = zero;
    }
    setAnimationFrame(sprite, animState, 0, 1);
    registerScriptObject((u8 *)entity, 0);
    entity->flags = (u16)(entity->flags | 0x1000);
    *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) = (u8)zero;
    {
        u8 *scriptData;
        u32 *timerTable;
        timerTable = (u32 *)0x08671BB0;
        scriptData = (u8 *)entity + 0x18;
        sub_080C31E4(scriptData, (u8 *)entity + 0x22, *timerTable);
        *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) = *(u8 *)((u8 *)entity + 2 * entity->scriptStep + 0x19) + 1;
        scriptData = scriptData + 2 * entity->scriptStep;
        sub_080C31E0((u8 *)entity, *(u32 *)(*(u32 *)((u8 *)entity + 0x14) + 4 * *(u8 *)scriptData));
    }
}
