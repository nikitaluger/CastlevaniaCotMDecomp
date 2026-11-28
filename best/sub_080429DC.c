extern struct CC_KindTable gSpriteKindTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern void sub_08042FF8(void *);
extern s32 signOf(s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern u8 gSpriteAnimDataTable[];
extern s32 gMainObjTimerCallbacks[];
extern u16 gKindZeroLayerAttrs[];
struct RefSpawnLayer
{
  u8 unused;
  u8 kind;
  u8 subkind;
  u8 state;
  u16 gfxA;
  u16 affine0;
  u16 affine1;
  u16 affine2;
  u16 affine3;
  u16 palette;
  u32 sprite;
  u16 timer;
};
struct RefSpawnWork
{
  u8 _0[8];
  s32 x;
  s32 y;
  u32 velX;
  u32 f14;
  u32 frameIndex;
  s16 kind;
  u8 _1E[4];
  s16 slot;
  u32 updateFn;
  struct RefSpawnLayer *spriteLayer;
  u8 _2C[8];
  u8 anim[0x24];
};
struct RefSpawnThread
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x22 - 4];
  s16 stateIndex;
  u8 _24[0x38 - 0x24];
  u8 *sprite;
  struct RefSpawnWork *state;
  u8 _40[0x4C - 0x40];
  s16 f4C;
  u8 _4E[6];
  s16 f54;
  u8 _56[0xAC - 0x56];
  struct RefSpawnPositionHolder *refHolder;
};
struct RefSpawnMainWorkspace
{
  u8 _0[0x18A8];
  u8 frameCounter;
  u8 _18A9[0x19];
  u16 gfxFlag;
};
struct RefSpawnScrollState
{
  u8 _0[0x1278];
  u32 scrollX;
  u32 scrollY;
};
extern struct RefSpawnMainWorkspace gMainWorkspace;
extern struct RefSpawnScrollState gCameraState;
void sub_080429DC(struct RefSpawnThread *thread)
{
  u8 *__base_gSpriteAnimDataTable;
  u8 *sprite;
  struct RefSpawnWork *work;
  struct RefSpawnWork *newWork;
  u8 *anim;
  s32 slot;
  s32 __repair_phase_slot;
  u32 zero;
  u8 *camera;
  u8 *kindTable;
  s32 *callbackSlot;
  struct RefSpawnPositionHolder *refHolder;
  s16 refType;
  u16 upd1;
  refHolder = thread->refHolder;
  sprite = allocSpriteObject();
  work = NULL;
  slot = 0;
  __base_gSpriteAnimDataTable = gSpriteAnimDataTable;
  if ((((sprite == NULL) || ((thread->sprite = sprite, allocWorkSlot((u8 *) thread, 0, 0x4C, 0), newWork = thread->state, newWork == NULL))) || ((work = newWork, anim = ((u8 *) work) + 0x34, work->updateFn = *((u32 *) (((u8 *) thread) + 0x24)), *((u32 *) (((u8 *) thread) + 0x24)) = (u32) sub_08042FF8, refType = refHolder->ref->type, (  {
    switch (refType)
    {
      case 0x110:
        work->kind = 0x4D;
        break;

      case 0x111:
        work->kind = 0x83;
        break;

    }

    0;
  }
), kindTable = (u8 *) gSpriteKindTable, work->frameIndex = ((struct RefSpawnKindEntry *) kindTable)[work->kind].frame, work->x = refHolder->ref->value0 << 16, work->y = refHolder->ref->value1 << 16, slot = findKindIndex(work->kind), zero = 0, work->slot = slot, ((s32) (slot << 16)) < 0))) || ((initSpriteGraphics(sprite, anim, (work->kind * 0xC) + ((s32) __base_gSpriteAnimDataTable)), work->spriteLayer = (struct RefSpawnLayer *) allocEffectPart(), work->spriteLayer == NULL)))
  {
    do
    {
      _call_via_r1((u8 *) thread, *((s32 *) (((u8 *) thread) + 0x24)));
    }
    while (0);
    return;
  }
  work->spriteLayer->kind = 0;
  work->spriteLayer->subkind = 8;
  work->spriteLayer->state = 1;
  work->spriteLayer->gfxA = ((struct RefSpawnKindEntry *) kindTable)[work->kind].tile;
  work->spriteLayer->affine0 = gKindZeroLayerAttrs[0];
  work->spriteLayer->affine1 = gKindZeroLayerAttrs[1];
  work->spriteLayer->affine2 = gKindZeroLayerAttrs[2];
  work->spriteLayer->affine3 = gKindZeroLayerAttrs[3];
  work->spriteLayer->palette = ((struct RefSpawnKindEntry *) kindTable)[work->kind].mode;
  work->spriteLayer->sprite = (u32) sprite;
  do
  {
    work->spriteLayer->timer = zero;
    __repair_phase_slot = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) work) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) work) + 0x22))) + 8) << 12));
  }
  while (0);
  *((u16 *) sprite) = __repair_phase_slot;
  do
  {
    *((u16 *) sprite) = __repair_phase_slot | gMainWorkspace.gfxFlag;
  }
  while (0);
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  {
    u32 scrollOffset = 0x1278;
    *((u32 *) (sprite + 0x14)) = work->x - (((*((u32 *) (((camera = (u8 *) (&gCameraState)) + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 scrollOffset = 0x127C;
    *((u32 *) (sprite + 0x18)) = work->y - (((*((u32 *) ((camera + 0x127C) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  setAnimationFrame(sprite, anim, 0, 1);
  *((u16 *) (anim + 0x16)) = zero;
  if (((refHolder->ref->flags & 2) == 0) && ((refHolder->ref->flags & 1) != 0))
  {
    upd1 = *((u16 *) (sprite + 2));
    upd1 &= ~0x10;
    *((u16 *) (sprite + 2)) = upd1;
  }
  else
    if ((signOf(work->x) + 1) > (0 + 1))
  {
    *((u16 *) (sprite + 2)) |= 0x10;
  }
  else
  {
    *((u16 *) (sprite + 2)) &= ~0x10;
  }
  registerScriptObject((u8 *) thread, 0);
  thread->flags |= 0x1000;
  *((u8 *) ((((u8 *) thread) + (2 * thread->stateIndex)) + 0x19)) = 0;
  callbackSlot = (s32 *) gMainObjTimerCallbacks;
  _call_via_r2(((u8 *) thread) + 0x18, ((u8 *) thread) + 0x22, *callbackSlot);
  {
    u32 timerAddr = 2 * ((u32) thread->stateIndex);
    u8 *timerByte;
    timerAddr += (u32) thread;
    timerByte = (u8 *) timerAddr;
    *((u8 *) (timerByte + 0x19)) = (*((u8 *) (timerByte + 0x19))) + 1;
  }
  {
    u8 *stepByte = ((u8 *) thread) + 0x18;
    stepByte += thread->stateIndex * 2;
    do
    {
      do
      {
        _call_via_r1((u8 *) thread, *((s32 *) ((*((u8 **) (((u8 *) thread) + 0x14))) + ((*stepByte) * 4))));
      }
      while (0);
    }
    while (0);
  }
}

