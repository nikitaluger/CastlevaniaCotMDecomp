extern void sub_08003A6C(void *, s32, void *);
extern void sub_080C31E8(void *, void *, s32, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u8 D_080E03A0[];
extern u8 D_084A67F4[];
extern void *D_08671BD0;

/* If the scenario flag is set, copy one record of the D_080E03A0 table into
 * the destination object, start an action on the actor, then clear this script
 * slot's parameter and advance the script. */
s32 sub_0806865C(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 *self = (u8 *)arg0;
    u8 *actor = (u8 *)arg2;
    u8 *outObj = (u8 *)arg3;
    u32 flagTable = (u32)gGameStatus;
    u32 workBase = (u32)gMainWorkspace;
    u32 flagOffset;
    u32 altOffset;
    u32 tableBase, entryOffset, entryPtr;
    s32 entryIndex;
    s16 scriptIdx;
    u8 *slotPtr;
    void **advanceFn;

    flagOffset = 0x3BE;
    if (*(s32 *)(workBase + 0x24) != 0 ?
        (*(u16 *)(workBase + 0x28) & *(u16 *)(flagTable + flagOffset)) :
        (altOffset = 0x146C, *(u16 *)((u32)gCameraState + altOffset) & *(u16 *)(flagTable + flagOffset))) {
        *(s32 *)(actor + 0x40) = 0;
        tableBase = (u32)D_080E03A0;
        entryIndex = *(s32 *)(actor + 0x44);
        entryOffset = 0x58 * entryIndex;
        tableBase += 0x1C;
        entryPtr = entryOffset + tableBase;
        *(s32 *)(outObj + 0x0C) = *(s32 *)entryPtr;
        *(s32 *)(actor + 0x4C) = 1;
        *(s32 *)(actor + 0x50) = 0;
        sub_08003A6C(actor + 0x28, 0, (void *)D_084A67F4);
        scriptIdx = *(s16 *)(self + 0x22);
        slotPtr = (u8 *)(scriptIdx * 2 + (s32)self);
        slotPtr[0x19] = 0;
        advanceFn = &D_08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 0x23, *advanceFn);
        return 1;
    }
    return 0;
}
