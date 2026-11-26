extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Copy the entity's world position (from its work struct) into the sprite's
 * screen coordinates, offset by the camera's coordinate table entry. */
void sub_08013C8C(void *entity, void *sprite)
{
    void *work = *(void **)((u8 *)entity + 0x3C);
    u8 *coordTable;
    u8 *cameraIndex;
    u8 *xBase;
    u8 *yBase;
    u32 coordOffset;

    coordTable = gCameraState;
    cameraIndex = gMainWorkspace;
    cameraIndex += 0x18A8;

    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    xBase = coordTable + 0x1278;
    *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(xBase + coordOffset) + 0x8000) & 0xFFFF0000);

    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    yBase = coordTable + 0x127C;
    *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(yBase + coordOffset) + 0xFFFF8000) & 0xFFFF0000);
}
