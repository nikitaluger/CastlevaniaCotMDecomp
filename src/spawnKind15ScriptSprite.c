/* Build the kind-0x15 scripted sprite for an entity: allocate its sprite and
 * work state, install the graphics and animation, place it using the camera
 * scroll rows, then arm the next script step and run the entity's callback. */
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnLogic { u8 pad0[4]; u16 kind; u8 pad6[2]; u32 moveX, moveY; u8 pad10[0xC]; s16 cfgIndex; u8 pad1E[0x16]; u8 pad34[0x14]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *entity, int a, int b, int c);
extern void installUpdateHandler(void *a, struct SpawnLogic *b, void (*c)(void));
extern void sub_08033498(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct SpawnLogic *c, u32 d, u32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void allocSpriteConfigPart(void *a, struct SpawnLogic *b, struct SpawnSprite *c);
extern void initThreeSubObjects(void *a, struct SpawnLogic *b, struct SpawnSprite *c, void *d);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u8 gSpriteAnimDataTable[]; extern u32 gScriptStepCallbackTable;
extern u32 sub_0805FAEC(void *, u32);
extern void sub_080338F0(void *a, struct SpawnLogic *b, struct SpawnSprite *c);

void spawnKind15ScriptSprite(void *entity) {
    struct SpawnSprite *sprite; struct SpawnLogic *logic;
    u32 spawnParam; s32 zero;
    u8 *animData; u8 *coordTable, *scrollState, *xBase, *yBase;
    u32 coordIndex;
    u8 *scriptData; u8 *stepSlot; u8 *scriptEntry;
    u32 *callbackEntry;
    spawnParam = U32(entity, 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    sub_080C31E0(entity, U32(entity, 0x24));
    return;
ok0:
    U32(entity, 0x38) = (u32)sprite;
    allocWorkSlot(entity, 0, 0x64, 0);
    if (U32(entity, 0x3C) == 0) goto fail;
    goto body;
fail:
    sub_080C31E0(entity, U32(entity, 0x24));
    return;
body:
    sprite->typeId = 0x8000000A;
    logic = (struct SpawnLogic *)U32(entity, 0x3C);
    animData = (u8 *)logic + 0x34;
    installUpdateHandler(entity, logic, sub_08033498);
    initWorkStateForKind(entity, sprite, logic, spawnParam, 0x15);
    zero = 0;
    logic->kind = 8;
    initSpriteGraphics(sprite, animData, (u8 *)gSpriteAnimDataTable + logic->cfgIndex * 12);
    setAnimationFrame(sprite, animData, 0, 1);
    allocSpriteConfigPart(entity, logic, sprite);
    initThreeSubObjects(entity, logic, sprite, (u8 *)logic + 0x54);
    if (sub_0805FAEC(entity, 0xE1) == 0) {
fail1:
        sub_080C31E0(entity, U32(entity, 0x24));
        goto end;
    } else {
        sub_080338F0(entity, logic, sprite);
    }
    coordTable = gCameraState;
    scrollState = gMainWorkspace;
    scrollState += 0x18A8;
    coordIndex = ((u32)*scrollState + 1) * 0x40;
    xBase = coordTable + 0x1278;
    sprite->worldX = logic->moveX - ((*(u32 *)(xBase + coordIndex) + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*scrollState + 1) * 0x40;
    yBase = coordTable + 0x127C;
    sprite->worldY = logic->moveY - ((*(u32 *)(yBase + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(entity, 0);
    U16(entity, 0x02) = 0x1000 | U16(entity, 0x02);
    U8(entity, 0x19 + (s16)U16(entity, 0x22) * 2) = zero;
    callbackEntry = &gScriptStepCallbackTable;
    scriptData = (u8 *)entity + 0x18;
    sub_080C31E4(scriptData, (s16 *)((u8 *)entity + 0x22), *callbackEntry);
    stepSlot = (u8 *)((s16)U16(entity, 0x22) * 2 + (u32)entity);
    stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
    scriptEntry = scriptData + (s16)U16(entity, 0x22) * 2;
    sub_080C31E0(entity, *(u32 *)(U32(entity, 0x14) + *scriptEntry * 4));
end:
    return;
}
