#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SceneStateView { u8 pad[0x18A8]; u8 camera; u8 pad2[0x18C2 - 0x18A9]; u16 val; };
struct CoordTableView { u8 pad[0x1278]; u32 x, y; };
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnEntity {
    u8 _0, active, kind, variant;
    u16 gfxId, extra0, extra1, extra2, extra3, gfxId2;
    u32 sprite;
};
struct LogicEntityRef { u8 pad[0xC]; struct SpawnEntity *entity; };
struct SpawnLogic {
    u8 pad0[4]; u16 kind; u8 pad6[2];
    u32 moveX, moveY;
    u8 pad10[0xC]; s16 cfgIndex; u8 pad1E[0x16];
    struct LogicEntityRef *unusedPtr; u8 pad38[0x14];
};
struct SpawnSpriteDef { u8 _pad[4]; u16 gfxId; u16 gfxId2; u8 _08[0x20]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct SpawnLogic *b, void (*c)(void));
extern void sub_0803443C(void);
extern void sub_080141F8(void *a, struct SpawnSprite *b, struct SpawnLogic *c, u32 d, u32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void sub_0803AEF0(void *a, struct SpawnLogic *b, struct SpawnSprite *c);
extern struct SpawnEntity *allocEffectPart(void);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u8 gEffectGfxTable[]; extern u8 gSpriteAnimDataTable[]; extern u16 D_080CEDB4[]; extern u32 gMainObjTimerCallback;

/* Spawns a larger attack entity: allocates a sprite, logic state and entity,
 * initialises them from animation/sprite tables, sets world coordinates from the
 * scroll table, and records the attack on its owner. */
void sub_080339F0(void *owner) {
    struct SpawnLogic *logic; struct SpawnSprite *sprite; struct SpawnEntity *entity;
    u32 savedAC; s32 zero;
    u8 *animData; struct LogicEntityRef *entityRef; u32 t1, t2, i1, i2;
    u16 *attrTable; u32 *cmdTable; u8 *entries; u8 *spriteTable;
    savedAC = U32(owner, 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    sub_080C31E0(owner, U32(owner, 0x24));
    return;
ok0:
    U32(owner, 0x38) = (u32)sprite;
    allocWorkSlot(owner, 0, 0x5C, 0);
    if (U32(owner, 0x3C) == 0) goto fail;
    sprite->typeId = 0x8000000A;
    logic = (struct SpawnLogic *)U32(owner, 0x3C);
    animData = (u8 *)logic + 0x34;
    entityRef = (struct LogicEntityRef *)((u8 *)logic + 0x48);
    installUpdateHandler(owner, logic, sub_0803443C);
    sub_080141F8(owner, sprite, logic, savedAC, 0x17);
    zero = 0;
    logic->kind = 8;
    initSpriteGraphics(sprite, animData, (u8 *)gSpriteAnimDataTable + logic->cfgIndex * 12);
    setAnimationFrame(sprite, animData, 0, 1);
    sub_0803AEF0(owner, logic, sprite);
    attrTable = D_080CEDB4;
    entityRef->entity = allocEffectPart();
    if (entityRef->entity == NULL) goto fail;
    goto fields;
fail:
    sub_080C31E0(owner, U32(owner, 0x24));
    return;
fields:
    entity = entityRef->entity; entity->active = zero; entityRef->entity->kind = 8; entityRef->entity->variant = 1;
    { u8 *defBytes = (u8 *)entityRef->entity; spriteTable = gEffectGfxTable; ((struct SpawnEntity *) defBytes)->gfxId = ((struct SpawnSpriteDef *) (spriteTable + (((s32) logic->cfgIndex) * 40)))->gfxId; }
    ((struct SpawnEntity *) entityRef->entity)->extra0 = attrTable[0];
    ((struct SpawnEntity *) entityRef->entity)->extra1 = attrTable[1];
    ((struct SpawnEntity *) entityRef->entity)->extra2 = attrTable[2];
    ((struct SpawnEntity *) entityRef->entity)->extra3 = attrTable[3];
    ((struct SpawnEntity *) entityRef->entity)->gfxId2 = ((struct SpawnSpriteDef *) (spriteTable + (((s32) logic->cfgIndex) * 40)))->gfxId2;
    ((struct SpawnEntity *) entityRef->entity)->sprite = (u32)sprite;
    {
      u8 *pt = gCameraState;
      u8 *sceneState = gMainWorkspace;
      u8 *base1;
      u8 *base2c;
      u32 coordIndex;
      sceneState += 0x18A8;
      coordIndex = ((u32)*sceneState + 1) * 0x40;
      base1 = pt + 0x1278;
      sprite->worldX = logic->moveX - ((*(u32 *)(base1 + coordIndex) + 0x8000) & 0xFFFF0000);
      coordIndex = ((u32)*sceneState + 1) * 0x40;
      base2c = pt + 0x127C;
      sprite->worldY = logic->moveY - ((*(u32 *)(base2c + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
    }
    registerScriptObject(owner, 0);
    U16(owner, 0x02) = 0x1000 | U16(owner, 0x02);
    U8(owner, 0x19 + (s16)U16(owner, 0x22) * 2) = zero;
    cmdTable = &gMainObjTimerCallback; entries = (u8 *)owner + 0x18;
    sub_080C31E4(entries, (s16 *)((u8 *)owner + 0x22), *cmdTable);
    { s16 slot = *((s16 *)((u8 *)owner + 0x22)); u8 *counterPtr = (u8 *)((((s32) slot) * 2) + (u32) owner); counterPtr[0x19] = (u8) (counterPtr[0x19] + 1); }
    { s16 slot2 = *((s16 *)((u8 *)owner + 0x22)); u8 *entry = entries + (((s32) slot2) * 2); sub_080C31E0(owner, *(u32 *) ((((u32) (*entry)) * 4) + U32(owner, 0x14))); }
}
