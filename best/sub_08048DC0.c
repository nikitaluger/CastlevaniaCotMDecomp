extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, u32, u32, u32);
extern void installUpdateHandler(void *, void *, void *);
extern void updateScriptedEffectObject(void);
extern u32 findKindIndex(s16);
extern void initSpriteGraphics(void *, void *, void *);
extern void sub_080492B8(void *, void *, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, u32);

extern u8 gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u32 D_080CF8F8[];
extern u16 D_080CF8F0[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

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
    u8 _40[0x54];
    u8 variant94;
};
struct Part {
    u8 _0[8];
    u32 f08;
    u32 f0C;
    u32 f10;
    u32 f14;
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

void sub_08048DC0(struct Entity *entity)
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

  sprite = (struct SpriteObj *)allocSpriteObject();
  if (sprite == NULL) goto fail;
  entity->object = (u32)sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if (entity->part == 0) goto fail;
  sprite->typeFlags = 0x80000009;
  part = (struct Part *)entity->part;
  anim = ((u8 *)part) + 0x34;
  installUpdateHandler(entity, part, &updateScriptedEffectObject);
  part->animId = (s16)D_080CF8F8[*((u8 *)entity + 0x94)];
  zero = 0;
  part->f08 = *(u32 *)((u8 *)entity + 0x4C);
  part->f0C = *(u32 *)((u8 *)entity + 0x5C);
  part->f10 = *(u32 *)((u8 *)entity + 0x6C);
  part->f14 = *(u32 *)((u8 *)entity + 0x7C);
  slot = findKindIndex(part->animId);
  part->animSlot = (u16)slot;
  if (((s16)((u16)slot)) < 0) goto fail;
  graphics = ((u32)(((s32)((s16)part->animSlot)) << 6)) + (0x80 << 2);
  graphics |= (slot + 8) << 12;
  sprite->graphics = (u16)graphics;
  state = gMainWorkspace;
  graphics |= *((u16 *)(state + 0x18C2));
  sprite->graphics = (u16)graphics;
  initSpriteGraphics(sprite, anim, (void *)(gSpriteAnimDataTable + (12 * ((s32)part->animId))));
  sub_080492B8(sprite, part, (s32)anim);
  config = (u8 *)D_080CF8F0;
  part->subEffect = (u32)allocEffectPart();
  if (part->subEffect == 0) goto fail;
  goto cont;

fail:
  sub_080C31E0(entity, entity->script);
  return;

cont:
  ((u8 *)part->subEffect)[1] = 5;
  ((u8 *)part->subEffect)[2] = 8;
  ((u8 *)part->subEffect)[3] = 1;
  {
    u8 *sub = (u8 *)part->subEffect;
    animTable = gEffectGfxTable;
    ((struct SubEffect *)sub)->f04 = ((struct AnimEntry *)(animTable + (((s32)part->animId) * 0x28)))->w0;
  }
  ((struct SubEffect *)part->subEffect)->f06 = *((u16 *)(&config[0]));
  ((struct SubEffect *)part->subEffect)->f08 = *((u16 *)(&config[2]));
  ((struct SubEffect *)part->subEffect)->f0A = *((u16 *)(&config[4]));
  ((struct SubEffect *)part->subEffect)->f0C = *((u16 *)(&config[6]));
  ((struct SubEffect *)part->subEffect)->f0E = ((struct AnimEntry *)(animTable + (((s32)part->animId) * 0x28)))->w1;
  {
    u8 *se = (u8 *)part->subEffect;
    *((u32 *)(se + 0x10)) = (u32)sprite;
    if (*((u8 *)entity + 0x8C) != 0) {
      se[1] = zero;
    }
  }
  {
    u8 *pt = gCameraState;
    u8 *base1;
    u8 *base2;
    u32 idx;
    idx = ((u32)*(state + 0x18A8) + 1) * 0x40;
    base1 = pt + 0x1278;
    sprite->x = part->f08 - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*(state + 0x18A8) + 1) * 0x40;
    base2 = pt + 0x127C;
    sprite->y = part->f0C - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
  }
  entity->flags |= 0x1000;
  step = *((s16 *)(((u8 *)entity) + 0x22));
  *((((u8 *)entity) + (((s32)step) * 2)) + 0x19) = zero;
  {
    u32 *gptr = &gMainObjTimerCallbacks;
    u8 *p18 = ((u8 *)entity) + 0x18;
    u8 *p22 = ((u8 *)entity) + 0x22;
    sub_080C31E4(p18, p22, *gptr);
    { s16 i2 = *((s16 *)p22); u8 *p19 = (u8 *)((((s32)i2) * 2) + (u32)entity); p19[0x19] = (u8)(p19[0x19] + 1); }
    { s16 i3 = *((s16 *)p22); u8 *q = p18 + (((s32)i3) * 2); sub_080C31E0(entity, *((u32 *)((((u32)(*q)) * 4) + entity->dispatch))); }
  }
}
