extern void sub_08098338(s32, void *);
extern void sub_0809C318(s32, void *, void *, void *, s32);
extern void sub_0809C3F4(void *, void *, void *, void *);
extern void sub_0809C490(s32, void *, void *, void *);
extern void sub_080C31E0(void *, s32);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/*
 * Entity AI state update: rebuilds the sprite's pose flags, dispatches the
 * handler for the current script step, runs the attack/position helpers and
 * writes the entity's map-relative world position.
 */
void sub_08098E40(u8 *entity) {
    u8 *sprite;
    u8 *motion;
    u8 *status;
    u8 *motionEx;
    u8 *stepData;
    u32 idx;
    u32 scrollX;
    u32 scrollY;
    u8 *mapTable;
    u8 *mapIndex;
    u8 *baseX;
    u8 *baseY;
    u32 mapOff;

    sprite = *(u8 **)(entity + 0x38);
    motion = *(u8 **)(entity + 0x3C);
    status = motion + 0x34;
    motionEx = motion + 0x48;

    *(u16 *)sprite = (*(u16 *)sprite & 0x0FFF) | ((*(u16 *)(motion + 0x22) + 8) << 12);
    *(u32 *)(entity + 0x14) = 0x0866FBA0;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepData = (u8 *)((s32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;

    {
        s32 stepIndex = *(s16 *)(entity + 0x22) * 2;
        u8 *stepTable = entity + 0x18;
        u8 stepByte = *(u8 *)((u32)stepTable + (u32)stepIndex);
        sub_080C31E0(entity, *(s32 *)(*(u8 **)(entity + 0x14) + stepByte * 4));
    }

    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;

    sub_0809C318(*(s32 *)(motionEx + 8), sprite, motion, status, *(u16 *)(motionEx + 0x24));
    sub_0809C3F4(motion + 0x54, sprite, motion, status);
    sub_0809C490(*(s32 *)(motionEx + 0x14), sprite, motion, status);
    sub_08098338(3, sprite);

    mapTable = gCameraState;
    mapOff = 0x18A8;
    mapIndex = gMainWorkspace + mapOff;
    idx = ((u32)*mapIndex + 1) * 0x40;
    baseX = mapTable + 0x1278;
    scrollX = *(u32 *)(baseX + idx);
    *(u32 *)(sprite + 0x14) = *(u32 *)(motion + 8) - ((scrollX + 0x8000) & 0xFFFF0000);

    idx = ((u32)*mapIndex + 1) * 0x40;
    baseY = mapTable + 0x127C;
    scrollY = *(u32 *)(baseY + idx);
    *(u32 *)(sprite + 0x18) = *(u32 *)(motion + 0x0C) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
