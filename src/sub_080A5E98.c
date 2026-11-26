extern void sub_080983E8(void *);
extern void sub_080A820C(void *, void *, void *, void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Initializes a weapon entity's state: updates the owner's animation flags,
 * dispatches its slot callback, runs the sub-object setup, then copies the
 * camera-corrected world position back through the coordinate table. */
void sub_080A5E98(u8 *entity) {
    u8 *parent;
    u8 *obj;
    u8 *slot;
    u8 *objSub;
    u8 *objState;
    u32 tableIdx;
    u32 camOffX;
    u32 camOffY;
    u8 *coordTable;
    u8 *areaState;
    u8 *baseX;
    u8 *baseY;
    u32 stateOffset;

    parent = *(u8 **)(entity + 0x38);
    obj = *(u8 **)(entity + 0x3C);
    objSub = obj + 0x34;
    objState = obj + 0x48;

    *(u16 *)(parent + 0x00) = (*(u16 *)(parent + 0x00) & 0x0FFF) | (((*(u16 *)(obj + 0x22)) + 8) << 12);
    *(u32 *)(entity + 0x14) = 0x0866FF8C;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    slot = (u8 *)((s32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;

    {
        s32 slotOff = *(s16 *)(entity + 0x22) * 2;
        u8 *slots = entity + 0x18;
        u8 slotByte = *(u8 *)((u32)slots + (u32)slotOff);
        sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + slotByte * 4));
    }

    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    sub_080A820C(entity, parent, objSub, obj, objState);
    sub_080983E8(parent);

    coordTable = gCameraState;
    stateOffset = 0x18A8;
    areaState = gMainWorkspace + stateOffset;
    tableIdx = ((u32)*areaState + 1) * 0x40;
    baseX = coordTable + 0x1278;
    camOffX = *(u32 *)(baseX + tableIdx);
    *(u32 *)(parent + 0x14) = *(u32 *)(obj + 0x08) - ((camOffX + 0x8000) & 0xFFFF0000);

    tableIdx = ((u32)*areaState + 1) * 0x40;
    baseY = coordTable + 0x127C;
    camOffY = *(u32 *)(baseY + tableIdx);
    *(u32 *)(parent + 0x18) = *(u32 *)(obj + 0x0C) - ((camOffY + 0xFFFF8000) & 0xFFFF0000);
}
