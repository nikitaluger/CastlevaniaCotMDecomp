/* Spawn a kind-0x66 directional actor effect: allocate a sprite and render layer,
 * seed a fixed-point speed from the entity's facing byte, then advance the
 * current command-script step. Allocation failures call the fallback handler. */
struct GlobalFlags { u8 _0[0x18C2]; u16 flags; };
extern struct GlobalFlags gMainWorkspace;
struct EffectLayer {
  u8 _0;
  u8 active;
  u8 kind;
  u8 layer;
  u16 gfxA;
  u16 affine0;
  u16 affine1;
  u16 affine2;
  u16 affine3;
  s16 frame;
  u32 owner;
};
struct EffectWork {
  u8 _0[8];
  u32 x;
  u32 y;
  u32 speed;
  u32 unused14;
  u8 _18[4];
  u16 kind;
  u8 _1E[4];
  u16 animSlot;
  u8 _24[4];
  struct EffectLayer *layer;
};
struct FrameDef { u8 _0[0x20]; u16 gfxA; u16 gfxB; u8 _24[4]; };
struct ClearByte { u32 value; u8 byte; };
extern struct FrameDef gEffectGfxTable[];
extern u16 gKind66LayerParams[];
extern s32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void setSpriteFlipForDirection(void *, s32);
extern void initSharedSpriteGraphics(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void _call_via_r1(void *, u32);
extern void _call_via_r2(void *, void *, s32);
extern void updateActorEffectSubObject(void);
void spawnKind66DirectionalEffect(u8 *entity)
{
  u8 *sprite;
  struct EffectWork *work;
  u8 *animState;
  u16 *layerParams;
  u8 *scriptPtr;
  u8 *stepPtr;
  s32 *callbackTable;
  s32 direction;
  s32 speed;
  u8 *layer;
  u16 flags;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((u32 *) (entity + 0x38)) = (u32) sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((u32 *) (entity + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = 0x8000000B;
  work = (struct EffectWork *) (*((u32 *) (entity + 0x3C)));
  animState = ((u8 *) work) + 0x34;
  installUpdateHandler(entity, work, updateActorEffectSubObject);
  work->kind = 0x66;
  *((u16 *) sprite) |= gMainWorkspace.flags;
  work->x = *((u32 *) (entity + 0x4C));
  work->y = *((u32 *) (entity + 0x5C));
  direction = (s8) (*((s8 *) (entity + 0x6C)));
  speed = direction * 3;
  work->speed = speed << 16;
  if ((*((u8 *) (entity + 0x70))) == 1)
  {
    work->speed = -(speed << 16);
  }
  setSpriteFlipForDirection(sprite, -work->speed);
  initSharedSpriteGraphics(sprite, animState);
  setAnimationFrame(sprite, animState, 2, 1);
  layerParams = gKind66LayerParams;
  layer = allocEffectPart();
  *((void **) (((u8 *) work) + 0x28)) = layer;
  if (layer != NULL)
  {
    goto success;
  }
  fail:
  _call_via_r1(entity, *((u32 *) (entity + 0x24)));

  return;
  success:
  *((u8 *) (layer + 1)) = 1;

  *((u8 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 2)) = 8;
  *((u8 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 3)) = 1;
  *((u16 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 4)) = gEffectGfxTable[*((s16 *) (((u8 *) work) + 0x1C))].gfxA;
  *((u16 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 6)) = layerParams[0];
  *((u16 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 8)) = layerParams[1];
  *((u16 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 0xA)) = layerParams[2];
  *((u16 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 0xC)) = layerParams[3];
  *((u16 *) ((*((u8 **) (((u8 *) work) + 0x28))) + 0xE)) = gEffectGfxTable[*((s16 *) (((u8 *) work) + 0x1C))].gfxB;
  *((void **) ((*((u8 **) (((u8 *) work) + 0x28))) + 0x10)) = sprite;
  do
  {
    struct ClearByte clearByte = {0, 0};
    *((u16 *) (entity + 0x74)) = 0x20;
    *((u32 *) (entity + 0x7C)) = 0;
    flags = *((u16 *) (entity + 2));
    flags |= 0x1000;
    *((u16 *) (entity + 2)) = flags;
    *((u8 *) ((entity + (((u32) (*((s16 *) (entity + 0x22)))) * 2)) + 0x19)) = clearByte.byte;
    callbackTable = &gScriptStepCallbackTable;
    scriptPtr = entity + 0x18;
    _call_via_r2(scriptPtr, entity + 0x22, *callbackTable);
    *((u8 *) ((entity + (((u32) (*((s16 *) (entity + 0x22)))) * 2)) + 0x19)) = (*((u8 *) ((entity + (((u32) (*((s16 *) (entity + 0x22)))) * 2)) + 0x19))) + 1;
    stepPtr = scriptPtr + (((u32) (*((s16 *) (entity + 0x22)))) * 2);
    _call_via_r1(entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + ((*((u8 *) stepPtr)) * 4))));
  }
  while (0);
}
