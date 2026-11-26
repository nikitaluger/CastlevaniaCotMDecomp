extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void sub_08014290(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
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
extern u16 D_080CF458[];
extern u8 gSpriteAnimDataTable[];
extern u32 D_080CF480[];
extern u32 D_080CF488[];

/* Create a scripted object's sprite and work block, choose its graphics from a
 * four-entry table, fill the single render part, position it against the scroll
 * table and run its entry script. */
void sub_080404C4(struct ScriptedObject *arg0)
{
  u32 gfxFlags[4];
  int index3;
  u32 hi;
  u32 lo;
  u8 *sprite;
  struct EffectWork *work;
  struct EffectWork *workCheck;
  u8 *animState;
  u8 *scratchPtr;
  int deadOffset;
  u16 *animTable;
  u8 *vtablePtr;
  s32 kindIndex;
  u32 gfxFlagsValue;
  u32 zero;
  s16 animId;
  s32 *scriptOps;
  u8 *statePtr;
  u8 *unusedBase;
  u32 *flagBase;
  u32 flagIndex;
  u8 variantByte;
  u8 *pt;
  u8 *pb;
  u8 *base1;
  u8 *base2;
  u32 idx;
  u8 opcode;
  hi = D_080CF480[1];
  lo = D_080CF480[0];
  gfxFlags[2] = lo;
  gfxFlags[3] = hi;
  hi = D_080CF488[1];
  lo = D_080CF488[0];
  gfxFlags[0] = lo;
  gfxFlags[1] = hi;
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
  scratchPtr = ((u8 *) arg0) + 0x7C;
  *((u32 *) (((u8 *) sprite) + 0x1C)) = gfxFlags[*((u8 *) scratchPtr)];
  work = arg0->work;
  animState = ((u8 *) work) + 0x34;
  installUpdateHandler((u8 *) arg0, (u8 *) work, (void *) sub_08014290);
  zero = 0;
  work->kind = 0x31;
  work->worldX = arg0->worldX;
  work->worldY = arg0->worldY;
  kindIndex = findKindIndex(0x31);
  work->slot = kindIndex;
  if (((s32) (kindIndex << 16)) < 0)
  {
    goto fail;
  }
  gfxFlagsValue = (((s32)work->slot) << 6) + 0x200;
  gfxFlagsValue |= (kindIndex + 8) << 12;
  *((u16 *) sprite) = gfxFlagsValue;
  statePtr = (u8 *) (&gMainWorkspace);
  *((u16 *) sprite) = gfxFlagsValue | (*((u16 *) (statePtr + 0x18C2)));
  initSpriteGraphics(sprite, animState, ((s32) gSpriteAnimDataTable) + (work->kind * 0xC));
  variantByte = *((u8 *) scratchPtr);
  flagIndex = variantByte * 4;
  flagBase = &gfxFlags[2];
  animId = *((s16 *) ((u32) flagIndex + (u32) flagBase));
  setAnimationFrame(sprite, animState, animId, 0);
  animTable = (u16 *) 0x080CF458;
  work->gfx = (struct EffectPart *) allocEffectPart();
  if (work->gfx != NULL)
  {
    goto main;
  }
  fail:
  _call_via_r1((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
  goto end;
  deadOffset = 0x127C;
  main:
  work->gfx->kind = 5;
  work->gfx->layer = zero;
  work->gfx->priority = zero;
  work->gfx->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->gfx->anim0 = animTable[0];
  work->gfx->anim1 = animTable[1];
  work->gfx->anim2 = animTable[2];
  work->gfx->anim3 = animTable[index3 = 3];
  work->gfx->palette = gEffectGfxTable[work->kind].palette;
  work->gfx->object = (u32) sprite;
  arg0->initialized = 1;
  {
    u8 *scrollTable = (u8 *) &gCameraState;
    u8 *globalPtr = (u8 *) &gMainWorkspace;
    u8 *scrollXBase;
    u8 *scrollYBase;
    u32 scrollIdx;
    globalPtr += 0x18A8;
    scrollIdx = ((u32)*globalPtr + 1) * 0x40;
    scrollXBase = scrollTable + 0x1278;
    *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(scrollXBase + scrollIdx) + 0x8000) & 0xFFFF0000);
    scrollIdx = ((u32)*globalPtr + 1) * 0x40;
    scrollYBase = scrollTable + 0x127C;
    *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(scrollYBase + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
  }
  arg0->flags |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = zero;
  scriptOps = (s32 *) 0x08671BB0;
  vtablePtr = ((u8 *) arg0) + 0x14;
  scratchPtr = ((u8 *) arg0) + 0x18;
  hi = 4;
  _call_via_r2(scratchPtr, ((u8 *) arg0) + 0x22, *scriptOps);
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) += 1;
  scratchPtr = scratchPtr + (2 * arg0->index);
  {
    u8 opcode = *((u8 *) scratchPtr);
    _call_via_r1((u8 *) arg0, *((u32 *) (*((u32 *) vtablePtr) + opcode * 4)));
  }
  end:
  ;
  ;
  ;
  ;
}
