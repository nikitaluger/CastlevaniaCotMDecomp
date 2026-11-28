/* Work state in the owner's +0x3C slot. World coordinates are 16.16; the
 * direction word selects the sprite's horizontal flip. */
struct Kind36EffectWork {
    u8 _0[8];
    u32 worldX;       /* 0x08 */
    u32 worldY;       /* 0x0C */
    u32 direction;    /* 0x10 */
    u8 _14[8];
    s16 kind;         /* 0x1C: KIND36_EFFECT_KIND */
    u8 _1E[4];
    u16 graphicsSlot; /* 0x22: index returned by findKindIndex */
    u32 _24;
    u32 layer;        /* 0x28: render layer from allocEffectPart */
    u8 _2C[8];
    u32 _34;          /* animation track scratch */
};

/* Entity that requested the effect. */
struct Kind36EffectOwner {
    u8 _0[2];
    u16 flags;        /* 0x02: EFFECT_SPRITE_READY set on success */
    u8 _04[0x10];
    u32 dispatch;     /* 0x14: script-step handler table */
    u8 _18[0xA];
    s16 step;         /* 0x22: current script-step index */
    u32 script;       /* 0x24: cleanup callback on failure */
    u8 _28[0x10];
    u32 sprite;       /* 0x38: spawned sprite */
    u32 work;         /* 0x3C: allocated work state */
    u8 _40[0xC];
    u32 worldX;       /* 0x4C */
    u8 _50[0xC];
    u32 worldY;       /* 0x5C */
    u8 _60[0xC];
    u32 direction;    /* 0x6C */
};

/* Sprite created for the effect. */
struct Kind36Sprite {
    u16 attrs;        /* 0x00: OAM attribute 0 */
    u8 _02[0x12];
    u32 screenX;      /* 0x14 */
    u32 screenY;      /* 0x18 */
    u32 gfxId;        /* 0x1C */
};

/* Render layer installed at work+0x28. */
struct Kind36EffectLayer {
    u8 mode;          /* 0x00 */
    u8 kind;          /* 0x01 */
    u8 layer;         /* 0x02 */
    u8 priority;      /* 0x03 */
    u16 gfxA;         /* 0x04 */
    u16 affine0;      /* 0x06 */
    u16 affine1;      /* 0x08 */
    u16 affine2;      /* 0x0A */
    u16 affine3;      /* 0x0C */
    u16 gfxB;         /* 0x0E */
    u32 sprite;       /* 0x10: owner sprite */
};

/* Per-kind graphics entry in gEffectGfxTable (40-byte stride). */
struct Kind36EffectGfxEntry {
    u8 _pad[4];
    u16 gfxA;         /* 0x04 */
    u16 gfxB;         /* 0x06 */
    u8 _08[0x20];
};

