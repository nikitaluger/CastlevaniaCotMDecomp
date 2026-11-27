extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern s32 isOutsideCameraBounds(s32, s32);
extern void sub_080227D4(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, s32, s32, s32);
extern u32 scaleByRandom(u32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gScriptEventCallbacks[];
struct Update22470LayerFlags { u8 pad; u8 flags; };
struct Update22470StateFlags { u16 flags; };

void updateDirectionalMultiPartProjectile(u8 *entity)
{
  s32 sprite;
  u8 *state;
  u8 *gfxInit;
  u8 *parts;
  u8 *layer;
  s32 stepOffset;
  u8 *script;
  u8 command;
  u8 *cameraBase;
  u32 scrollOffset;
  u32 *callback;
  s16 stepIndex;
  u16 *stepWords;
  sprite = *((s32 *) (entity + 0x38));
  state = *((u8 **) (entity + 0x3C));
  gfxInit = state + 0x34;
  parts = state + 0x48;
  layer = *((u8 **) (state + 0x28));
  ((struct Update22470LayerFlags *) layer)->flags |= 1;
  ((struct Update22470LayerFlags *) (*((u8 **) (parts + 0x34))))->flags |= 1;
  ((struct Update22470LayerFlags *) (*((u8 **) (parts + 0x38))))->flags |= 1;
  if ((*((s16 *) parts) == 1) && (isOutsideCameraBounds(*((s32 *) (state + 8)), *((s32 *) (state + 0xC))) == 1))
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));
    return;
  }
  if ((*((u16 *) (entity + 0x6C)) & 2) != 0)
    ((struct Update22470StateFlags *) state)->flags |= 1;
  if ((1 & ((struct Update22470StateFlags *) state)->flags) != 0)
  {
    ((struct Update22470LayerFlags *) (*((u8 **) (state + 0x28))))->flags = 0;
    ((struct Update22470LayerFlags *) (*((u8 **) (parts + 0x34))))->flags = 0;
    ((struct Update22470LayerFlags *) (*((u8 **) (parts + 0x38))))->flags = 0;
    if ((*((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1A))) != 2)
    {
      *((s32 *) (parts + 4)) = 0x16C1;
      *((s32 *) (state + 0x10)) = 0;
      *((s32 *) (state + 0x14)) = scaleByRandom(0x10001) + 0x8000;
      *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1B)) = 0;
      callback = gScriptEventCallbacks;
      sub_080C31E8(entity + 0x18, entity + 0x22, 2, *callback);
    }
  }
  if (updateObjectDisplayState(sprite, state) == 0)
  {
    *((void **) (entity + 0x14)) = (void *) 0x0866D878;
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) + 1);
    stepIndex = *((s16 *) (entity + 0x22));
    stepWords = (u16 *) entity;
    ((u8 *) (&stepWords[stepIndex]))[0x19] = ((u8 *) (&stepWords[stepIndex]))[0x19] + 1;
    stepOffset = (*((s16 *) (entity + 0x22))) * 2;
    script = entity + 0x18;
    command = script[stepOffset];
    sub_080C31E0(entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (command * 4))));
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) - 1);
    if (((*((u16 *) (entity + 2)) & 0x8000) != 0))
      goto done;
    if ((1 & ((struct Update22470StateFlags *) state)->flags) == 0)
      stepAnimationTrack(sprite, gfxInit);
    advanceMotion(state, *((s32 *) (parts + 4)));
  }
  sub_080227D4(entity, sprite);
  {
    u8 *layerBase;
    u8 *base1;
    u8 *base2;
    u32 idx;
    cameraBase = gCameraState;
    layerBase = gMainWorkspace;
    layerBase += 0x18A8;
    idx = ((u32) *layerBase + 1) * 0x40;
    base1 = cameraBase + 0x1278;
    *((u32 *) (sprite + 0x14)) = *((u32 *) (state + 0x08)) - ((*((u32 *) (base1 + idx)) + 0x8000) & 0xFFFF0000);
    idx = ((u32) *layerBase + 1) * 0x40;
    base2 = cameraBase + 0x127C;
    *((u32 *) (sprite + 0x18)) = *((u32 *) (state + 0x0C)) - ((*((u32 *) (base2 + idx)) + 0xFFFF8000) & 0xFFFF0000);
  }
done:
  ;
}
