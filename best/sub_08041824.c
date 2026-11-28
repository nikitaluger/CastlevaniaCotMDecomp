#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnEntity {
    u8 _0, active, kind, variant;
    u16 gfxId, extra0, extra1, extra2, extra3, gfxId2;
    u32 sprite;
};
struct LogicEntityRef { u8 pad[4]; struct SpawnEntity *entity; };
struct SpawnSpriteDef { u8 _pad[4]; u16 gfxId; u16 gfxId2; u8 _08[0x20]; };
struct TargetLogic {
    u8 pad0[4]; u16 kind; u8 pad6[2];
    u32 moveX, moveY;
    u8 pad10[0xC]; s16 cfgIndex; u8 pad1E[0xA];
    struct SpawnEntity *ent1;
    u8 pad2C[0x1C];
};

extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct TargetLogic *b, void (*c)(void));
extern void sub_080420F4(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct TargetLogic *c, u32 d, s32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(void *a, void *b, u16 c, u8 d);
extern void setSpriteFacingToTarget(struct SpawnSprite *a, u32 b);
extern struct SpawnEntity *allocEffectPart(void);
extern void registerScriptObject(void *a, u32 b);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u8 gSpriteAnimDataTable[];
extern u8 gEffectGfxTable[]; extern u16 D_080CF4C8[]; extern u16 D_080CF4D0[];
extern u8 D_080CF4F0[]; extern u32 gMainObjTimerCallbacks;

void sub_08041824(void *owner) {
    u8 *__base_D_080CF4F0;
    struct TargetLogic *logic; struct SpawnSprite *sprite;
    struct LogicEntityRef *entityRef;
    u32 savedAC; s32 zero;
    u8 *animData; u16 *attrTable; u8 *spriteTable;

    savedAC = U32(owner, 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    sub_080C31E0(owner, U32(owner, 0x24));
    return;
ok0:
    U32(owner, 0x38) = (u32)sprite;
    allocWorkSlot(owner, 0, 0x50, 0);
    if (U32(owner, 0x3C) == 0) goto fail;
    sprite->typeId = 0x8000000A;
    logic = (struct TargetLogic *)U32(owner, 0x3C);
    animData = (u8 *)logic + 0x34;
    entityRef = (struct LogicEntityRef *)((u8 *)logic + 0x48);
    installUpdateHandler(owner, logic, sub_080420F4);
    __base_D_080CF4F0 = D_080CF4F0;
    initWorkStateForKind(owner, sprite, logic, savedAC, *(s16 *)(__base_D_080CF4F0 + U8(owner, 0x4C) * 4));
    initSpriteGraphics(sprite, animData, (u8 *)gSpriteAnimDataTable + logic->cfgIndex * 12);
    setAnimationFrame(sprite, animData, 0, 0);
    zero = 0;
    logic->kind = 8;
    setSpriteFacingToTarget(sprite, logic->moveX);
    attrTable = D_080CF4C8;
    logic->ent1 = allocEffectPart();
    if (logic->ent1 == NULL) goto fail;
    logic->ent1->active = 5;
    logic->ent1->kind = 8;
    logic->ent1->variant = 1;
    spriteTable = gEffectGfxTable;
    logic->ent1->gfxId = ((u16 *)(spriteTable + logic->cfgIndex * 20))[0];
    logic->ent1->extra0 = attrTable[0];
    logic->ent1->extra1 = attrTable[1];
    logic->ent1->extra2 = attrTable[2];
    logic->ent1->extra3 = attrTable[3];
    logic->ent1->gfxId2 = ((u16 *)(spriteTable + logic->cfgIndex * 20))[2];
    logic->ent1->sprite = (u32)sprite;
    attrTable = D_080CF4D0;
    entityRef->entity = allocEffectPart();
    if (entityRef->entity == NULL) goto fail;
    entityRef->entity->active = zero;
    entityRef->entity->kind = 8;
    entityRef->entity->variant = 1;
    entityRef->entity->gfxId = ((struct SpawnSpriteDef *)(spriteTable + logic->cfgIndex * 40))->gfxId;
    entityRef->entity->extra0 = attrTable[0];
    entityRef->entity->extra1 = attrTable[1];
    entityRef->entity->extra2 = attrTable[2];
    entityRef->entity->extra3 = attrTable[3];
    entityRef->entity->gfxId2 = ((struct SpawnSpriteDef *)(spriteTable + logic->cfgIndex * 40))->gfxId2;
    entityRef->entity->sprite = (u32)sprite;
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
    { const u32 *cmdTable = &gMainObjTimerCallbacks; u8 *entries = (u8 *)owner + 0x18; sub_080C31E4(entries, (s16 *)((u8 *)owner + 0x22), *cmdTable); }
    { s16 slot = *((s16 *)((u8 *)owner + 0x22)); u8 *counterPtr = (u8 *)((((s32) slot) * 2) + (u32) owner); counterPtr[0x19] = (u8) (counterPtr[0x19] + 1); }
    { s16 slot2 = *((s16 *)((u8 *)owner + 0x22)); u8 *entry = (u8 *)owner + 0x18 + (((s32) slot2) * 2); sub_080C31E0(owner, *(u32 *) ((((u32) (*entry)) * 4) + U32(owner, 0x14))); }
    return;
fail:
    sub_080C31E0(owner, U32(owner, 0x24));
}
