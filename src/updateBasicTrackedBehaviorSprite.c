extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern s32 advanceMotion(void *, s32);
extern s32 stepAnimationTrack(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gBasicTrackedBehaviorStepHandlers[];

static inline void or40p(u8 *q)
{
    u8 v = *q;
    u32 m = 0x40;
    m |= v;
    *q = (u8) m;
}

/* Dispatch the current script command, set an entity flag from a comparison,
 * and, unless disabled, sync state fields and apply table-based offsets. */
void updateBasicTrackedBehaviorSprite(u8 *arg0) {
    u8 *entity;
    u8 *state;
    u8 *stateField34;
    u8 *stateField48;
    s32 compareResult;
    u8 *scriptSlot;
    u8 *stateTable;
    u8 *tableIndexPtr;
    u8 *tablePtr;
    u8 *shakeCounter;
    u32 tableIndex;
    u32 tableValue1;
    u32 tableValue2;
    u32 scriptByte;
    u8 *scriptBase;
    s32 scriptOffset;
    u8 *targetObj;
    u16 disableFlag;
    u8 *flagByte;
    u32 highMask;

    entity = *(u8 **)(arg0 + 0x38);
    state = *(u8 **)(arg0 + 0x3C);
    stateField34 = state + 0x34;
    stateField48 = state + 0x48;
    compareResult = isOutsideCameraBounds(*(s32 *)(state + 0x08), *(s32 *)(state + 0x0C));
    if (compareResult == 1) {
        targetObj = *(u8 **)(stateField48 + 0x04);
        *(u8 *)(targetObj + 0x01) = 0;
        flagByte = entity + 0x2A;
        *flagByte = *flagByte & 0xBF;
    } else {
        targetObj = *(u8 **)(stateField48 + 0x04);
        *(u8 *)(targetObj + 0x01) = 1;
        flagByte = entity + 0x2A;
        or40p(flagByte);
    }
    *(u32 *)(arg0 + 0x14) = (u32)gBasicTrackedBehaviorStepHandlers;
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
    scriptSlot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
    *(u8 *)(scriptSlot + 0x19) = *(u8 *)(scriptSlot + 0x19) + 1;
    scriptOffset = *(s16 *)(arg0 + 0x22) * 2;
    scriptBase = arg0;
    scriptBase += 0x18;
    scriptByte = *(u8 *)((u32)scriptBase + (u32)scriptOffset);
    sub_080C31E0((s32)arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + scriptByte * 4));
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;

    disableFlag = (*(u16 *)(arg0 + 2)) & 0x8000;
    if (disableFlag == 0) {
        *(u16 *)(*(u8 * volatile *)(stateField48 + 0x04) + 0x04) = *(u16 *)(state + 0x0A);
        {
            u8 *targetObj2 = *(u8 * volatile *)(stateField48 + 0x04);
            highMask = 0xFFFF0000;
            *(u16 *)(targetObj2 + 0x06) = *(u16 *)(state + 0x0E) + 1;
        }
        *(u32 *)(stateField48 + 0x14) = *(u32 *)(state + 0x08);
        *(u32 *)(stateField48 + 0x18) = *(u32 *)(state + 0x0C);
        *(u16 *)(stateField48 + 0x1C) = 0;
        advanceMotion(state, 0);
        stepAnimationTrack(entity, stateField34);

        stateTable = gCameraState;
        shakeCounter = gMainWorkspace;
        shakeCounter += 0x18A8;
        tableIndex = ((u32)*shakeCounter + 1) * 0x40;
        tableIndexPtr = stateTable + 0x1278;
        tableValue1 = *(u32 *)(tableIndexPtr + tableIndex);
        *(u32 *)(entity + 0x14) = *(u32 *)(stateField48 + 0x14) - ((tableValue1 + 0x8000) & highMask);
        tableIndex = ((u32)*shakeCounter + 1) * 0x40;
        tablePtr = stateTable + 0x127C;
        tableValue2 = *(u32 *)(tablePtr + tableIndex);
        *(u32 *)(entity + 0x18) = *(u32 *)(stateField48 + 0x18) - ((tableValue2 + 0xFFFF8000) & highMask);
    }
}
