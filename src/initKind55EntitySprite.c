struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  u32 callbackTable;
  u8 _18[0xA];
  s16 childIndex;
  u32 callback;
  u8 _28[0x10];
  u32 sprite;
  u32 gfxState;
  u8 _40[0xC];
  s16 param1;
  u8 _4E[6];
  s16 param2;
  u8 _56[6];
  s16 param3;
  u8 _5E[0xE];
  u32 animData;
};
struct Sprite
{
  u16 attr;
  u8 _02[0x12];
  u32 screenX;
  u32 screenY;
  u32 gfxId;
};
struct GfxState
{
  u8 _0[8];
  u32 x;
  u32 y;
  u8 _10[0xC];
  s16 spriteType;
  u8 _1E[4];
  s16 attrIndex;
  u8 _24[0x24];
  u32 posX;
  u32 posY;
  u8 _50[4];
  u32 f54;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 frameCounter;
  u8 _1[0x19];
  u16 gfxFlags;
};
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 findKindIndex(s32);
extern s32 sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gCameraState[];
extern struct S_02025FF0 gMainWorkspace;
extern void *gScriptStepCallbackTable;
extern void *gTrigFuncPtr;
extern u8 gSpriteAnimDataTable[];

/* Initializes an entity's kind-0x55 sprite: allocates its sprite and graphics
 * state, places it against the camera scroll, starts its animation, then
 * advances the entity's script callback. */
void initKind55EntitySprite(struct Entity *entity)
{
  struct Sprite *sprite;
  struct GfxState *state;
  u8 *gfxInit;
  s32 kindSlot;
  u32 animData;

  sprite = allocSpriteObject();
  if (((sprite == NULL) || ((entity->sprite = (u32) sprite, allocWorkSlot(entity, 0, 0x58, 0), (state = (struct GfxState *) entity->gfxState) == NULL))) || ((gfxInit = ((u8 *) state) + 0x34, state->spriteType = SPRITE_KIND_FIXED_EFFECT, state->x = (u32) (((s32) entity->param1) << 16), state->y = (u32) (((s32) entity->param2) << 16), kindSlot = findKindIndex(SPRITE_KIND_FIXED_EFFECT), state->attrIndex = kindSlot, (kindSlot << 16) < 0)))
  {
    sub_080C31E0(entity, (void *) entity->callback);
    return;
  }
  initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + state->spriteType * 12);
  {
    u32 coordOffset = 0x22;
    u32 baseAttrs = *(u16 *)sprite & 0xC00;
    s32 tileX = (*(s16 *)((u8 *)state + coordOffset) << 6) + 0x200;
    u32 tileY = (*(u16 *)((u8 *)state + 0x22) + 8) << 12;
    sprite->attr = baseAttrs | (tileX | tileY);
  }
  sprite->attr |= gMainWorkspace.gfxFlags;
  sprite->gfxId = EFFECT_SPRITE_GFX_ID;
  {
    u8 *worldPos = ((u8 *) state) + 0x48;
    *((u32 *) worldPos) = state->x;
    *((u32 *) (worldPos + 4)) = state->y;
    animData = entity->animData;
    *((u32 *) (worldPos + 0xC)) = animData;
    {
      s32 trigResult = sub_080C31E0((void *) animData, gTrigFuncPtr);
      state->x = state->posX + (trigResult << 4);
    }
    state->y = (*((u32 *) (worldPos + 4))) + (((s32) entity->param3) << 16);
  }
  {
    u32 scrollOffset = 0x1278;
    u8 *camera = gCameraState;
    u32 scrollX = *((u32 *) ((camera + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)));
    scrollX = (scrollX + 0x8000) & 0xFFFF0000;
    sprite->screenX = state->x - scrollX;
  }
  {
    u32 scrollOffset = 0x127C;
    u8 *camera = gCameraState;
    u32 scrollY = *((u32 *) ((camera + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)));
    scrollY = scrollY + 0xFFFF8000;
    scrollY = scrollY & 0xFFFF0000;
    sprite->screenY = state->y - scrollY;
  }
  setAnimationFrame(sprite, gfxInit, FIXED_EFFECT_ANIM_FRAME, 0);
  entity->flags |= EFFECT_SPRITE_READY;
  {
    u8 *scriptEntry = (u8 *) ((((u32) entity->childIndex) * 2) + ((u32) entity));
    scriptEntry[0x19] = 0;
  }
  {
    void **callbackTable = &gScriptStepCallbackTable;
    sub_080C31E4(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, (s32) (*callbackTable));
  }
  {
    u8 *scriptEntry = (u8 *) ((((u32) entity->childIndex) * 2) + ((u32) entity));
    scriptEntry[0x19] = scriptEntry[0x19] + 1;
  }
  {
    u8 *scriptSteps = ((u8 *) entity) + 0x18;
    s32 stepOffset = entity->childIndex * 2;
    u8 stepOpcode = *(scriptSteps + stepOffset);
    sub_080C31E0(entity, *((void **) (((u8 *) entity->callbackTable) + (stepOpcode * 4))));
  }
}
