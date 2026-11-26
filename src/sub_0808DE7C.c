/* Spawns a companion object from the pool, initializes it from the source
 * entity and a graphics table, copies the entity's position and spawn flags,
 * then advances the action byte and dispatches the next script handler. */
struct Entity {
    u8 _00[2]; u16 flags2; u8 _04[0x10]; u32 unk14; u8 _18[4]; u32 unk1C;
    u8 _20[2]; s16 scriptIndex; void *failCallback; u8 _28[0x10];
    void *spawnedObj; void *sourceEnt;
    u8 _40[0xC]; u32 coordX; u8 _50[0xC]; u32 coordY; u8 _60[0xC];
    u16 spawnFlags; u8 _6E[6]; s16 variant;
};
struct SpawnedObj { u16 flags0; u16 flags2; u8 _04[0x10]; u32 unk14; u32 coordX; u32 param1C; };
struct GlobalData { u8 _0[0x18a8]; u8 flag18A8; u8 _a9[0x19]; u16 mask18C2; };
extern struct GlobalData gMainWorkspace;
extern u8 gCameraState[];
extern u32 D_08100218[];
extern s16 D_08100224[];
extern void *gMainObjTimerCallback;
void *allocSpriteObject(void);
void allocWorkSlot(void *, int, int, int);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, s16, int);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

void sub_0808DE7C(struct Entity *self) {
    void *newObj;
    void *source;
    void **cbTable;
    u8 *scriptPtr;
    u8 *cmdPtr;
    s16 variant;

    newObj = allocSpriteObject();
    if (newObj == NULL) goto fail;
    self->spawnedObj = newObj;
    allocWorkSlot(self, 0, 0x14, 0);
    source = self->sourceEnt;
    if (source == NULL) {
fail:
        sub_080C31E0(self, self->failCallback);
        return;
    }
    initSpriteGraphics(newObj, source, D_08100218);
    variant = self->variant;
    setAnimationFrame(newObj, source, D_08100224[variant], 0);
    if (self->spawnFlags & 0x10) ((struct SpawnedObj *)newObj)->flags2 |= 0x10;
    if (self->spawnFlags & 0x20) ((struct SpawnedObj *)newObj)->flags2 |= 0x20;
    ((struct SpawnedObj *)newObj)->param1C = (self->spawnFlags & 0x0F) | 0x80000000;
    ((struct SpawnedObj *)newObj)->flags0 |= gMainWorkspace.mask18C2;
    {
        u8 *coordTable = gCameraState;
        u8 *globalBase = (u8 *)&gMainWorkspace;
        u8 *xBase;
        u8 *yBase;
        u32 coordIdx;

        globalBase += 0x18A8;

        coordIdx = ((u32)*globalBase + 1) * 0x40;
        xBase = coordTable + 0x1278;
        *(u32 *)((u8 *)newObj + 0x14) = *(u32 *)((u8 *)self + 0x4C) - ((*(u32 *)(xBase + coordIdx) + 0x8000) & 0xFFFF0000);

        coordIdx = ((u32)*globalBase + 1) * 0x40;
        yBase = coordTable + 0x127C;
        *(u32 *)((u8 *)newObj + 0x18) = *(u32 *)((u8 *)self + 0x5C) - ((*(u32 *)(yBase + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)((u8 *)self + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x19) = 0;
    cbTable = &gMainObjTimerCallback;
    scriptPtr = (u8 *)self;
    scriptPtr += 0x18;
    sub_080C31E4(scriptPtr, (u8 *)self + 0x22, (s32)*cbTable);
    *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x19) += 1;
    cmdPtr = scriptPtr + (u32)(*(s16 *)((u8 *)self + 0x22)) * 2;
    sub_080C31E0((u8 *)self, *(void **)(*(u8 **)((u8 *)self + 0x14) + *(u8 *)cmdPtr * 4));
}
