#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnLogic { u8 pad0[4]; u16 kind; u8 pad6[2]; u32 moveX, moveY; u8 pad10[0xC]; s16 cfgIndex; u8 pad1E[0x16]; u8 pad34[0x14]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct SpawnLogic *b, void (*c)(void));
extern void sub_08014290(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct SpawnLogic *c, u32 d, u32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void allocSpriteConfigPart(void *a, struct SpawnLogic *b, struct SpawnSprite *c);
extern void *spawnBudgetedEffect(void *a, int b);
extern void _call_via_r1(void *a, u32 b);
extern void _call_via_r2(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u8 gSpriteAnimDataTable[]; extern u32 gMainObjTimerCallbacks;

void sub_08039E24(void *arg0) {
    struct SpawnSprite *sprite;
    struct SpawnLogic *logic;
    u32 savedAC;
    s32 zero;
    u8 *animData;
    void *effect;
    s16 *tileTable;
    u8 *coordTable, *scrollState, *xBase, *yBase;
    u32 coordIndex;
    u8 *scriptData;
    u32 *audioCmd;

    savedAC = U32(arg0, 0xAC);
    sprite = allocSpriteObject();
    if (sprite == 0) {
        _call_via_r1(arg0, U32(arg0, 0x24));
        return;
    }
    U32(arg0, 0x38) = (u32)sprite;
    allocWorkSlot(arg0, 0, 0x58, 0);
    if (U32(arg0, 0x3C) == 0) {
        _call_via_r1(arg0, U32(arg0, 0x24));
        return;
    }
    sprite->typeId = 0x8000000A;
    logic = (struct SpawnLogic *)U32(arg0, 0x3C);
    animData = (u8 *)logic + 0x34;
    installUpdateHandler(arg0, logic, sub_08014290);
    tileTable = (s16 *)0x080CD400;
    initWorkStateForKind(arg0, sprite, logic, savedAC, tileTable[U8(arg0, 0x4C) * 2]);
    do { zero = 0; } while (0);
    logic->kind = 8;
    initSpriteGraphics(sprite, animData, (u8 *)gSpriteAnimDataTable + logic->cfgIndex * 12);
    setAnimationFrame(sprite, animData, 0, 1);
    allocSpriteConfigPart(arg0, logic, sprite);
    effect = spawnBudgetedEffect(arg0, 0xF3);
    if (effect == 0) {
        _call_via_r1(arg0, U32(arg0, 0x24));
        return;
    }
    U8(effect, 0x4C) = U8(arg0, 0x4C);
    U8(effect, 0x7C) = 0;
    coordTable = gCameraState;
    scrollState = gMainWorkspace;
    scrollState += 0x18A8;
    coordIndex = ((u32)*scrollState + 1) * 0x40;
    xBase = coordTable + 0x1278;
    sprite->worldX = logic->moveX - ((*(u32 *)(xBase + coordIndex) + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*scrollState + 1) * 0x40;
    yBase = coordTable + 0x127C;
    sprite->worldY = logic->moveY - ((*(u32 *)(yBase + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(arg0, 0);
    U16(arg0, 0x02) = 0x1000 | U16(arg0, 0x02);
    U8(arg0, 0x19 + (s16)U16(arg0, 0x22) * 2) = zero;
    audioCmd = &gMainObjTimerCallbacks;
    scriptData = (u8 *)arg0 + 0x18;
    _call_via_r2(scriptData, (s16 *)((u8 *)arg0 + 0x22), *audioCmd);
    {
        u8 *stepSlot;
        stepSlot = (u8 *)((s16)U16(arg0, 0x22) * 2 + (u32)arg0);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        {
            u8 *scriptEntry;
            scriptEntry = scriptData + (s16)U16(arg0, 0x22) * 2;
            _call_via_r1(arg0, *(u32 *)(U32(arg0, 0x14) + *scriptEntry * 4));
        }
    }
}
