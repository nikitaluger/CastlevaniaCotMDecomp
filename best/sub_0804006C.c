extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void sub_08014290(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *);

struct EffectPart
{
  u8 unk0;
  u8 kind;
  u8 layer;
  u8 priority;
  u16 gfxIndex;
  u16 anim0;
  u16 anim1;
  u16 anim2;
  u16 anim3;
  u16 palette;
  u32 object;
  u16 tail;
};
struct EffectWork
{
  u8 unk0[8];
  s32 worldX;
  s32 worldY;
  u32 radiusA;
  u32 radiusB;
  u32 state;
  s16 kind;
  u8 unk1E[4];
  s16 slot;
  u32 updateCb;
  struct EffectPart *gfx;
};
struct ScriptedObject
{
  u8 unk0[2];
  u16 flags;
  u8 unk4[0x22 - 4];
  s16 index;
  u8 unk24[0x38 - 0x24];
  u8 *sprite;
  struct EffectWork *work;
  u8 unk40[0x4C - 0x40];
  s32 worldX;
  u8 unk50[0x5C - 0x50];
  s32 worldY;
  u8 unk60[0x7C - 0x60];
  u8 variant;
  u8 unk7D[0x8C - 0x7D];
  u32 initialized;
};
struct GameState
{
  u8 unk0[0x18A8];
  u8 unk18A8;
  u8 unk18A9[0x19];
  u16 renderFlags;
};
extern struct GameState gMainWorkspace;
struct ScrollState
{
  u8 unk0[0x1278];
  u32 cameraX;
  u32 cameraY;
};
extern struct ScrollState gCameraState;
struct EffectTemplate
{
  u8 unk0[4];
  u16 gfxIndex;
  u16 palette;
  u8 unk8[0x28 - 8];
};
extern struct EffectTemplate gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 D_080CF460[];
extern u32 gMainObjTimerCallback;

void sub_0804006C(struct ScriptedObject *arg0)
{
  u8 *sprite;
  struct EffectWork *work;
  struct EffectWork *workCheck;
  u8 *animState;
  s32 kindIndex;
  u32 gfxFlagsValue;
  u32 zero;
  u16 *animTable;
  u8 *statePtr;
  u8 *globalPtr;
  u32 scrollIdx;
  u8 *scrollXBase;

  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  arg0->sprite = sprite;
  allocWorkSlot((u8 *) arg0, 0, 0x48, 0);
  workCheck = *((struct EffectWork * volatile *) (((u8 *) arg0) + 0x3C));
  if (workCheck == NULL)
  {
    goto fail;
  }
  *((u32 *) (((u8 *) sprite) + 0x1C)) = 0x8000000A;
  work = arg0->work;
  animState = ((u8 *) work) + 0x34;
  installUpdateHandler((u8 *) arg0, (u8 *) work, (void *) sub_08014290);
  zero = 0;
  work->kind = 0x30;
  work->worldX = arg0->worldX;
  work->worldY = arg0->worldY;
  kindIndex = findKindIndex(0x30);
  work->slot = kindIndex;
  if (((s32) (kindIndex << 16)) < 0)
  {
    goto fail;
  }
  gfxFlagsValue = (((s32) work->slot) << 6) + 0x200;
  gfxFlagsValue |= (kindIndex + 8) << 12;
  *((u16 *) sprite) = (u16) gfxFlagsValue;
  statePtr = (u8 *) (&gMainWorkspace);
  *((u16 *) sprite) = (u16) (gfxFlagsValue | *((u16 *) (statePtr + 0x18C2)));
  initSpriteGraphics(sprite, animState, (0x080CD400) + (work->kind * 0xC));
  setAnimationFrame(sprite, animState, 0x10, 0);
  animTable = (u16 *) D_080CF460;
  work->gfx = allocEffectPart();
  if (work->gfx != NULL)
  {
    goto main;
  }
fail:
  sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
  goto end;
main:
  work->gfx->kind = 5;
  work->gfx->layer = (u8) zero;
  work->gfx->priority = (u8) zero;
  work->gfx->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->gfx->anim0 = animTable[0];
  work->gfx->anim1 = animTable[1];
  work->gfx->anim2 = animTable[2];
  work->gfx->anim3 = animTable[3];
  work->gfx->palette = gEffectGfxTable[work->kind].palette;
  work->gfx->object = (u32) sprite;
  scrollXBase = (u8 *) (&gCameraState) + 0x1278;
  globalPtr = (u8 *) (&gMainWorkspace);
  globalPtr += 0x18A8;
  scrollIdx = ((u32) *globalPtr + 1) * 0x40;
  *((u32 *) (((u8 *) sprite) + 0x14)) = *((u32 *) (((u8 *) work) + 0x08)) - ((*((u32 *) (scrollXBase + scrollIdx)) + 0x8000) & 0xFFFF0000);
  scrollIdx = ((u32) *globalPtr + 1) * 0x40;
  animState = (u8 *) (&gCameraState) + 0x127C;
  *((u32 *) (((u8 *) sprite) + 0x18)) = *((u32 *) (((u8 *) work) + 0x0C)) - ((*((u32 *) (animState + scrollIdx)) + 0xFFFF8000) & 0xFFFF0000);
  arg0->flags |= 0x1000;
  *((u8 *) (((u8 *) arg0) + (2 * arg0->index) + 0x19)) = (u8) zero;
  sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22);
end:
  ;
}
