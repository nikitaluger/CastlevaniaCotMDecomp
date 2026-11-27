#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct SpawnLogic { u8 pad0[4]; u16 kind; u8 pad6[2]; u32 moveX, moveY; u8 pad10[0xC]; s16 cfgIndex; u8 pad1E[0x16]; u8 pad34[0x14]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, struct SpawnLogic *b, void (*c)(void));
extern void sub_08037128(void);
extern void initWorkStateForKind(void *a, struct SpawnSprite *b, struct SpawnLogic *c, u32 d, s32 e);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void setAnimationFrame(struct SpawnSprite *a, u8 *b, int c, int d);
extern void allocSpriteConfigPart(void *a, struct SpawnLogic *b, struct SpawnSprite *c);
extern void initThreeSubObjects(void *a, struct SpawnLogic *b, struct SpawnSprite *c, u8 *d);
extern void sub_080C31E0(void *a, u32 b); /* _call_via_r1: dispatch the entity's saved handler */
extern void sub_080C31E4(u8 *a, s16 *b, u32 c); /* _call_via_r2: run the current script step */
extern void registerScriptObject(void *a, u32 b);
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u8 gSpriteAnimDataTable[]; extern u8 gProjectileSpeedTable[]; extern u8 gScriptStepCallbackTable[];

/* Spawn and initialise a scripted three-part projectile: allocate the sprite and work state,
 * install the cleanup handler, pick a launch speed from the table, build the animation and
 * three render parts, align the sprite to the camera scroll, then arm the script and dispatch
 * its first command. */
void spawnTriplePartProjectile(void *entity) {
    struct SpawnSprite *sprite; struct SpawnLogic *work;
    u32 savedParam; s32 zero, speed;
    u8 *animTrack; u8 *camScrollTable, *frameCount, *scrollX, *scrollY;
    u32 scrollRow;
    u8 *stepStream; u8 *currentStep; u8 *scriptCmd;
    u32 *stepCallbackWord; u8 *speedTable;
    savedParam = U32(entity, 0xAC);
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
    work = (struct SpawnLogic *)U32(entity, 0x3C);
    animTrack = (u8 *)work + 0x34;
    installUpdateHandler(entity, work, sub_08037128);
    speedTable = gProjectileSpeedTable;
    speed = *(s16 *)(speedTable + U8(entity, 0x4C) * 4);
    initWorkStateForKind(entity, sprite, work, savedParam, speed);
    zero = 0;
    work->kind = 8;
    initSpriteGraphics(sprite, animTrack, (u8 *)gSpriteAnimDataTable + work->cfgIndex * 12);
    setAnimationFrame(sprite, animTrack, 0, 1);
    allocSpriteConfigPart(entity, work, sprite);
    initThreeSubObjects(entity, work, sprite, (u8 *)work + 0x54);
    camScrollTable = gCameraState;
    frameCount = gMainWorkspace;
    frameCount += 0x18A8;
    scrollRow = ((u32)*frameCount + 1) * 0x40;
    scrollX = camScrollTable + 0x1278;
    sprite->worldX = work->moveX - ((*(u32 *)(scrollX + scrollRow) + 0x8000) & 0xFFFF0000);
    scrollRow = ((u32)*frameCount + 1) * 0x40;
    scrollY = camScrollTable + 0x127C;
    sprite->worldY = work->moveY - ((*(u32 *)(scrollY + scrollRow) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(entity, 0);
    U16(entity, 0x02) = 0x1000 | U16(entity, 0x02);
    U8(entity, 0x19 + (s16)U16(entity, 0x22) * 2) = zero;
    stepCallbackWord = &gScriptStepCallbackTable;
    stepStream = (u8 *)entity + 0x18;
    sub_080C31E4(stepStream, (s16 *)((u8 *)entity + 0x22), *stepCallbackWord);
    currentStep = (u8 *)((s16)U16(entity, 0x22) * 2 + (u32)entity);
    currentStep[0x19] = (u8)(currentStep[0x19] + 1);
    scriptCmd = stepStream + (s16)U16(entity, 0x22) * 2;
    sub_080C31E0(entity, *(u32 *)(U32(entity, 0x14) + *scriptCmd * 4));
}
