/* Main object that owns the spawned effect. */
struct MainObj {
    u8 _00[2]; u16 flags; u8 _04[0x10]; u32 unk14; u8 _18[4]; u32 unk1C;
    u8 _20[2]; s16 index; void *cleanupCb; u8 _28[0x10]; void *object; void *component;
    u8 _40[0xC]; u32 posX; u8 _50[0xC]; u32 posY; u8 _60[0xC];
    u16 spawnFlags; u8 _6E[6]; s16 unk74;
};
/* Newly allocated effect object. */
struct SpawnedObj { u16 flags; u16 flags2; u8 _04[0x10]; u32 worldX; u32 worldY; u32 kind; };
struct GameState { u8 _0[0x18a8]; u8 scrollIndex; u8 _a9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
extern u8 gCameraState[];
extern void *gMainObjTimerCallback;
void *allocSpriteObject(void);
void allocWorkSlot(void *, int, int, int);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, s32, int);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Spawn an effect for a main object, seed its flags and camera-relative world
   coordinates, then dispatch the object's current state script handler. */
void sub_0808E7E0(struct MainObj *arg0) {
    void *object;
    void *component;
    void **cmdTable;
    u8 *scriptPtr;
    u8 *stateBytePtr;

    object = allocSpriteObject();
    if (object == NULL) goto bad;
    arg0->object = object;
    allocWorkSlot(arg0, 0, 0x14, 0);
    component = arg0->component;
    if (component == NULL) {
bad:
        sub_080C31E0(arg0, arg0->cleanupCb);
        return;
    }
    initSpriteGraphics(object, component, (void *)0x08100258);
    setAnimationFrame(object, component, 0x15, 0);
    if (arg0->spawnFlags & 0x10) ((struct SpawnedObj *)object)->flags2 |= 0x10;
    if (arg0->spawnFlags & 0x20) ((struct SpawnedObj *)object)->flags2 |= 0x20;
    ((struct SpawnedObj *)object)->kind = (arg0->spawnFlags & 0x0F) | 0x80000000;
    ((struct SpawnedObj *)object)->flags |= gMainWorkspace.flags;
    {
        u8 *scrollTable = gCameraState;
        u8 *gameState = (u8 *)&gMainWorkspace;
        u8 *scrollXAddr;
        u8 *scrollYAddr;
        u32 scrollIdx;

        gameState += 0x18A8;

        scrollIdx = ((u32)*gameState + 1) * 0x40;
        scrollXAddr = scrollTable + 0x1278;
        *(u32 *)((u8 *)object + 0x14) = *(u32 *)((u8 *)arg0 + 0x4C) - ((*(u32 *)(scrollXAddr + scrollIdx) + 0x8000) & 0xFFFF0000);

        scrollIdx = ((u32)*gameState + 1) * 0x40;
        scrollYAddr = scrollTable + 0x127C;
        *(u32 *)((u8 *)object + 0x18) = *(u32 *)((u8 *)arg0 + 0x5C) - ((*(u32 *)(scrollYAddr + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)((u8 *)arg0 + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = 0;
    cmdTable = &gMainObjTimerCallback;
    scriptPtr = (u8 *)arg0;
    scriptPtr += 0x18;
    sub_080C31E4(scriptPtr, (u8 *)arg0 + 0x22, (s32)*cmdTable);
    *(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) += 1;
    stateBytePtr = scriptPtr + (u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
    sub_080C31E0((u8 *)arg0, *(void **)(*(u8 **)((u8 *)arg0 + 0x14) + *(u8 *)stateBytePtr * 4));
}
