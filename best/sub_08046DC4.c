extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void updateScriptedEffectObject(void);
extern s32 scaleByRandom(s32);
extern s32 nextRandomWord(void);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, u32);
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern struct ScriptedEffectKindEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
inline static u8 *inline_fn(u8 *arg0)
{
  return arg0 + 0x1278;
}

void sub_08046DC4(u8 *entity)
{
  struct ScriptedEffectWork *work;
  u8 *sprite;
  u8 *gfxInit;
  u8 *variantPtr;
  u8 *kindTable;
  struct ScriptedEffectLayer *layer;
  u32 *scriptOps;
  u8 *scriptSlots;
  u8 *stepBytePtr;
  u8 *__repair_phase_stepBytePtr;
  s32 zeroByte;
  s32 slot;
  u32 spriteAttr;
  u16 flags;
  u32 scrollIdx;
  u32 scrollIdx_w1;
  u32 __repair_phase_scrollIdx;
  u8 opcode;
  void *handler;
  s32 randVal;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));

    return;
  }
  *((void **) (entity + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((u32 *) (entity + 0x3C))) == 0)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));

    return;
  }
  *((u32 *) (sprite + 0x1C)) = MULTI_PART_SPRITE_GFX_ID;
  work = *((struct ScriptedEffectWork **) (entity + 0x3C));
  gfxInit = ((u8 *) work) + 0x34;
  installUpdateHandler(entity, (u8 *) work, (void *) updateScriptedEffectObject);
  kindTable = (u8 *) 0x080CF84C;
  variantPtr = entity + 0x4C;
  work->kind = *((u32 *) (kindTable + ((*variantPtr) * 4)));
  work->worldX = *((s32 *) (entity + 0x5C));
  work->worldY = *((s32 *) (entity + 0x6C));
  randVal = scaleByRandom(0xC000) + 0x4000;
  work->radiusA = ((s8) entity[0x7C]) * randVal;
  work->radiusB = -(scaleByRandom(0x28000) + 0x28000);
  slot = findKindIndex(work->kind);
  work->animSlot = slot;
  if ((slot << 16) < 0)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));

    return;
  }
  spriteAttr = (((s32) work->animSlot) << 6) + 0x200;
  scrollIdx = (slot + 8) << 12; spriteAttr |= scrollIdx;
  *((u16 *) sprite) = spriteAttr;
  {
    u8 *workspace = gMainWorkspace;
    workspace += 0x18C2;
    *((u16 *) sprite) |= *((u16 *) workspace);
  }
  if (nextRandomWord() & 1)
  {
    *((u16 *) (sprite + 2)) |= 0x10;
  }
  else
  {
    *((u16 *) (sprite + 2)) &= 0xFFEF;
  }
  initSpriteGraphics(sprite, ((u8 *) work) + 0x34, ((s32) gSpriteAnimDataTable) + (work->kind * 12));
  {
    u8 *frameAttrs = (u8 *) 0x080CF8A8;
    setAnimationFrame(sprite, gfxInit, *((s16 *) (frameAttrs + (entity[0x90] * 2))), 0);
  }
  layer = allocEffectPart();
  work->layer = layer;
  if (layer == NULL)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));

    return;
  }
  goto body;
  body:
  layer->kind = 5;

  work->layer->layer = 8;
  work->layer->priority = 1;
  {
    zeroByte = 0;
    work->layer->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    {
      u16 *attrs = (u16 *) 0x080CF8A8;
      work->layer->anim0 = attrs[0];
      work->layer->anim1 = attrs[1];
      work->layer->anim2 = attrs[2];
      work->layer->anim3 = attrs[3];
    }
    work->layer->palette = gEffectGfxTable[work->kind].palette;
  }
  work->layer->object = (u32) sprite;
  {
    u8 *camera = gCameraState;
    u8 *workspace = gMainWorkspace;
    workspace += 0x18A8;
    scrollIdx_w1 = (((u32) (*workspace)) + 1) * 0x40;
    *((u32 *) (sprite + 0x14)) = work->worldX - (((*((u32 *) (inline_fn(camera) + scrollIdx_w1))) + 0x8000) & 0xFFFF0000);
    __repair_phase_scrollIdx = (((u32) (*workspace)) + 1) * 0x40;
    *((u32 *) (sprite + 0x18)) = work->worldY - (((*((u32 *) ((gCameraState + 0x127C) + __repair_phase_scrollIdx))) + 0xFFFF8000) & 0xFFFF0000);
  }
  *((u16 *) (entity + 2)) |= 0x1000;
  *((u8 *) ((((u32) ((*((s16 *) (entity + 0x22))) * 2)) + ((u32) entity)) + 0x19)) = (u8) zeroByte;
  scriptOps = (u32 *) 0x08671BB0;
  scriptSlots = entity + 0x18;
  _call_via_r2(scriptSlots, entity + 0x22, *scriptOps);
  {
    __repair_phase_stepBytePtr = (u8 *) ((((u32) ((*((s16 *) (entity + 0x22))) * 2)) + ((u32) entity)) + 0x19);
    *__repair_phase_stepBytePtr = (u8) ((*__repair_phase_stepBytePtr) + 1);
    stepBytePtr = scriptSlots;
    stepBytePtr += (*((s16 *) (entity + 0x22))) * 2;
    opcode = *stepBytePtr;
    handler = ((void **) (*((void **) (entity + 0x14))))[opcode];
    _call_via_r1(entity, handler);
  }
}

