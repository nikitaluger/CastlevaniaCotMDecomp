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
extern void *gMainObjTimerCallbacks;
void *allocSpriteObject(void);
void allocWorkSlot(void *, int, int, int);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, s32, int);
void _call_via_r1(void *, void *);
void _call_via_r2(void *, void *, s32);

/* Spawn a sprite effect for a main object: allocate the object and a work slot,
   seed its flags and camera-relative world coordinates from the object's spawn
   parameters, then dispatch the object's current script step. */
void spawnMainObjectSpriteEffect(struct MainObj *obj) {
    void *object;
    void *component;
    void **cmdTable;
    u8 *scriptPtr;
    u8 *stateBytePtr;

    object = allocSpriteObject();
    if (object == NULL) goto bad;
    obj->object = object;
    allocWorkSlot(obj, 0, 0x14, 0);
    component = obj->component;
    if (component == NULL) {
bad:
        _call_via_r1(obj, obj->cleanupCb);
        return;
    }
    initSpriteGraphics(object, component, (void *)MAIN_OBJ_SPRITE_EFFECT_ANIM_DESC);
    setAnimationFrame(object, component, 0x15, 0);
    if (obj->spawnFlags & 0x10) ((struct SpawnedObj *)object)->flags2 |= 0x10;
    if (obj->spawnFlags & 0x20) ((struct SpawnedObj *)object)->flags2 |= 0x20;
    ((struct SpawnedObj *)object)->kind = (obj->spawnFlags & 0x0F) | 0x80000000;
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
        *(u32 *)((u8 *)object + 0x14) = *(u32 *)((u8 *)obj + 0x4C) - ((*(u32 *)(scrollXAddr + scrollIdx) + 0x8000) & 0xFFFF0000);

        scrollIdx = ((u32)*gameState + 1) * 0x40;
        scrollYAddr = scrollTable + 0x127C;
        *(u32 *)((u8 *)object + 0x18) = *(u32 *)((u8 *)obj + 0x5C) - ((*(u32 *)(scrollYAddr + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)((u8 *)obj + 2) |= EFFECT_SPRITE_READY;
    *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x19) = 0;
    cmdTable = &gMainObjTimerCallbacks;
    scriptPtr = (u8 *)obj;
    scriptPtr += 0x18;
    _call_via_r2(scriptPtr, (u8 *)obj + 0x22, (s32)*cmdTable);
    *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x19) += 1;
    stateBytePtr = scriptPtr + (u32)(*(s16 *)((u8 *)obj + 0x22)) * 2;
    _call_via_r1((u8 *)obj, *(void **)(*(u8 **)((u8 *)obj + 0x14) + *(u8 *)stateBytePtr * 4));
}