void *allocSpriteObject(void);
void allocWorkSlot(void *, u32, u32, u32);
void installUpdateHandler(void *, void *, void *);
void updateScriptedEffectObject(void);
u32 findKindIndex(s16);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, u32, u32);
void setSpriteFlipForDirection(void *, u32);
void *allocEffectPart(void);
void _call_via_r1(void *, u32);
void _call_via_r2(void *, void *, u32);
extern u8 gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 gKind36EffectAffineParams[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

/* Spawns the fixed kind-0x36 effect sprite for an owner entity: allocates the
 * sprite and work state, fills the render layer from the kind/attribute tables,
 * places the sprite in screen space using the camera scroll rows, then advances
 * the owner's script step. On allocation failure it calls the owner's cleanup
 * callback and returns. */
void spawnKind36EffectSprite(struct Kind36EffectOwner *owner)
{
  struct Kind36Sprite *sprite;
  struct Kind36EffectWork *work;
  u8 *animData;
  u8 *workspace;
  u8 *attrConfig;
  u8 *spriteTable;
  u32 graphics;
  u32 kindSlot;
  s16 step;
  sprite = (struct Kind36Sprite *) allocSpriteObject();
  if (sprite == NULL) goto fail;
  owner->sprite = (u32) sprite;
  allocWorkSlot(owner, 0, KIND36_EFFECT_WORK_SLOT, 0);
  if (owner->work == 0) goto fail;
  sprite->gfxId = EFFECT_SPRITE_GFX_ID;
  work = (struct Kind36EffectWork *) owner->work;
  animData = ((u8 *) work) + 0x34;
  installUpdateHandler(owner, work, &updateScriptedEffectObject);
  work->kind = KIND36_EFFECT_KIND;
  work->worldX = owner->worldX;
  work->worldY = owner->worldY;
  work->direction = owner->direction;
  kindSlot = findKindIndex(work->kind);
  work->graphicsSlot = (u16) kindSlot;
  if (((s16) ((u16) kindSlot)) < 0) goto fail;
  graphics = ((u32) (((s32) ((s16) work->graphicsSlot)) << 6)) + (0x80 << 2);
  graphics |= (kindSlot + 8) << 12;
  sprite->attrs = (u16) graphics;
  workspace = gMainWorkspace;
  graphics |= *((u16 *) (workspace + KIND36_GFX_FLAGS));
  sprite->attrs = (u16) graphics;
  initSpriteGraphics(sprite, animData, (void *) (gSpriteAnimDataTable + (KIND36_ANIM_ENTRY_STRIDE * ((s32) work->kind))));
  setAnimationFrame(sprite, animData, KIND36_EFFECT_START_FRAME, 0x01);
  setSpriteFlipForDirection(sprite, work->direction);
  attrConfig = (u8 *) gKind36EffectAffineParams;
  work->layer = (u32) allocEffectPart();
  if (work->layer == 0) goto fail;
  goto cont;
fail:
  _call_via_r1(owner, owner->script);
  return;
cont:
  ((u8 *) work->layer)[1] = KIND36_LAYER_KIND;
  ((u8 *) work->layer)[2] = KIND36_LAYER_INDEX;
  ((u8 *) work->layer)[3] = KIND36_LAYER_PRIORITY;
  { u8 *layer = (u8 *) work->layer; spriteTable = gEffectGfxTable; ((struct Kind36EffectLayer *) layer)->gfxA = ((struct Kind36EffectGfxEntry *) (spriteTable + (((s32) work->kind) * KIND36_GFX_ENTRY_STRIDE)))->gfxA; }
  ((struct Kind36EffectLayer *) work->layer)->affine0 = *((u16 *) (&attrConfig[0]));
  ((struct Kind36EffectLayer *) work->layer)->affine1 = *((u16 *) (&attrConfig[2]));
  ((struct Kind36EffectLayer *) work->layer)->affine2 = *((u16 *) (&attrConfig[4]));
  ((struct Kind36EffectLayer *) work->layer)->affine3 = *((u16 *) (&attrConfig[6]));
  ((struct Kind36EffectLayer *) work->layer)->gfxB = ((struct Kind36EffectGfxEntry *) (spriteTable + (((s32) work->kind) * KIND36_GFX_ENTRY_STRIDE)))->gfxB;
  *((u32 *) (((u8 *) work->layer) + 0x10)) = (u32) sprite;
  {
    u8 *scroll = gCameraState;
    u8 *scrollXRow;
    u8 *scrollYRow;
    u32 rowIndex;
    rowIndex = ((u32)*(workspace + KIND36_FRAME_COUNTER) + 1) * KIND36_SCROLL_STRIDE;
    scrollXRow = scroll + KIND36_SCROLL_X;
    sprite->screenX = work->worldX - ((*(u32 *)(scrollXRow + rowIndex) + KIND36_SCROLL_BIAS_X) & 0xFFFF0000);
    rowIndex = ((u32)*(workspace + KIND36_FRAME_COUNTER) + 1) * KIND36_SCROLL_STRIDE;
    scrollYRow = scroll + KIND36_SCROLL_Y;
    sprite->screenY = work->worldY - ((*(u32 *)(scrollYRow + rowIndex) + KIND36_SCROLL_BIAS_Y) & 0xFFFF0000);
  }
  owner->flags |= EFFECT_SPRITE_READY;
  step = *((s16 *) (((u8 *) owner) + 0x22));
  *((((u8 *) owner) + (((s32) step) * 2)) + 0x19) = 0;
  {
    u32 *timerCallback = &gMainObjTimerCallbacks;
    u8 *steps = ((u8 *) owner) + 0x18;
    u8 *stepIndexPtr = ((u8 *) owner) + 0x22;
    _call_via_r2(steps, stepIndexPtr, *timerCallback);
    { s16 stepA = *((s16 *) stepIndexPtr); u8 *stepByte = (u8 *)((((s32) stepA) * 2) + (u32) owner); stepByte[0x19] = (u8) (stepByte[0x19] + 1); }
    { s16 stepB = *((s16 *) stepIndexPtr); u8 *handler = steps + (((s32) stepB) * 2); _call_via_r1(owner, *((u32 *) ((((u32) (*handler)) * 4) + owner->dispatch))); }
  }
}
