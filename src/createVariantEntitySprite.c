/* Parent entity. Offsets in the name are the byte offsets in the original struct. */
struct Entity {
    u8 _0[2];
    u16 flags;          /* 0x02 */
    u8 _04[0x10];
    u32 dispatch;       /* 0x14: per-step handler table */
    u8 _18[0xA];
    s16 step;           /* 0x22: current animation step */
    u32 script;         /* 0x24: current script */
    u8 _28[0x10];
    u32 object;         /* 0x38: sprite object created here */
    u32 part;           /* 0x3C: effect part data */
    u8 _40[0xC];
    u8 variant;         /* 0x4C: index into gProjectileSpeedTable */
    u8 _4D[0xF];
    u32 x;              /* 0x5C */
    u8 _60[0xC];
    u32 y;              /* 0x6C */
    u8 _70[0xC];
    u32 _7C;
};
/* Effect part that owns the animation and the sub-effect. */
struct Part {
    u8 _0[8];
    u32 x;              /* 0x08 */
    u32 y;              /* 0x0C */
    u32 _10;
    u8 _14[8];
    s16 animId;         /* 0x1C */
    u8 _1E[4];
    u16 animSlot;       /* 0x22 */
    u32 _24;
    u32 subEffect;      /* 0x28 */
    u8 _2C[8];
    u32 anim;           /* 0x34: animation player */
};
/* Render object allocated by allocSpriteObject. */
struct SpriteObj {
    u16 graphics;       /* 0x00: packed graphics/shape */
    u8 _02[0x12];
    u32 x;              /* 0x14 */
    u32 y;              /* 0x18 */
    u32 typeFlags;      /* 0x1C */
};
/* Small sub-effect allocated by allocEffectPart. */
struct SubEffect {
    u8 f00, f01, f02, f03;
    u16 f04, f06, f08, f0A, f0C, f0E;
    u32 f10;
};
/* Entry of gEffectGfxTable: two graphics parameters. */
struct AnimEntry {
    u8 _pad[4];
    u16 w0;             /* 0x04 */
    u16 w1;             /* 0x06 */
    u8 _08[0x20];
};
void *allocSpriteObject(void);
void allocWorkSlot(void *, u32, u32, u32);
void installUpdateHandler(void *, void *, void *);
void sub_08014290(void);
u32 findKindIndex(s16);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, u32, u32);
void *allocEffectPart(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
extern u8 gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u32 gProjectileSpeedTable[];
extern u16 D_080CEF98[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gScriptStepCallbackTable;

/* Create a sprite object and its effect part for an entity: pick the animation
 * from the variant table, attach an animation player and a small sub-effect,
 * place it at the entity's coordinates, then advance the animation step. */
void createVariantEntitySprite(struct Entity *entity)
{
  struct SpriteObj *sprite;
  struct Part *part;
  u8 *anim;
  u8 *state;
  u8 *config;
  u8 *animTable;
  u32 graphics;
  u32 slot;
  s16 step;
  u8 zero;
  sprite = (struct SpriteObj *) allocSpriteObject();
  if (sprite == NULL) goto fail;
  entity->object = (u32) sprite;
  allocWorkSlot(entity, 0, VARIANT_ENTITY_WORK_SLOT_SIZE, 0);
  if (entity->part == 0) goto fail;
  sprite->typeFlags = VARIANT_SPRITE_GFX_ID;
  part = (struct Part *) entity->part;
  anim = ((u8 *) part) + 0x34;
  installUpdateHandler(entity, part, &sub_08014290);
  part->animId = (s16) gProjectileSpeedTable[entity->variant];
  zero = 0;
  part->x = entity->x;
  part->y = entity->y;
  slot = findKindIndex(part->animId);
  part->animSlot = (u16) slot;
  if (((s16) ((u16) slot)) < 0) goto fail;
  graphics = ((u32) (((s32) ((s16) part->animSlot)) << 6)) + (0x80 << 2);
  graphics |= (slot + 8) << 12;
  sprite->graphics = (u16) graphics;
  state = gMainWorkspace;
  graphics |= *((u16 *) (state + 0x18C2));
  sprite->graphics = (u16) graphics;
  initSpriteGraphics(sprite, anim, (void *) (gSpriteAnimDataTable + (12 * ((s32) part->animId))));
  setAnimationFrame(sprite, anim, VARIANT_ANIM_FRAME, VARIANT_ANIM_FRAME_FLAG);
  config = (u8 *) D_080CEF98;
  part->subEffect = (u32) allocEffectPart();
  if (part->subEffect == 0) goto fail;
  goto cont;
fail:
  sub_080C31E0(entity, entity->script);
  return;
cont:
  ((u8 *) part->subEffect)[1] = zero;
  ((u8 *) part->subEffect)[2] = 8;
  ((u8 *) part->subEffect)[3] = 1;
  { u8 *sub = (u8 *) part->subEffect; animTable = gEffectGfxTable; ((struct SubEffect *) sub)->f04 = ((struct AnimEntry *) (animTable + (((s32) part->animId) * VARIANT_ANIM_ENTRY_SIZE)))->w0; }
  ((struct SubEffect *) part->subEffect)->f06 = *((u16 *) (&config[0]));
  ((struct SubEffect *) part->subEffect)->f08 = *((u16 *) (&config[2]));
  ((struct SubEffect *) part->subEffect)->f0A = *((u16 *) (&config[4]));
  ((struct SubEffect *) part->subEffect)->f0C = *((u16 *) (&config[6]));
  ((struct SubEffect *) part->subEffect)->f0E = ((struct AnimEntry *) (animTable + (((s32) part->animId) * VARIANT_ANIM_ENTRY_SIZE)))->w1;
  *((u32 *) (((u8 *) part->subEffect) + 0x10)) = (u32) sprite;
  {
    u8 *pt = gCameraState;
    u8 *base1;
    u8 *base2;
    u32 idx;
    idx = ((u32)*(state + 0x18A8) + 1) * 0x40;
    base1 = pt + 0x1278;
    sprite->x = part->x - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*(state + 0x18A8) + 1) * 0x40;
    base2 = pt + 0x127C;
    sprite->y = part->y - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
  }
  entity->flags |= CHILD_SPRITE_READY;
  step = *((s16 *) (((u8 *) entity) + 0x22));
  *((((u8 *) entity) + (((s32) step) * 2)) + 0x19) = zero;
  {
    u32 *gptr = &gScriptStepCallbackTable;
    u8 *p18 = ((u8 *) entity) + 0x18;
    u8 *p22 = ((u8 *) entity) + 0x22;
    sub_080C31E4(p18, p22, *gptr);
    { s16 i2 = *((s16 *) p22); u8 *p19 = (u8 *)((((s32) i2) * 2) + (u32) entity); p19[0x19] = (u8) (p19[0x19] + 1); }
    { s16 i3 = *((s16 *) p22); u8 *q = p18 + (((s32) i3) * 2); sub_080C31E0(entity, *((u32 *) ((((u32) (*q)) * 4) + entity->dispatch))); }
  }
}
