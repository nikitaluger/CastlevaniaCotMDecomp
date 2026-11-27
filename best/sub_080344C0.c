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

void sub_080344C0(struct Entity *owner)
{
  struct SpriteObj *sprite;
  struct Part *part;
  u8 *animData;
  u8 *state;
  u8 *attrConfig;
  u8 *spriteTable;
  u32 graphics;
  u32 animSlotId;
  s16 step;
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
  } else {
    part->x += 0x02025FF0;
  }
  part->_10 = 0x18C2;
  part->_14 = 0;
  animSlotId = findKindIndex(part->animId);
  part->animSlot = (u16) animSlotId;
  if (((s16) ((u16) animSlotId)) < 0) goto fail;
  graphics = ((u32) (((s32) ((s16) part->animSlot)) << 6)) + (0x80 << 2);
  graphics |= (animSlotId + 8) << 12;
  sprite->graphics = (u16) graphics;
  state = gMainWorkspace;
  graphics |= *((u16 *) (state + 0x18C2));
  sprite->graphics = (u16) graphics;
  initSpriteGraphics(sprite, animData, (void *) (gSpriteAnimDataTable + (12 * ((s32) part->animId))));
  setAnimationFrame(sprite, animData, 0x3B, 0x01);
  attrConfig = (u8 *) D_080CEDF4;
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
  { u8 *sub = (u8 *) part->subEffect; spriteTable = gEffectGfxTable; ((struct SubEffect *) sub)->f04 = ((struct AnimEntry *) (spriteTable + (((s32) part->animId) * 40)))->w0; }
  ((struct SubEffect *) part->subEffect)->f06 = *((u16 *) (&attrConfig[0]));
  ((struct SubEffect *) part->subEffect)->f08 = *((u16 *) (&attrConfig[2]));
  ((struct SubEffect *) part->subEffect)->f0A = *((u16 *) (&attrConfig[4]));
  ((struct SubEffect *) part->subEffect)->f0C = *((u16 *) (&attrConfig[6]));
  ((struct SubEffect *) part->subEffect)->f0E = ((struct AnimEntry *) (spriteTable + (((s32) part->animId) * 40)))->w1;
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
  owner->flags |= 0x1000;
  step = *((s16 *) (((u8 *) owner) + 0x22));
  *((((u8 *) owner) + (((s32) step) * 2)) + 0x19) = 0;
  {
    u32 *gptr = &gMainObjTimerCallbacks;
    u8 *p18 = ((u8 *) owner) + 0x18;
    u8 *p22 = ((u8 *) owner) + 0x22;
    sub_080C31E4(p18, p22, *gptr);
    { s16 i2 = *((s16 *) p22); u8 *p19 = (u8 *)((((s32) i2) * 2) + (u32) owner); p19[0x19] = (u8) (p19[0x19] + 1); }
    { s16 i3 = *((s16 *) p22); u8 *q = p18 + (((s32) i3) * 2); sub_080C31E0(owner, *((u32 *) ((((u32) (*q)) * 4) + owner->dispatch))); }
  }
}
