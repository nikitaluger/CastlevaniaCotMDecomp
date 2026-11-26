extern void sub_080983E8(void *);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_08670378[];

/* Advance an entity's script step, dispatch the selected handler, then refresh
 * its sprite attributes and world position relative to the active layer. */
void sub_080B3634(u8 *entity) {
    u8 *sprite;
    u8 *actor;
    u8 *stepPtr;
    u32 layerOffset;
    u32 centerX;
    u32 centerY;
    u8 *layerTable;
    u8 *activeLayer;
    u8 *xTable;
    u8 *yTable;
    u32 activeLayerOffset;

    sprite = *(u8 **)(entity + 0x38);
    actor = *(u8 **)(entity + 0x3C);

    *(u16 *)(sprite + 0x00) = (*(u16 *)(sprite + 0x00) & 0x0FFF) | (((*(u16 *)(actor + 0x22)) + 8) << 12);
    *(u32 *)(entity + 0x14) = (u32)D_08670378;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepPtr = (u8 *)((s32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;

    {
        s32 ctrlOffset = *(s16 *)(entity + 0x22) * 2;
        u8 *ctrlBase = entity + 0x18;
        u8 stepByte = *(u8 *)((u32)ctrlBase + (u32)ctrlOffset);
        sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + stepByte * 4));
    }

    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    sub_080983E8(sprite);

    layerTable = gCameraState;
    activeLayerOffset = 0x18A8;
    activeLayer = gMainWorkspace + activeLayerOffset;
    layerOffset = ((u32)*activeLayer + 1) * 0x40;
    xTable = layerTable + 0x1278;
    centerX = *(u32 *)(xTable + layerOffset);
    *(u32 *)(sprite + 0x14) = *(u32 *)(actor + 0x08) - ((centerX + 0x8000) & 0xFFFF0000);

    layerOffset = ((u32)*activeLayer + 1) * 0x40;
    yTable = layerTable + 0x127C;
    centerY = *(u32 *)(yTable + layerOffset);
    *(u32 *)(sprite + 0x18) = *(u32 *)(actor + 0x0C) - ((centerY + 0xFFFF8000) & 0xFFFF0000);
}
