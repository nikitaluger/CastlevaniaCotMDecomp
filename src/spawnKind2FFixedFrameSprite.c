/* Spawns the entity's kind-0x2F attack sprite: allocates its state block,
 * seeds a fixed animation from the entity's pose, places it in camera space,
 * marks the entity ready and dispatches its first script step. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
struct Actor
{
  u8 _0[8];
  s32 worldX;
  s32 worldY;
  s32 _10;
  s32 _14;
  u8 _18[4];
  s16 kind;
  u8 _1E[4];
  s16 slot;
};
struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x22 - 4];
  s16 stepIndex;
  u8 _24[0x38 - 0x24];
  u8 *sprite;
  struct Actor *state;
  u8 _40[0x4C - 0x40];
  s16 spawnX;
  u8 _4E[6];
  s16 spawnY;
  u8 _56[0x5C - 0x56];
  u16 variant;
  u8 _5E[0x6C - 0x5E];
  u32 extra;
};
struct CameraInfo
{
  u8 _0[0x18A8];
  u8 frameCounter;
  u8 _18A9[0x19];
  u16 attrMask;
};
extern struct CameraInfo gMainWorkspace;
struct CoordTable
{
  u8 _0[0x1278];
  u32 scrollX;
  u32 scrollY;
};
extern struct CoordTable gCameraState;
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;
void spawnKind2FFixedFrameSprite(struct Entity *entity)
{
  u8 *sprite;
  struct Actor *state;
  u8 *anim;
  s32 slot;
  u32 attrs;
  u8 *scrollBase;
  s32 *callback;
  sprite = allocSpriteObject();
  state = NULL;
  anim = NULL;
  slot = 0;
  if (((sprite == NULL) || ((entity->sprite = sprite, allocWorkSlot((u8 *) entity, 0, KIND2F_FIXED_WORK_SLOT, 0), state = entity->state, state == NULL))) || ((anim = ((u8 *) state) + 0x34, state->kind = SPRITE_KIND_RANDOM_ATTACK, state->worldX = entity->spawnX << 16, state->worldY = entity->spawnY << 16, slot = findKindIndex(SPRITE_KIND_RANDOM_ATTACK), state->slot = slot, ((s32) (slot << 16)) < 0)))
  {
 do { _call_via_r1((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24))); } while (0);
    return;
  }
  initSpriteGraphics(sprite, anim, ((s32) gSpriteAnimDataTable) + (state->kind * 0xC));
  setAnimationFrame(sprite, anim, KIND2F_FIXED_ANIM_FRAME, 0);
  attrs = ((*((u16 *) sprite)) & KIND2F_FIXED_ATTR_MASK) | ((((*((s16 *) (((u8 *) state) + 0x22))) << 6) + KIND2F_FIXED_ATTR_BIAS) | (((*((u16 *) (((u8 *) state) + 0x22))) + KIND2F_FIXED_FRAME_BIAS) << 12));
  *((u16 *) sprite) = attrs;
  *((u16 *) sprite) = attrs | gMainWorkspace.attrMask;
  *((u32 *) (sprite + 0x1C)) = KIND2F_FIXED_GFX_ID;
  if (entity->variant & 1)
  {
    *((u16 *) (sprite + 2)) |= SPRITE_OAM_FLIP_X;
  }
  scrollBase = (u8 *) (&gCameraState);
  {
    u32 scrollOffset = KIND2F_FIXED_SCROLL_X;
    *((u32 *) (sprite + 0x14)) = state->worldX - (((*((u32 *) ((scrollBase + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)))) + KIND2F_FIXED_SCROLL_BIAS_X) & KIND2F_FIXED_FRAC_MASK);
  }
  {
    u32 scrollOffset = KIND2F_FIXED_SCROLL_Y;
    *((u32 *) (sprite + 0x18)) = state->worldY - (((*((u32 *) ((scrollBase + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)))) + KIND2F_FIXED_SCROLL_BIAS_Y) & KIND2F_FIXED_FRAC_MASK);
  }
  entity->flags |= EFFECT_SPRITE_READY;
  *((u8 *) ((((u8 *) entity) + (2 * entity->stepIndex)) + 0x19)) = 0;
  callback = (s32 *) MAIN_OBJ_TIMER_CALLBACK_TABLE;
  _call_via_r2(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, *callback);
}
