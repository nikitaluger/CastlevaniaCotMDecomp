/* Spawn the variant-selected sprite of a main object: allocate a sprite and a
 * 0x14-byte work slot, initialize its graphics and animation frame from the
 * shared variant tables, copy the object's spawn flags and camera-relative
 * world coordinates, then advance to and dispatch the next script command.
 * A missing allocation or source object dispatches the failure callback. */
struct MainObject {
    u8 _00[2]; u16 flags2; u8 _04[0x10]; u32 unk14; u8 _18[4]; u32 unk1C;
    u8 _20[2]; s16 scriptIndex; void *failCallback; u8 _28[0x10];
    void *spawnedObj; void *sourceEnt;
    u8 _40[0xC]; u32 coordX; u8 _50[0xC]; u32 coordY; u8 _60[0xC];
    u16 spawnFlags; u8 _6E[6]; s16 variant;
};
struct SpawnedObj { u16 flags0; u16 flags2; u8 _04[0x10]; u32 unk14; u32 coordX; u32 param1C; };
struct GameWorkspace { u8 _0[0x18a8]; u8 flag18A8; u8 _a9[0x19]; u16 mask18C2; };
extern struct GameWorkspace gMainWorkspace;
extern u8 gCameraState[];
extern u32 gSmallVariantSpriteGfxDesc[];
extern s16 gSmallVariantSpriteFrames[];
extern void *gMainObjTimerCallbacks;
void *allocSpriteObject(void);
void allocWorkSlot(void *, int, int, int);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, s16, int);
void _call_via_r1(void *, void *);
void _call_via_r2(void *, void *, s32);

void initVariantSpriteObjectSmall(struct MainObject *self) {
    void *sprite;
    void *childState;
    void **cbTable;
    u8 *scriptPtr;
    u8 *stepPtr;
    s16 variant;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    self->spawnedObj = sprite;
    allocWorkSlot(self, 0, 0x14, 0);
    childState = self->sourceEnt;
    if (childState == NULL) {
fail:
        _call_via_r1(self, self->failCallback);
        return;
    }
    initSpriteGraphics(sprite, childState, gSmallVariantSpriteGfxDesc);
    variant = self->variant;
    setAnimationFrame(sprite, childState, gSmallVariantSpriteFrames[variant], 0);
    if (self->spawnFlags & 0x10) ((struct SpawnedObj *)sprite)->flags2 |= 0x10;
    if (self->spawnFlags & 0x20) ((struct SpawnedObj *)sprite)->flags2 |= 0x20;
    ((struct SpawnedObj *)sprite)->param1C = (self->spawnFlags & 0x0F) | 0x80000000;
    ((struct SpawnedObj *)sprite)->flags0 |= gMainWorkspace.mask18C2;
    {
        u8 *coordTable = gCameraState;
        u8 *globalBase = (u8 *)&gMainWorkspace;
        u8 *xBase;
        u8 *yBase;
        u32 coordIdx;

        globalBase += 0x18A8;

        coordIdx = ((u32)*globalBase + 1) * 0x40;
        xBase = coordTable + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)self + 0x4C) - ((*(u32 *)(xBase + coordIdx) + 0x8000) & 0xFFFF0000);

        coordIdx = ((u32)*globalBase + 1) * 0x40;
        yBase = coordTable + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)self + 0x5C) - ((*(u32 *)(yBase + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)((u8 *)self + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x19) = 0;
    cbTable = &gMainObjTimerCallbacks;
    scriptPtr = (u8 *)self;
    scriptPtr += 0x18;
    _call_via_r2(scriptPtr, (u8 *)self + 0x22, (s32)*cbTable);
    *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x19) += 1;
    stepPtr = scriptPtr + (u32)(*(s16 *)((u8 *)self + 0x22)) * 2;
    _call_via_r1((u8 *)self, *(void **)(*(u8 **)((u8 *)self + 0x14) + *(u8 *)stepPtr * 4));
}
