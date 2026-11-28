struct Entity {
    u8 _0[2];
    u16 flags;          /* 0x02 */
    u8 _04[0x10];
    u32 dispatch;       /* 0x14 */
    u8 _18[0xA];
    s16 step;           /* 0x22 */
    u32 script;         /* 0x24 */
    u8 _28[0x10];
    u32 object;         /* 0x38 */
    u32 part;           /* 0x3C */
    u8 _40[0xC];
    u8 variant;         /* 0x4C */
    u8 _4D[0xF];
    u32 x;              /* 0x5C */
    u8 _60[0xC];
    u32 y;              /* 0x6C */
    u8 _70[0xC];
    u8 offsetIndex;     /* 0x7C */
    u8 _7D[3];
    u8 flipFlag;        /* 0x80 */
    u8 _81[0x7F];
};
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
    u32 anim;           /* 0x34 */
};
struct SpriteObj {
    u16 graphics;       /* 0x00 */
    u16 renderFlags;    /* 0x02 */
    u8 _04[0x10];
    u32 x;              /* 0x14 */
    u32 y;              /* 0x18 */
    u32 typeFlags;      /* 0x1C */
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
void setObjectAnimationFrame(void *, void *, u32, u32);
void *allocEffectPart(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
extern u8 gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u32 D_080CF188[];
extern u16 D_080CF1C0[];
extern u8 D_080CF1D8[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

void sub_0803AA4C(struct Entity *entity)
{
  struct SpriteObj *sprite;
  struct Part *part;
  u8 *anim;
  u8 *workspace;
  u8 *config;
  u8 *gfxTable;
  u32 graphics;
  u32 kindSlot;
  s16 stepIndex;
  int temp;
  sprite = (struct SpriteObj *) allocSpriteObject();
  if (sprite == NULL) {
sub_080C31E0(entity, entity->script);
return;
}
  entity->object = (u32) sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if (entity->part == 0) {
sub_080C31E0(entity, entity->script);
return;
}
  sprite->typeFlags = 0x80000009;
  part = (struct Part *) entity->part;
  anim = ((u8 *) part) + 0x34;
  installUpdateHandler(entity, part, &sub_08014290);
  if (entity->flipFlag != 0) {
    u32 temp2;
    sprite->renderFlags |= 0x10;
    temp2 = *((u32 *)(D_080CF1D8 + (entity->offsetIndex << 3)));
    part->x = entity->x - temp2;
  } else {
    sprite->renderFlags &= 0xFFEF;
    part->x = *((u32 *)(D_080CF1D8 + (entity->offsetIndex << 3))) + entity->x;
  }
  temp = (entity->offsetIndex << 3) + 4;
  part->y = entity->y + *((u32 *)(D_080CF1D8 + temp));
  part->animId = (s16) D_080CF188[entity->variant];
  kindSlot = findKindIndex(part->animId);
  part->animSlot = (u16) kindSlot;
  if (((s16) ((u16) kindSlot)) < 0) {
sub_080C31E0(entity, entity->script);
return;
}
  graphics = ((u32) (((s32) ((s16) part->animSlot)) << 6)) + (0x80 << 2);
  graphics |= (kindSlot + 8) << 12;
  sprite->graphics = (u16) graphics;
  workspace = gMainWorkspace;
  graphics |= *((u16 *) (workspace + 0x18C2));
  sprite->graphics = (u16) graphics;
  initSpriteGraphics(sprite, anim, (void *) (gSpriteAnimDataTable + (12 * ((s32) part->animId))));
  setObjectAnimationFrame(sprite, anim, 0x1E, 0);
  config = (u8 *) D_080CF1C0;
  part->subEffect = (u32) allocEffectPart();
  if (part->subEffect == 0) {
sub_080C31E0(entity, entity->script);
return;
}
  goto cont;

  do { do { sub_080C31E0(entity, entity->script); } while (0); } while (0);
  return;
cont:
  ((u8 *) part->subEffect)[1] = 0;
  ((u8 *) part->subEffect)[2] = 8;
  ((u8 *) part->subEffect)[3] = 1;
  { u8 *layer = (u8 *) part->subEffect; gfxTable = gEffectGfxTable; ((struct SubEffect *) layer)->f04 = ((struct AnimEntry *) (gfxTable + (((s32) part->animId) * 40)))->w0; }
  ((struct SubEffect *) part->subEffect)->f06 = *((u16 *) (&config[0]));
  ((struct SubEffect *) part->subEffect)->f08 = *((u16 *) (&config[2]));
  ((struct SubEffect *) part->subEffect)->f0A = *((u16 *) (&config[4]));
  ((struct SubEffect *) part->subEffect)->f0C = *((u16 *) (&config[6]));
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
    temp = ((u32)*(workspace + 0x18A8) + 1); rowIndex = temp * 0x40;
    scrollYRow = scroll + 0x127C;
    sprite->y = part->y - ((*(u32 *)(scrollYRow + rowIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  entity->flags |= 0x10;
  stepIndex = *((s16 *) (((u8 *) entity) + 0x22));
  *((((u8 *) entity) + (((s32) stepIndex) * 2)) + 0x19) = 0;
  {
    u32 *timerCallback = &gMainObjTimerCallbacks;
    u8 *steps = ((u8 *) entity) + 0x18;
    u8 *stepIndexPtr = ((u8 *) entity) + 0x22;
    sub_080C31E4(steps, stepIndexPtr, *timerCallback);
    { s16 stepA = *((s16 *) stepIndexPtr); u8 *stepByte = (u8 *)((((s32) stepA) * 2) + (u32) entity); stepByte[0x19] = (u8) (stepByte[0x19] + 1); }
    { s16 stepB = *((s16 *) stepIndexPtr); u8 *handler = steps + (((s32) stepB) * 2); do { do { sub_080C31E0(entity, *((u32 *) ((((u32) (*handler)) * 4) + entity->dispatch))); } while (0); } while (0); }
  }
}
