struct GraphicsWorkspace { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GraphicsWorkspace gMainWorkspace;

struct EffectRenderPart {
    u8 _0;
    u8 active;
    u8 kind;
    u8 layer;
    u16 gfxIndex;
    u16 anim0;
    u16 anim1;
    u16 anim2;
    u16 anim3;
    u16 palette;
    u32 sprite;
};

struct EffectWork {
    u8 _0[8];
    u32 f8;
    u32 fC;
    u8 _10[0xC];
    u16 animIndex;
    u8 _1E[4];
    s16 kindIndex;
    u8 _24[4];
    struct EffectRenderPart *renderPart;
    u8 _2C[0x1C];
    u32 f48;
};

struct EffectGfxEntry { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x20]; };
extern struct EffectGfxEntry gEffectGfxTable[];
extern u16 D_08102708[];
extern void *gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void sub_08014668(void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/*
 * Build an actor's sprite/work/render-part trio for a scripted effect, set up
 * its animation, gfx flags and palette value, copy in the spawn defaults, then
 * advance its script index. On any allocation failure the saved cleanup
 * callback is invoked instead.
 */
void initScriptedEffectSprite(u8 *actor)
{
  s32 sprite;
  struct EffectWork *work;
  u8 *anim;
  s32 value;
  u32 v;
  u16 *animDefaults;
  u8 *scriptPtr;
  void **scriptTablePtr;
  u8 *scriptEntry;

  sprite = (s32) allocSpriteObject();
  if (sprite == 0)
  {
    goto fail;
  }
  *((u32 *) (actor + 0x38)) = sprite;
  allocWorkSlot(actor, 0, 0x48, 0);
  if ((*((u32 *) (actor + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  work = (struct EffectWork *) (*((u8 **) (actor + 0x3C)));
  anim = ((u8 *) work) + 0x34;
  installUpdateHandler(actor, (u8 *) work, updateActorEffectSubObject);
  work->animIndex = 0x65;
  value = findKindIndex();
  work->kindIndex = value;
  if (((s16) value) < 0)
  {
    goto fail;
  }
  value = work->kindIndex;
  value = value << 6;
  value = value + 0x200;
  value &= 0xFC0;
  *((u16 *) sprite) = value;
  *((u16 *) sprite) |= gMainWorkspace.gfxFlags;
  sub_08014668((void *) sprite, *((u32 *) (actor + 0x4C)));
  initSpriteGraphics((void *) sprite, anim, ((*((s16 *) (((u8 *) work) + 0x1C))) * 0xC) + 0x080CD400);
  setAnimationFrame((void *) sprite, anim, 0, 0);
  {
    s16 entryIndex = *((s16 *) (anim + 0xE));
    u8 indexAdjust = *((u8 *) (anim + 1));
    void **table = *((void ***) (anim + 8));
    u32 sum = (u32) (entryIndex + indexAdjust);
    void *tableBase = *table;
    u32 offset = sum * 4;
    u8 *entry = (u8 *) (offset + (u32) tableBase) - 4;
    u16 lookup = *((u16 *) (entry + 2));
    *((u16 *) (actor + 0x5C)) = lookup;
  }
  animDefaults = D_08102708;
  work->renderPart = allocEffectPart();
  if (work->renderPart != NULL)
  {
    goto cont;
  }
  fail:
  sub_080C31E0(actor, *((void **) (actor + 0x24)));

  return;
  cont:
  work->renderPart->active = 1;

  work->renderPart->kind = 8;
  work->renderPart->layer = 1;
  work->renderPart->gfxIndex = gEffectGfxTable[*((s16 *) (((u8 *) work) + 0x1C))].gfxIndex;
  work->renderPart->anim0 = animDefaults[0];
  work->renderPart->anim1 = animDefaults[1];
  work->renderPart->anim2 = animDefaults[2];
  work->renderPart->anim3 = animDefaults[3];
  work->renderPart->palette = gEffectGfxTable[*((s16 *) (((u8 *) work) + 0x1C))].palette;
  work->renderPart->sprite = sprite;
  *((u16 *) (sprite + 2)) |= 0x400;
  *((u32 *) (actor + 4)) = 0;
  *((u16 *) (actor + 2)) |= 0x1000;
  *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x19)) = 0;
  scriptTablePtr = &gScriptStepCallbackTable;
  scriptPtr = actor;
  scriptPtr += 0x18;
  sub_080C31E4(scriptPtr, actor + 0x22, (s32) (*scriptTablePtr));
  *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x19)) += 1;
  scriptEntry = scriptPtr + (((u32) (*((s16 *) (actor + 0x22)))) * 2);
  sub_080C31E0(actor, *((void **) ((*((u8 **) (actor + 0x14))) + ((*((u8 *) scriptEntry)) * 4))));
}
