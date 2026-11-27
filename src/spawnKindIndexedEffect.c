/* Spawns a kind-selected attack/effect entity: allocates the sprite and its descriptor,
 * copies the animation data, sets the world position from the coordinate tables, then
 * advances the parent's state index. */
struct EffectSpawnerEntity
{
  u8 _0[2];
  u16 flags;
  u8 _04[0x10];
  u32 indexTable;
  u8 _18[0xA];
  s16 stateIndex;
  u32 updateFn;
  u8 _28[0x10];
  u32 sprite;
  u32 state;
  u8 _40[0xC];
  u8 kindIndex;
  u8 _4D[0xF];
  u32 x;
  u8 _60[0xC];
  u32 y;
  u8 _70[0xC];
  u32 direction;
};
struct EffectSpawnerWork
{
  u8 _0[8];
  u32 x;
  u32 y;
  u32 direction;
  u8 _14[8];
  s16 kind;
  u8 _1E[4];
  u16 slot;
  u32 updateFn;
  u32 spriteDef;
  u8 _2C[8];
  u32 f34;
};
struct EffectSprite
{
  u16 attrs;
  u8 _02[0x12];
  u32 x;
  u32 y;
  u32 magic;
};
struct EffectSpriteLayer
{
  u8 f00;
  u8 f01;
  u8 f02;
  u8 f03;
  u16 f04;
  u16 f06;
  u16 f08;
  u16 f0A;
  u16 f0C;
  u16 f0E;
  u32 f10;
};
struct EffectGfxEntry
{
  u8 _pad[4];
  u16 gfxA;
  u16 gfxB;
  u8 _08[0x20];
};
void *allocSpriteObject(void);
void allocWorkSlot(void *, u32, u32, u32);
void installUpdateHandler(void *, void *, void *);
void sub_08014290(void);
u32 findKindIndex(s16);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, u32, u32);
void setSpriteFlipForDirection(void *, u32);
void *allocEffectPart(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
extern u8 gEffectGfxTable[];
extern u16 D_080CF55C[];
extern u8 gSpriteAnimDataTable[];
extern u32 gChildSpriteKindTable[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gScriptStepCallbackTable;
void spawnKindIndexedEffect(struct EffectSpawnerEntity *actor)
{
  struct EffectSprite *sprite;
  struct EffectSpawnerWork *state;
  u8 *scratchBuf;
  u8 *globalState;
  u8 *spriteCfg;
  u8 *spriteTable;
  u32 attrs;
  u32 slotIndex;
  s16 stateIndex;
  sprite = (struct EffectSprite *) allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  actor->sprite = (u32) sprite;
  allocWorkSlot(actor, 0, 0x48, 0);
  if (actor->state == 0)
  {
    goto fail;
  }
  sprite->magic = 0x80000009;
  state = (struct EffectSpawnerWork *) actor->state;
  scratchBuf = ((u8 *) state) + 0x34;
  installUpdateHandler(actor, state, &sub_08014290);
  state->kind = (s16) gChildSpriteKindTable[actor->kindIndex];
  state->x = actor->x;
  state->y = actor->y;
  state->direction = actor->direction;
  slotIndex = findKindIndex(state->kind);
  state->slot = (u16) slotIndex;
  if (((s16) ((u16) slotIndex)) < 0)
  {
    goto fail;
  }
  attrs = ((u32) (((s32) ((s16) state->slot)) << 6)) + (0x80 << 2);
  attrs |= (slotIndex + 8) << 12;
  sprite->attrs = (u16) attrs;
  globalState = gMainWorkspace;
  attrs |= *((u16 *) (globalState + 0x18C2));
  sprite->attrs = (u16) attrs;
  initSpriteGraphics(sprite, scratchBuf, (void *) (gSpriteAnimDataTable + (12 * ((s32) state->kind))));
  setAnimationFrame(sprite, scratchBuf, 0x13, 0);
  setSpriteFlipForDirection(sprite, state->direction);
  spriteCfg = (u8 *) D_080CF55C;
  state->spriteDef = (u32) allocEffectPart();
  if (state->spriteDef == 0)
  {
    goto fail;
  }
  goto cont;
  fail:
  sub_080C31E0(actor, actor->updateFn);

  return;
  cont:
  ((u8 *) state->spriteDef)[1] = 5;

  ((u8 *) state->spriteDef)[2] = 8;
  ((u8 *) state->spriteDef)[3] = 1;
  {
    u8 *defBytes = (u8 *) state->spriteDef;
    spriteTable = gEffectGfxTable;
    ((struct EffectSpriteLayer *) defBytes)->f04 = ((struct EffectGfxEntry *) (spriteTable + (((s32) state->kind) * 40)))->gfxA;
  }
  ((struct EffectSpriteLayer *) state->spriteDef)->f06 = *((u16 *) (&spriteCfg[0]));
  ((struct EffectSpriteLayer *) state->spriteDef)->f08 = *((u16 *) (&spriteCfg[2]));
  ((struct EffectSpriteLayer *) state->spriteDef)->f0A = *((u16 *) (&spriteCfg[4]));
  ((struct EffectSpriteLayer *) state->spriteDef)->f0C = *((u16 *) (&spriteCfg[6]));
  ((struct EffectSpriteLayer *) state->spriteDef)->f0E = ((struct EffectGfxEntry *) (spriteTable + (((s32) state->kind) * 40)))->gfxB;
  *((u32 *) (((u8 *) state->spriteDef) + 0x10)) = (u32) sprite;
  {
    u8 *coordTable = gCameraState;
    u8 *sceneState = gMainWorkspace;
    u8 *base1;
    u8 *base2c;
    u32 coordIndex;
    sceneState += 0x18A8;
    coordIndex = ((u32)*sceneState + 1) * 0x40;
    base1 = coordTable + 0x1278;
    sprite->x = state->x - ((*(u32 *)(base1 + coordIndex) + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*sceneState + 1) * 0x40;
    base2c = coordTable + 0x127C;
    sprite->y = state->y - ((*(u32 *)(base2c + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  actor->flags |= 0x1000;
  stateIndex = *((s16 *) (((u8 *) actor) + 0x22));
  *((((u8 *) actor) + (((s32) stateIndex) * 2)) + 0x19) = 0;
  {
    u32 *callbackTable = &gScriptStepCallbackTable;
    u8 *extra = ((u8 *) actor) + 0x18;
    u8 *stateIndexPtr = ((u8 *) actor) + 0x22;
    sub_080C31E4(extra, stateIndexPtr, *callbackTable);
    {
      s16 index2 = *((s16 *) stateIndexPtr);
      u8 *stateByte = (u8 *)((((s32) index2) * 2) + (u32) actor);
      stateByte[0x19] = (u8) (stateByte[0x19] + 1);
    }
    {
      s16 index3 = *((s16 *) stateIndexPtr);
      u8 *stateBytePtr = extra + (((s32) index3) * 2);
      sub_080C31E0(actor, *((u32 *) ((((u32) (*stateBytePtr)) * 4) + actor->indexTable)));
    }
  }
}
