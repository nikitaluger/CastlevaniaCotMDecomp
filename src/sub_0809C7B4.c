extern u8 gCameraState[];
extern u8 gMainWorkspace[];

static inline u16 get_8000(void)
{
    return 0x8000;
}

struct Rec {
    s32 f0;
    s32 f4;
    u8 _pad[0x38];
};

struct Base {
    u8 _pad[0x1278];
    struct Rec rec[2];
    u8 _pad2[0x1C];
    u16 x, y, z;
};

/* Convert a world position to camera-relative coordinates: look up the active camera
 * origin in the coordinate table using the global camera index, round it to whole
 * pixels, subtract it from (worldX, worldY), and store the result plus angle+0x8000
 * into the global state at 0x1314/0x1316/0x1318. */
void sub_0809C7B4(s32 worldX, s32 worldY, u16 angle)
{
    struct Base *coordState = (struct Base *)gCameraState;
    u8 *indexPtr = gMainWorkspace;
    u8 cameraIndex;
    s32 originX, originY;
    u16 half;
    s32 off;
    u16 angleValue;

    indexPtr += 0x18A8;

    cameraIndex = *indexPtr;
    originX = coordState->rec[cameraIndex + 1].f0;
    half = get_8000();
    coordState->x = (u32)(worldX - ((originX + half) & 0xFFFF0000)) >> 16;

    cameraIndex = *indexPtr;
    originY = coordState->rec[cameraIndex + 1].f4;
    coordState->y = (u32)(worldY - ((originY + (s32)0xFFFF8000) & 0xFFFF0000)) >> 16;

    angleValue = angle + half;
    off = 0x1318;
    *(u16 *)((u8 *)coordState + off) = angleValue;
}
