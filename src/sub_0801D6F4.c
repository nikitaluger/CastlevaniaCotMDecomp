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
  u32 unk1C;
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
  u8 f18A8;
  u8 _1[0x19];
  u16 f18C2;
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
extern void *gMainObjTimerCallback;
extern void *D_08671BFC;
extern u8 gSpriteAnimDataTable[];

/* Builds an entity's graphics: allocates its sprite and state, sets the sprite
 * attributes and screen position, then updates the entity's child bookkeeping. */
void sub_0801D6F4(struct Entity *arg0)
{
  struct Sprite *sprite;
  struct GfxState *state;
  u8 *anim;
  s32 spriteIndex;
  u32 animRes;

  sprite = allocSpriteObject();
  if (((sprite == NULL) || ((arg0->sprite = (u32) sprite, allocWorkSlot(arg0, 0, 0x58, 0), (state = (struct GfxState *) arg0->gfxState) == NULL))) || ((anim = ((u8 *) state) + 0x34, state->spriteType = 0x87, state->x = (u32) (((s32) arg0->param1) << 16), state->y = (u32) (((s32) arg0->param2) << 16), spriteIndex = findKindIndex(0x87), state->attrIndex = spriteIndex, (spriteIndex << 16) < 0)))
  {
    sub_080C31E0(arg0, (void *) arg0->callback);
    return;
  }
  initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + state->spriteType * 12);
  {
    u32 posOff = 0x22;
    u32 baseAttr = *(u16 *)sprite & 0xC00;
    s32 tileX = (*(s16 *)((u8 *)state + posOff) << 6) + 0x200;
    u32 tileY = (*(u16 *)((u8 *)state + 0x22) + 8) << 12;
    sprite->attr = baseAttr | (tileX | tileY);
  }
  sprite->attr |= gMainWorkspace.f18C2;
  sprite->unk1C = 0x8000000A;
  {
    u8 *extra = ((u8 *) state) + 0x48;
    *((u32 *) extra) = state->x;
    *((u32 *) (extra + 4)) = state->y;
    animRes = arg0->animData;
    *((u32 *) (extra + 0xC)) = animRes;
    {
      s32 res = sub_080C31E0((void *) animRes, *((void **) 0x08671BFC));
      state->x = state->posX + (res << 4);
    }
    state->y = (*((u32 *) (extra + 4))) + (((s32) arg0->param3) << 16);
  }
  {
    u32 offset = 0x1278;
    u8 *coordBase = gCameraState;
    u32 adjX = *((u32 *) ((coordBase + offset) + ((gMainWorkspace.f18A8 + 1) << 6)));
    adjX = (adjX + 0x8000) & 0xFFFF0000;
    sprite->screenX = state->x - adjX;
  }
  {
    u32 offset = 0x127C;
    u8 *coordBase = gCameraState;
    u32 adjY = *((u32 *) ((coordBase + offset) + ((gMainWorkspace.f18A8 + 1) << 6)));
    adjY = adjY + 0xFFFF8000;
    adjY = adjY & 0xFFFF0000;
    sprite->screenY = state->y - adjY;
  }
  setAnimationFrame(sprite, anim, 0x1A, 0);
  arg0->flags |= 0x1000;
  {
    u8 *child = (u8 *) ((((u32) arg0->childIndex) * 2) + ((u32) arg0));
    child[0x19] = 0;
  }
  {
    void **table = &gMainObjTimerCallback;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, (s32) (*table));
  }
  {
    u8 *child = (u8 *) ((((u32) arg0->childIndex) * 2) + ((u32) arg0));
    child[0x19] = child[0x19] + 1;
  }
  {
    u8 *childArr = ((u8 *) arg0) + 0x18;
    s32 index = arg0->childIndex * 2;
    u8 value = *(childArr + index);
    sub_080C31E0(arg0, *((void **) (((u8 *) arg0->callbackTable) + (value * 4))));
  }
}
