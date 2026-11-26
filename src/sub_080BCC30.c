/* Spawns the 50-part (0x32-slot) particle effect, the large variant of kind
 * 0x68: allocates a sprite and a 50-slot effect state, initialises every part
 * from the shared effect tables, sets the sprite attributes, then advances the
 * parent's state machine. */
struct S_02025FF0 { u8 _0[0x18C2]; u16 spriteBits; };
extern struct S_02025FF0 gMainWorkspace;
extern u16 D_08102F38[];   /* per-part affine/offset parameters, 4 per part */
extern void *gMainObjTimerCallback;

/* 0x34-byte effect part record allocated by allocEffectPart. */
struct EffectPart {
    u8 _0;
    u8 active;   /* 0x01: 0 while spawning */
    u8 param2;   /* 0x02: 8 */
    u8 param3;   /* 0x03: 1 */
    u16 tile;    /* 0x04: base tile from gEffectGfxTable */
    u16 p0;      /* 0x06: per-part parameters from D_08102F38 */
    u16 p1;      /* 0x08 */
    u16 p2;      /* 0x0A */
    u16 p3;      /* 0x0C */
    u16 tile2;   /* 0x0E: second tile from gEffectGfxTable */
    u32 sprite;  /* 0x10: owner sprite */
};
extern void *allocSpriteObject(void);                     /* alloc sprite */
extern void allocWorkSlot(void *, s32, s32, s32);     /* alloc + clear state */
extern void installUpdateHandler(void *, void *, void *);    /* install update handler */
extern s32 findKindIndex(void);                       /* kind -> active slot */
extern void initSpriteGfx(void *, void *, s32, s32);  /* init sprite graphics */
extern void *allocEffectPart(void);                     /* alloc effect part */
extern void sub_080C31E0(void *, void *);            /* indirect call */
extern void sub_080C31E4(void *, void *, s32);       /* indirect call */
extern void sub_080BCFA0(void);                      /* effect release handler */

void sub_080BCC30(u8 *entity)
{
  u8 *sprite;
  u8 *state;
  u8 *ptr;
  u8 *self;
  struct EffectPart **partSlots;
  struct EffectPart **slot;
  s32 *stateTable;
  u8 *effectDefs;
  u16 *partParams;
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
  ptr = state + 0x34;                              /* embedded gfx-init block */
  partSlots = (struct EffectPart **) (state + 0x48); /* 50 part pointers */
  installUpdateHandler(entity, state, sub_080BCFA0);
  *((u16 *) (state + 0x1C)) = 0x68;                /* kind */
  slotIndex = findKindIndex();                      /* kind already in r0 */
  *((u16 *) (state + 0x22)) = slotIndex;
  if ((slotIndex << 16) >= 0) goto cont;
fail:
  sub_080C31E0(entity, *((void **) (entity + 0x24)));
  return;
cont:
  *((u16 *) sprite) |= gMainWorkspace.spriteBits;
  initSpriteGfx(sprite, ptr, 0xA0, 0x14);
  i = 0;
  partParams = D_08102F38;
  effectDefs = (u8 *) 0x080CBDD0;
  slot = partSlots;
  do
  {
    *slot = allocEffectPart();
    if ((*slot) == NULL) goto fail;
    zero = 0;
    (*(*slot)).active = zero;
    (*slot)->param2 = 8;
    (*slot)->param3 = 1;
    (*slot)->tile = *((u16 *) ((effectDefs + ((*((s16 *) (state + 0x1C))) * 0x28)) + 0xC));
    (*slot)->p0 = partParams[0];
    (*slot)->p1 = partParams[1];
    (*slot)->p2 = partParams[2];
    (*slot)->p3 = partParams[3];
    (*slot)->tile2 = *((u16 *) ((effectDefs + ((*((s16 *) (state + 0x1C))) * 0x28)) + 0xE));
    (*(slot++))->sprite = (u32) sprite;
    i++;
  }
  while (i <= 0x31);
  {
    u32 zero2 = 0;
    *((u16 *) (sprite + 2)) = (*((u16 *) (sprite + 2)) | 0x400) | zero2;
    *((void **) (entity + 0x4C)) = zero;
    *((u16 *) (entity + 2)) |= 0x1000;
    *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x19)) = zero2;
    stateTable = (s32 *) 0x08671BB0;
    ptr = entity + 0x18;
    sub_080C31E4(ptr, entity + 0x22, *stateTable);
    *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x19)) += 1;
    ptr += ((u32) (*((s16 *) (entity + 0x22)))) * 2;
    {
      u8 stateId = *ptr;
      u8 *handlerTable = *((u8 **) (entity + 0x14));
      sub_080C31E0(entity, *((void **) (handlerTable + (stateId * 4))));
    }
  }
}
