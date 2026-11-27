struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _04[0x10];
    u32 dispatch;
    u8 _18[0xA];
    s16 step;
    u32 script;
    u8 _28[0x10];
    u32 object;
    u32 part;
    u8 _40[0xC];
    u32 f4C;
    u8 _50[0xC];
    u32 f5C;
    u8 _60[0xC];
    u8 f6C;
    u8 _6D[3];
    u8 f70;
};
struct Part {
    u8 _0[8];
    u32 x;
    u32 y;
    u32 _10;
    u32 _14;
    u8 _18[4];
    s16 animId;
    u8 _1E[4];
    u16 animSlot;
    u32 _24;
    u32 subEffect;
    u8 _2C[8];
    u32 anim;
};
struct SpriteObj {
    u16 graphics;
    u8 _02[0x12];
    u32 x;
    u32 y;
    u32 typeFlags;
};
struct SubEffect {
    u8 f00, f01, f02, f03;
    u16 f04, f06, f08, f0A, f0C, f0E;
    u32 f10;
};
struct AnimEntry {
    u8 _pad[4];
    u16 w0;
    u16 w1;
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
extern u16 D_080CEDF4[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

/* Spawns a direction-aware attack effect for its owner: allocates the sprite
 * and work slot, fills the animation slot and render layer from the kind and
 * attribute tables, offsets the effect by the owner's flip/facing flags,
 * places it in world space corrected for camera scroll and records the
 * attack on the owner's script step. */
void spawnDirectionalAttackEffectSprite(struct Entity *owner)
{
  struct SpriteObj *sprite;
  struct Part *part;
  u8 *animData;
  u8 *workspace;
  u8 *affineParams;
  u8 *gfxTable;
  u32 graphics;
  u32 kindSlot;
  s16 stepIndex;
  sprite = (struct SpriteObj *) allocSpriteObject();
  if (sprite == NULL) goto fail;
  owner->object = (u32) sprite;
  allocWorkSlot(owner, 0, 0x4C, 0);
  if (owner->part == 0) goto fail;
  sprite->typeFlags = 0x8000000B;
  part = (struct Part *) owner->part;
  animData = ((u8 *) part) + 0x34;
  installUpdateHandler(owner, part, &sub_08014290);
  part->animId = 0x17;
  part->x = owner->f4C;
  part->y = owner->f5C;
  if (((u8 *)owner)[0x6C] != 0) {
    part->y += 0xFFF40000;
  } else {
    part->y += 0xFFE40000;
  }
  if (((u8 *)owner)[0x70] != 0) {
    part->x += 0x1E0000;
    part->_10 = 0x40000;
  } else {
    part->x += 0xFFE20000;
    part->_10 = 0xFFFC0000;
  }
  part->_14 = 0;
  kindSlot = findKindIndex(part->animId);
  part->animSlot = (u16) kindSlot;
  if (((s16) ((u16) kindSlot)) < 0) goto fail;
  graphics = ((u32) (((s32) ((s16) part->animSlot)) << 6)) + (0x80 << 2);
  graphics |= (kindSlot + 8) << 12;
  sprite->graphics = (u16) graphics;
  workspace = gMainWorkspace;
  graphics |= *((u16 *) (workspace + 0x18C2));
  sprite->graphics = (u16) graphics;
  initSpriteGraphics(sprite, animData, (void *) (gSpriteAnimDataTable + (12 * ((s32) part->animId))));
  setAnimationFrame(sprite, animData, 0x3B, 0x01);
  affineParams = (u8 *) D_080CEDF4;
  part->subEffect = (u32) allocEffectPart();
  if (part->subEffect == 0) goto fail;
  goto cont;
fail:
  sub_080C31E0(owner, owner->script);
  return;
cont:
  ((u8 *) part->subEffect)[1] = 5;
  ((u8 *) part->subEffect)[2] = 8;
  ((u8 *) part->subEffect)[3] = 1;
  { u8 *layer = (u8 *) part->subEffect; gfxTable = gEffectGfxTable; ((struct SubEffect *) layer)->f04 = ((struct AnimEntry *) (gfxTable + (((s32) part->animId) * 40)))->w0; }
  ((struct SubEffect *) part->subEffect)->f06 = *((u16 *) (&affineParams[0]));
  ((struct SubEffect *) part->subEffect)->f08 = *((u16 *) (&affineParams[2]));
  ((struct SubEffect *) part->subEffect)->f0A = *((u16 *) (&affineParams[4]));
  ((struct SubEffect *) part->subEffect)->f0C = *((u16 *) (&affineParams[6]));
  ((struct SubEffect *) part->subEffect)->f0E = ((struct AnimEntry *) (gfxTable + (((s32) part->animId) * 40)))->w1;
  *((u32 *) (((u8 *) part->subEffect) + 0x10)) = (u32) sprite;
  {
    u8 *scroll = gCameraState;
    u8 *scrollXRow;
    u8 *scrollYRow;
    u32 rowIndex;
    rowIndex = ((u32)*(workspace + 0x18A8) + 1) * 0x40;
    scrollXRow = scroll + 0x1278;
    sprite->x = part->x - ((*(u32 *)(scrollXRow + rowIndex) + 0x8000) & 0xFFFF0000);
    rowIndex = ((u32)*(workspace + 0x18A8) + 1) * 0x40;
    scrollYRow = scroll + 0x127C;
    sprite->y = part->y - ((*(u32 *)(scrollYRow + rowIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  owner->flags |= 0x1000;
  stepIndex = *((s16 *) (((u8 *) owner) + 0x22));
  *((((u8 *) owner) + (((s32) stepIndex) * 2)) + 0x19) = 0;
  {
    u32 *timerCallback = &gMainObjTimerCallbacks;
    u8 *steps = ((u8 *) owner) + 0x18;
    u8 *stepIndexPtr = ((u8 *) owner) + 0x22;
    sub_080C31E4(steps, stepIndexPtr, *timerCallback);
    { s16 stepA = *((s16 *) stepIndexPtr); u8 *stepByte = (u8 *)((((s32) stepA) * 2) + (u32) owner); stepByte[0x19] = (u8) (stepByte[0x19] + 1); }
    { s16 stepB = *((s16 *) stepIndexPtr); u8 *handler = steps + (((s32) stepB) * 2); sub_080C31E0(owner, *((u32 *) ((((u32) (*handler)) * 4) + owner->dispatch))); }
  }
}
