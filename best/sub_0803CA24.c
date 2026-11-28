extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, s32, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void setSpriteFacingToTarget(void *);
extern void *allocEffectPart(void);
extern void registerScriptObject(void *, s32);
extern void _call_via_r1(void *, void *);
extern void updateScriptedEffectObject(void);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u8 gSpriteKindTable[];
extern u16 gAttackEffectAffineParams[];
extern u32 gMainObjTimerCallbacks[];
struct KindEntry
{
  u16 gfxA;
  u16 param;
  u16 gfxB;
  u8 _6[0xE];
};
struct Layer
{
  u8 _0;
  u8 kind;
  u8 layer;
  u8 priority;
  u16 gfxA;
  u16 attr0;
  u16 attr1;
  u16 attr2;
  u16 attr3;
  u16 gfxB;
  u32 object;
};
void sub_0803CA24(u8 *obj)
{
  u8 *sprite;
  u8 *work;
  u8 *anim;
  u8 *anim_1;
  struct Layer *layer;
  s32 param;
  s32 __repair_phase_param;
  volatile unsigned int kind;
  u32 scrollIdx;
  u32 __repair_phase_scrollIdx;
  param = *((s32 *) (obj + 0xAC));
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((u32 *) (obj + 0x38)) = (u32) sprite;
  allocWorkSlot(obj, 0, 0x58, 0);
  if ((*((u32 *) (obj + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  work = *((u8 **) (obj + 0x3C));
  anim = work + 0x34;
  installUpdateHandler(obj, work, (void *) updateScriptedEffectObject);
  {
    {
      initWorkStateForKind(obj, sprite, work, param, 0x2D);
    }
  }
  initSpriteGraphics(sprite, anim, ((s32) gSpriteAnimDataTable) + ((kind = *((s16 *) (work + 0x1C))) * 0xC));
  setAnimationFrame(sprite, anim, 0, 0);
  *((u32 *) (work + 8)) = *((u32 *) (obj + 0x4C));
  *((u32 *) (work + 0xC)) = *((u32 *) (obj + 0x5C));
  setSpriteFacingToTarget(sprite);
  layer = allocEffectPart();
  *((u32 *) (work + 0x28)) = (u32) layer;
  if (layer == NULL)
  {
    goto fail;
  }
  layer->kind = 5;
  {
    struct KindEntry *ke = (struct KindEntry *) (gSpriteKindTable + (kind * 0x14));
    __repair_phase_param = 0;
    ((struct Layer *) (*((u32 *) (work + 0x28))))->layer = (u8) __repair_phase_param;
    ((struct Layer *) (*((u32 *) (work + 0x28))))->priority = (u8) __repair_phase_param;
    ((struct Layer *) (*((u32 *) (work + 0x28))))->gfxA = ke->gfxA;
    ((struct Layer *) (*((u32 *) (work + 0x28))))->attr0 = gAttackEffectAffineParams[0];
    ((struct Layer *) (*((u32 *) (work + 0x28))))->attr1 = gAttackEffectAffineParams[1];
    ((struct Layer *) (*((u32 *) (work + 0x28))))->attr2 = gAttackEffectAffineParams[2];
    ((struct Layer *) ((*((u32 *) (work + 0x28))) & 0xFFFFFFFFFFFFFFFFu))->attr3 = gAttackEffectAffineParams[3];
    ((struct Layer *) (*((u32 *) (work + 0x28))))->gfxB = ke->gfxB;
  }
  ((struct Layer *) (*((u32 *) (work + 0x28))))->object = (u32) sprite;
  {
    u8 *state = gMainWorkspace + 0x18A8;
    u8 *camera = gCameraState;
    scrollIdx = (((u32) (*state)) + 1) * 0x40;
    anim_1 = (void *) (*((u32 *) (work + 8)));
    *((u32 *) (sprite + 0x14)) = ((u32) anim_1) - (((*((u32 *) ((camera + 0x1278) + scrollIdx))) + 0x8000) & 0xFFFF0000);
    __repair_phase_scrollIdx = (((u32) (*state)) + 1) * 0x40;
    *((u32 *) (sprite + 0x18)) = (*((u32 *) (work + 0xC))) - (((*((u32 *) ((gCameraState + 0x127C) + __repair_phase_scrollIdx))) + 0xFFFF8000) & 0xFFFF0000);
  }
  {
    {
      registerScriptObject(obj, 0);
    }
  }
  {
    u16 flags = *((u16 *) (obj + 2));
    flags |= 0x1000;
    *((u16 *) (obj + 2)) = flags;
  }
  *((u8 *) ((((u32) ((*((s16 *) (obj + 0x22))) * 2)) + ((u32) obj)) + 0x19)) = (u8) __repair_phase_param;
  {
    u32 *scriptCallback = (u32 *) gMainObjTimerCallbacks;
    u8 *p18 = obj + 0x18;
    {
      {
        _call_via_r1(p18, obj + 0x22);
      }
    }
    {
      s16 step = *((s16 *) (obj + 0x22));
      u8 *p19 = (u8 *) (((((u32) step) * 2) + ((u32) obj)) + 0x19);
      *p19 = (u8) ((*p19) + 1);
      step = *((s16 *) (obj + 0x22));
      {
        u8 *q = p18 + (step * 2);
        {
          {
            _call_via_r1(obj, *((void **) (((u8 *) (*((u32 *) (obj + 0x14)))) + ((*((u8 *) q)) * 4))));
          }
        }
      }
    }
  }
  return;
  fail:
  _call_via_r1(obj, *((void **) (obj + 0x24)));

}

