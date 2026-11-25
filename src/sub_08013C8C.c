extern u8 D_02021E90[];
extern u8 D_02025FF0[];

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

    coordTable = D_02021E90;
    cameraIndex = D_02025FF0;
    cameraIndex += 0x18A8;

    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    xBase = coordTable + 0x1278;
    *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(xBase + coordOffset) + 0x8000) & 0xFFFF0000);

    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    yBase = coordTable + 0x127C;
    *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(yBase + coordOffset) + 0xFFFF8000) & 0xFFFF0000);
}
