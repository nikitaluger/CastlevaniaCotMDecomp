/* Spawns the large (kind 0x68) particle effect: a sprite plus 50 render parts.
 * Allocates the sprite and work state, fills every part from the shared
 * kind/affine tables, sets the sprite attributes, then advances the parent's
 * script step. */
extern struct FixedEffectWorkspace gMainWorkspace;
extern u8 gEffectGfxTable[];
extern u16 gKind68EffectAffineParams[];
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, s32);
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initSpriteGfx(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void releaseKind68Effect(void *);

void spawnKind68Effect(u8 *entity)
{
  u8 *sprite;
  u8 *state;
  u8 *gfxInit;
  u8 *self;
  struct Kind68EffectPart **partSlots;
  struct Kind68EffectPart **part;
  s32 *stateTable;
  u8 *kindDefs;
  u16 *params;
  u32 i;
  u32 zero;
  s32 slotIndex;
  sprite = allocSpriteObject();
  if (sprite == NULL) goto fail;
  self = entity;
  *((void **) (entity + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x110, 0);
  if ((*((void **) (self + 0x3C))) == NULL) goto fail;
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  *((u8 *) (sprite + 0x2A)) &= 0xBF;
  state = *((u8 **) (entity + 0x3C));
  gfxInit = state + 0x34;
  partSlots = (struct Kind68EffectPart **) (state + 0x48); /* 50 part pointers */
  installUpdateHandler(entity, state, releaseKind68Effect);
  *((u16 *) (state + 0x1C)) = 0x68;                /* kind */
  slotIndex = findKindIndex();                      /* kind already in r0 */
  *((u16 *) (state + 0x22)) = slotIndex;
  if ((slotIndex << 16) >= 0) goto cont;
fail:
  _call_via_r1(entity, *((void **) (entity + 0x24)));
  return;
cont:
  *((u16 *) sprite) |= gMainWorkspace.gfxFlags;
  initSpriteGfx(sprite, gfxInit, 0xA0, 0x14);
  i = 0;
  params = gKind68EffectAffineParams;
  kindDefs = (u8 *) gEffectGfxTable;
  part = partSlots;
  do
  {
    *part = allocEffectPart();
    if ((*part) == NULL) goto fail;
    zero = 0;
    (*(*part)).active = zero;
    (*part)->layer = 8;
    (*part)->priority = 1;
    (*part)->gfxIndex = *((u16 *) ((kindDefs + ((*((s16 *) (state + 0x1C))) * 0x28)) + 0xC));
    (*part)->affine0 = params[0];
    (*part)->affine1 = params[1];
    (*part)->affine2 = params[2];
    (*part)->affine3 = params[3];
    (*part)->palette = *((u16 *) ((kindDefs + ((*((s16 *) (state + 0x1C))) * 0x28)) + 0xE));
    (*(part++))->sprite = (u32) sprite;
    i++;
  }
  while (i <= 0x31);
  {
    u32 zero2 = 0;
    *((u16 *) (sprite + 2)) = (*((u16 *) (sprite + 2)) | 0x400) | zero2;
    *((void **) (entity + 0x4C)) = zero;
    *((u16 *) (entity + 2)) |= 0x1000;
    *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x19)) = zero2;
    stateTable = (s32 *) MAIN_OBJ_TIMER_CALLBACK_TABLE;
    gfxInit = entity + 0x18;
    _call_via_r2(gfxInit, entity + 0x22, *stateTable);
    *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x19)) += 1;
    gfxInit += ((u32) (*((s16 *) (entity + 0x22)))) * 2;
    {
      u8 stateId = *gfxInit;
      u8 *handlerTable = *((u8 **) (entity + 0x14));
      _call_via_r1(entity, *((void **) (handlerTable + (stateId * 4))));
    }
  }
}
