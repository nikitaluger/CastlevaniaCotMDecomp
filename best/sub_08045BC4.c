#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnEntity { u8 _0, active, kind, variant; u16 gfxId, extra0, extra1, extra2, extra3, gfxId2; u32 sprite; };
struct ExtraRef { u16 val; u8 byte; u8 pad; struct SpawnEntity *effect2; };
struct EffectLogic {
    u8 pad0[4]; u16 kind; u8 pad6[2];
    u32 moveX, moveY, layer;
    u8 pad14[8]; s16 cfgIndex; u8 pad1E[0xA];
    struct SpawnEntity *effect1;
    u8 pad2C[0x1C]; u16 extraVal; u8 extraByte; u8 pad4B;
    struct SpawnEntity *effect2;
};
struct GfxDef20 { u16 gfxId; u16 pad; u16 gfxId2; u8 rest[14]; };
struct GfxDef40 { u16 gfxId; u16 pad; u16 gfxId2; u8 rest[34]; };
struct SpeedEntry { s16 animId; u8 pad[2]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct EffectLogic *b, void (*c)(void));
extern void sub_0804647C(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct EffectLogic *c, u32 d, u32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void setSpriteFacingToTarget(struct SpawnSprite *a, u32 b);
extern struct SpawnEntity *allocEffectPart(void);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern struct GfxDef40 gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[]; extern struct SpeedEntry gEffectKindBySelector[];
extern s16 D_080CF858[]; extern u16 gSpriteKindTable[]; extern struct GfxDef20 D_080CF5D8[];
extern u32 gMainObjTimerCallbacks;

void sub_08045BC4(void *owner) {
    struct EffectLogic *logic; struct SpawnSprite *sprite;
    u32 savedAC; s32 zero;
    u8 *animData; struct ExtraRef *extraRef; s16 animId; s16 frame; u32 layer; u8 kind;
    u16 *attrTable; u32 *cmdTable; u8 *entries;

    savedAC = U32(owner, 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) { sub_080C31E0(owner, U32(owner, 0x24)); return; }
    U32(owner, 0x38) = (u32)sprite;
    allocWorkSlot(owner, 0, 0x50, 0);
    if (U32(owner, 0x3C) == 0) { sub_080C31E0(owner, U32(owner, 0x24)); return; }
    sprite->typeId = 0x8000000A;
    logic = (struct EffectLogic *)U32(owner, 0x3C);
    animData = (u8 *)logic + 0x34;
    extraRef = (struct ExtraRef *)((u8 *)logic + 0x48);
    installUpdateHandler(owner, logic, sub_0804647C);
    animId = gEffectKindBySelector[U8(owner, 0x4C)].animId;
    initWorkStateForKind(owner, sprite, logic, savedAC, (u32)animId);
    logic->kind = 8;
    initSpriteGraphics(sprite, animData, (u8 *)gSpriteAnimDataTable + logic->cfgIndex * 12);
    frame = D_080CF858[U8(owner, 0x4C)];
    setAnimationFrame(sprite, animData, frame, 1);
    kind = 8;
    setSpriteFacingToTarget(sprite, logic->moveX);
    layer = 0xFFFFD000;
    if (sprite->flags0 & 0x10) layer = 0x3000;
    logic->layer = layer;
    extraRef->val = U16(sprite, 0x28);
    extraRef->byte = 0x18;
    attrTable = gSpriteKindTable;
    logic->effect1 = allocEffectPart();
    if (logic->effect1 == NULL) { sub_080C31E0(owner, U32(owner, 0x24)); return; }
    logic->effect1->active = 5;
    logic->effect1->kind = kind;
    logic->effect1->variant = 1;
    logic->effect1->gfxId = D_080CF5D8[logic->cfgIndex].gfxId;
    logic->effect1->extra0 = attrTable[0];
    logic->effect1->extra1 = attrTable[1];
    logic->effect1->extra2 = attrTable[2];
    logic->effect1->extra3 = attrTable[3];
    logic->effect1->gfxId2 = D_080CF5D8[logic->cfgIndex].gfxId2;
    logic->effect1->sprite = (u32)sprite;
    extraRef->effect2 = allocEffectPart();
    if (extraRef->effect2 == NULL) { sub_080C31E0(owner, U32(owner, 0x24)); return; }
    extraRef->effect2->active = zero;
    extraRef->effect2->kind = (u8)(u32)sprite;
    extraRef->effect2->variant = (u8)(u32)sprite;
    extraRef->effect2->gfxId = gEffectGfxTable[logic->cfgIndex].gfxId;
    extraRef->effect2->extra0 = attrTable[0];
    extraRef->effect2->extra1 = attrTable[1];
    extraRef->effect2->extra2 = attrTable[2];
    extraRef->effect2->extra3 = attrTable[3];
    extraRef->effect2->gfxId2 = gEffectGfxTable[logic->cfgIndex].gfxId2;
    extraRef->effect2->sprite = (u32)sprite;
    {
      u8 *pt = gCameraState;
      u8 *sceneState = gMainWorkspace;
      u8 *base1; u8 *base2c; u32 coordIndex;
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
    cmdTable = &gMainObjTimerCallbacks; entries = (u8 *)owner + 0x18;
    sub_080C31E4(entries, (s16 *)((u8 *)owner + 0x22), *cmdTable);
    { s16 slot = *((s16 *)((u8 *)owner + 0x22)); u8 *counterPtr = (u8 *)((((s32)slot)*2)+(u32)owner); counterPtr[0x19] = (u8)(counterPtr[0x19]+1); }
    { s16 slot2 = *((s16 *)((u8 *)owner + 0x22)); u8 *entry = entries + (((s32)slot2)*2); sub_080C31E0(owner, *(u32 *)((((u32)(*entry))*4)+U32(owner,0x14))); }
}
