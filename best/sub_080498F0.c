#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
struct SpawnSprite
{
  u16 flags0;
  u8 pad2[0x12];
  u32 worldX;
  u32 worldY;
  u32 typeId;
  u8 pad20[0x60];
};
struct SpawnEntity
{
  u8 _0;
  u8 active;
  u8 kind;
  u8 variant;
  u16 gfxId;
  u16 extra0;
  u16 extra1;
  u16 extra2;
  u16 extra3;
  u16 gfxId2;
  u32 sprite;
};
struct LogicEntityRef
{
  u8 pad[0xC];
  struct SpawnEntity *entity;
};
struct SpawnLogic
{
  u8 pad0[4];
  u16 kind;
  u8 pad6[2];
  u32 moveX;
  u32 moveY;
  u8 pad10[0xC];
  s16 cfgIndex;
  u8 pad1E[0xA];
  struct SpawnEntity *entity;
  u8 pad2C[0x1C];
  u8 req[0x10];
};
struct SpawnSpriteDef
{
  u8 _pad[4];
  u16 gfxId;
  u16 gfxId2;
  u8 _08[0x20];
};
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct SpawnLogic *b, void (*c)(void));
extern void updateScriptedEffectObject(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct SpawnLogic *c, u32 d, s32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void sub_0804A4D0(void *sprite, void *anim, void *req, s32 frame);
extern struct SpawnEntity *allocEffectPart(void);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern void copyPoseAttrs(void *dst, void *src);
extern void setSpriteFlipForDirection(void *sprite, s32 dir);
extern u8 gSpriteAnimDataTable[];
extern u8 gSpriteKindTable[];
extern u16 D_080CF934[];
extern s16 D_080CF95C[];
typedef struct { char pad[2]; u16 value; } __repair_member_u16_2;
typedef struct { short value; } __repair_global_short;
extern __repair_global_short gMainObjTimerCallbacks;
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
void sub_080498F0(void *owner)
{
  s32 dir;
  s32 dir_b1;
  struct SpawnLogic *logic;
  struct SpawnSprite *sprite;
  struct SpawnEntity *entity;
  u32 savedAC;
  u8 *animData;
  u8 *entityRef;
  u16 *attrTable;
  u32 *cmdTable;
  u8 *entries;
  u8 *spriteTable;
  u16 temp;
  savedAC = *((u32 *) (((u8 *) owner) + 0xAC));
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail0;
  }
  goto ok0;
  fail0:
  sub_080C31E0(owner, *((u32 *) (((u8 *) owner) + 0x24)));

 do { return; ok0: *((u32 *) (((u8 *) owner) + 0x38)) = (u32) sprite; allocWorkSlot(owner, 0, 0x54, 0); if ((*((u32 *) (((u8 *) owner) + 0x3C))) == 0) { goto fail; } sprite->typeId = 0x8000000A; logic = (struct SpawnLogic *) (*((u32 *) (((u8 *) owner) + 0x3C))); animData = ((u8 *) logic) + 0x34; entityRef = ((u8 *) logic) + 0x48; installUpdateHandler(owner, logic, updateScriptedEffectObject); initWorkStateForKind(owner, sprite, logic, savedAC, (s32) ((s16) D_080CF95C[(*((u8 *) (((u8 *) owner) + 0x7C))) * 2])); initSpriteGraphics(sprite, animData, ((u8 *) gSpriteAnimDataTable) + (logic->cfgIndex * 12)); if ((*((u8 *) (((u8 *) owner) + 0x6C))) != 0) { sub_0804A4D0(sprite, animData, entityRef, 2); entityRef[0xA] = 1; } else { setAnimationFrame(sprite, animData, 0, 0); sprite->flags0 = (sprite->flags0 & 0xFFF) | 0xC000; } if ((*((u8 *) (((u8 *) owner) + 0x6C))) != 0) { logic->moveX = *((u32 *) (((u8 *) owner) + 0x4C)); logic->moveY = *((u32 *) (((u8 *) owner) + 0x5C)); } attrTable = D_080CF934; logic->entity = allocEffectPart(); if (logic->entity == NULL) { goto fail; } goto fields; fail: sub_080C31E0(owner, *((u32 *) (((u8 *) owner) + 0x24))); return; fields: entity = logic->entity; entity->active = 5; logic->entity->kind = 8; } while (0);
  logic->entity->variant = 1;
  {
    u8 *defBytes = (u8 *) logic->entity;
    spriteTable = gSpriteKindTable;
    ((struct SpawnEntity *) defBytes)->gfxId = *((u16 *) (spriteTable + (((s32) logic->cfgIndex) * 20)));
  }
  logic->entity->extra0 = attrTable[0];
  logic->entity->extra1 = attrTable[1];
  logic->entity->extra2 = attrTable[2];
  logic->entity->extra3 = attrTable[3];
  logic->entity->gfxId2 = *((u16 *) ((spriteTable + (((s32) logic->cfgIndex) * 20)) + 4));
  logic->entity->sprite = (u32) sprite;
  if ((*((u8 *) (((u8 *) owner) + 0x6C))) != 0)
  {
    copyPoseAttrs(logic->entity, ((u8 *) attrTable) + 8);
  }
  else
  {
    s32 dir_b1_arm;
    logic->entity->kind = 0;
    logic->entity->variant = 0;
    {
      u32 _b = *((u8 *) (((u8 *) owner) + 0x70));
      dir_b1_arm = ((s32) (_b << 24) >> 24) * 0xC000;
    }
    *((u32 *) (((u8 *) logic) + 0x10)) = (u32) dir_b1_arm;
    setSpriteFlipForDirection(sprite, dir_b1_arm);
  }
  {
    u8 *pt = gCameraState;
    u8 *sceneState = gMainWorkspace;
    u8 *base1;
    u8 *base2c;
    sceneState += 0x18A8;
    dir_b1 = (((u32) (*sceneState)) + 1) * 0x40;
    base1 = pt + 0x1278;
    sprite->worldX = logic->moveX - (((*((u32 *) (base1 + dir_b1))) + 0x8000) & 0xFFFF0000);
    dir = (((u32) (*sceneState)) + 1) * 0x40;
    base2c = pt + 0x127C;
    sprite->worldY = logic->moveY - (((*((u32 *) (base2c + dir))) + 0xFFFF8000) & 0xFFFF0000);
  }
  registerScriptObject(owner, 0);
  (((__repair_member_u16_2 *) owner)->value) = 0x1000 | (*((u16 *) (((u8 *) owner) + 0x02)));
  *((u8 *) (((u8 *) owner) + (0x19 + (((s16) (*((u16 *) (((u8 *) owner) + 0x22)))) * 2)))) = 0;
  cmdTable = &gMainObjTimerCallbacks.value;
  entries = ((u8 *) owner) + 0x18;
  sub_080C31E4(entries, (s16 *) (((u8 *) owner) + 0x22), *cmdTable);
  {
    s16 slot = *((s16 *) (((u8 *) owner) + 0x22));
    u8 *counterPtr = (u8 *) ((((s32) slot) * 2) + ((u32) owner));
    counterPtr[0x19] = (u8) (counterPtr[0x19] + 1);
  }
  {
    s16 slot2 = *((s16 *) (((u8 *) owner) + 0x22));
    u8 *entry = entries + (((s32) slot2) * 2);
    sub_080C31E0(owner, *((u32 *) ((((u32) (*entry)) * 4) + (*((u32 *) (((u8 *) owner) + 0x14))))));
  }
}
