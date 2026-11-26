extern void sub_08013CF4(void *, s32, s32);
extern void sub_08013EEC(void *);
extern void sub_08015974(void);
extern void sub_08016678(void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct FlagDst { u16 flags; };

/* Actor update: derive world X/Y from the work's tile indices and the camera
 * coordinate table, apply the position/score updates, set the owner's flag,
 * release a pending work callback and run the tail handler. */
void sub_08013AC4(void *arg0) {
    void *self = arg0;
    void *ownerFlags = *(void **)((u8 *)self + 0xAC);
    void *work = *(void **)((u8 *)self + 0x3C);
    s32 *tileTable = *(s32 **)((u8 *)work + 0x28);
    u8 *coordTable;
    u8 *cameraIndex;
    u8 *xBase;
    u8 *yBase;
    u32 coordOffset;
    s32 worldX;
    s32 worldY;

    worldX = ((s32)((s16 *)tileTable)[0x18] << 16) + 0x8000;

    coordTable = gCameraState;
    cameraIndex = gMainWorkspace;
    cameraIndex += 0x18A8;
    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    xBase = coordTable + 0x1278;
    worldX += *(s32 *)(xBase + coordOffset);

    worldY = ((s32)((s16 *)tileTable)[0x19] << 16) + (s32)0xFFFF8000;
    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    yBase = coordTable + 0x127C;
    worldY += *(s32 *)(yBase + coordOffset);

    sub_08013CF4(work, worldX, worldY);
    sub_08013EEC(work);

    if (ownerFlags != 0) {
        ((struct FlagDst *)ownerFlags)->flags |= 4;
    }
    if (*(void **)((u8 *)work + 0x2C) != 0) {
        sub_08015974();
        *(void **)((u8 *)work + 0x2C) = 0;
    }
    sub_08016678(self);
}
