#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnLogic { u8 pad0[4]; u16 kind; u8 pad6[2]; u32 moveX, moveY; u8 pad10[0xC]; s16 cfgIndex; u8 pad1E[0x16]; u8 pad34[0x14]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct SpawnLogic *b, void (*c)(void));
extern void updateActorEffectSubObject(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct SpawnLogic *c, u32 d, s32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern u32 gMainWorkspace[]; extern u8 gSpriteAnimDataTable[]; extern u32 gMainObjTimerCallbacks;

/*
 * Spawns a sprite for a scripted task: allocates it, sets up its movement
 * logic and animation from the config table, then dispatches the current
 * step's handler from the table at task+0x14.
 */
void sub_080B96E8(void *task) {
    struct SpawnSprite *sprite; struct SpawnLogic *logic;
    u32 savedState; s32 zero;
    u8 *animData;
    u8 *stepEntries; u8 *stepState; u8 *stepEntry;
    u32 *endCallbacks;
    savedState = U32(task, 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    sub_080C31E0(task, U32(task, 0x24));
    return;
ok0:
    U32(task, 0x38) = (u32)sprite;
    allocWorkSlot(task, 0, 0x48, 0);
    if (U32(task, 0x3C) == 0) goto fail;
    goto body;
fail:
    sub_080C31E0(task, U32(task, 0x24));
    return;
body:
    sprite->typeId = 0x14;
    logic = (struct SpawnLogic *)U32(task, 0x3C);
    animData = (u8 *)logic + 0x34;
    installUpdateHandler(task, logic, updateActorEffectSubObject);
    initWorkStateForKind(task, sprite, logic, savedState, 0x67);
    sprite->flags0 = sprite->flags0 & 0x0FFF;
    zero = 0;
    initSpriteGraphics(sprite, animData, (u8 *)gSpriteAnimDataTable + logic->cfgIndex * 12);
    setAnimationFrame(sprite, animData, 0x29, 0);
    gMainWorkspace[0x10] = (u32)zero;
    U16(task, 0x02) = 0x1000 | U16(task, 0x02);
    U8(task, 0x19 + (s16)U16(task, 0x22) * 2) = (u8)zero;
    endCallbacks = &gMainObjTimerCallbacks;
    stepEntries = (u8 *)task + 0x18;
    sub_080C31E4(stepEntries, (s16 *)((u8 *)task + 0x22), *endCallbacks);
    stepState = (u8 *)((s16)U16(task, 0x22) * 2 + (u32)task);
    stepState[0x19] = (u8)(stepState[0x19] + 1);
    stepEntry = stepEntries + (s16)U16(task, 0x22) * 2;
    sub_080C31E0(task, *(u32 *)(U32(task, 0x14) + *stepEntry * 4));
}
