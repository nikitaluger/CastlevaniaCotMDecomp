extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_08013B5C(s32, void *);
extern s32 hitTestEntities(void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_08020498(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct StateFlags { u16 flags; };
struct LayerFlags { u8 _0; u8 flags; };
struct LayerTimer { u8 _0[0x14]; u16 flags; };
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gFixedKindEntityStateHandlers[];

/* Per-frame update for a fixed-kind entity sprite: refresh its layer and
 * display flags, handle a finished action, advance the animation and refresh
 * the sprite's screen position from the camera coordinate table. */
void updateFixedKindEntitySprite(u8 *entity)
{
  s32 sprite = *((s32 *) (entity + 0x38));
  u8 *work = *((u8 **) (entity + 0x3C));
  u8 *gfxInit = work + 0x34;
  u8 *parts = work + 0x48;
  u8 *layer;
  layer = *((u8 **) (work + 0x28));
  ((struct LayerFlags *) layer)->flags |= 5;
  if (*((s32 *)parts) <= 0)
  {
    if (sub_0805F9B4(*((s32 *) (work + 8)), *((s32 *) (work + 0xC))) == 1)
    {
      sub_080C31E0(entity, *((void **) (entity + 0x24)));
      return;
    }
  }
  if (hitTestEntities(*((void **) (work + 0x28))) != 0)
    ((struct StateFlags *) work)->flags |= 1;
  if ((1 & ((struct LayerTimer *) (*((u8 **) (work + 0x28))))->flags) || (*((u16 *) (entity + 0x5C)) & 2))
    ((struct StateFlags *) work)->flags |= 1;
  if (1 & (*((u16 *) work)))
  {
    s32 *callbacks;
    ((struct LayerFlags *) (*((u8 **) (work + 0x28))))->flags &= 0xFB;
    if ((*((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1A))) != 2)
    {
      *((s32 *) (parts + 8)) = 5;
      if (*((u16 *) (entity + 0x5C)) & 2)
        *((s32 *) (parts + 8)) = 3;
      sub_08005E80(0x189);
      *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1B)) = 0;
      callbacks = (s32 *) SCRIPT_EVENT_CALLBACK_TABLE;
      sub_080C31E8(entity + 0x18, entity + 0x22, 2, *callbacks);
    }
  }
  if (sub_08013B5C(sprite, work) == 0)
  {
    s32 stepOffset; u8 *stepBytes; u8 stepId; void **callbackTable; void *callback; u8 *stepSlot;
    *((void **) (entity + 0x14)) = (void *) gFixedKindEntityStateHandlers;
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) + 1);
    stepSlot = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    *((u8 *) (stepSlot + 0x19)) = (u8) ((*((u8 *) (stepSlot + 0x19))) + 1);
    stepOffset = (*((s16 *) (entity + 0x22))) * 2;
    stepBytes = entity + 0x18;
    stepId = *(stepBytes + stepOffset);
    callbackTable = *((void **) (entity + 0x14));
    callback = callbackTable[stepId];
    sub_080C31E0(entity, callback);
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) - 1);
    if (((*((u16 *) (entity + 2))) & 0x8000) == 0)
    {
      sub_080113A8(sprite, gfxInit);
      advanceMotion(work, 0);
    }
    else goto done;
  }
  sub_08020498(sprite, work);
  ((struct LayerTimer *) (*((u8 **) (work + 0x28))))->flags = 0;
  {
    u8 *coordBase = gCameraState;
    u8 *layerBase = gMainWorkspace;
    u8 *base1; u8 *base2; u32 idx;
    layerBase += 0x18A8;
    idx = ((u32)*layerBase + 1) * 0x40;
    base1 = coordBase + 0x1278;
    *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*layerBase + 1) * 0x40;
    base2 = coordBase + 0x127C;
    *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
  }
done:
  ;
}
