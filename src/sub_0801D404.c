extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(void *, void *);
extern void sub_0801D678(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866D718[];

/* Small flag pair at parent+0x28; bit 0 is flagged on entry. */
struct FlagPair { u8 unused; u8 flag; };

/* Runs one frame of an entity's effect state machine (dispatching through the
 * D_0866D718 handler table) and then snaps the child entity's x/y to the
 * parent's position using the gCameraState / gMainWorkspace coordinate tables. */
void sub_0801D404(u8 *self) {
    u8 *child;
    u8 *parent;
    u8 *parentData;
    struct FlagPair *parentFlag;
    u8 *frameData;
    u8 *posTable;
    u8 *coordXTable;
    u8 *coordIndexPtr;
    u32 coordIndex;
    u32 coordX;
    u32 coordY;
    u32 effectIndex;
    u8 *frameTable;
    s32 frameOffset;

    child = *(u8 **)(self + 0x38);
    parent = *(u8 **)(self + 0x3C);
    parentData = parent + 0x34;
    parentFlag = *(struct FlagPair **)(parent + 0x28);
    parentFlag->flag |= 1;

    if (sub_08013B5C(child, parent) != 0) goto common;

    *(u32 *)(self + 0x14) = (u32)D_0866D718;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    frameData = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(frameData + 0x19) = *(u8 *)(frameData + 0x19) + 1;
    frameOffset = *(s16 *)(self + 0x22) * 2;
    frameTable = self;
    frameTable += 0x18;
    effectIndex = *(u8 *)((u32)frameTable + (u32)frameOffset);
    sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + effectIndex * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & 0x8000) != 0) return;
    sub_080113A8(child, parentData);
    sub_0801165C(parent, 0);

common:
    sub_0801D678(self, child);

    posTable = gCameraState;
    coordIndexPtr = gMainWorkspace;
    coordIndexPtr += 0x18A8;
    coordIndex = ((u32)*coordIndexPtr + 1) * 0x40;
    coordXTable = posTable + 0x1278;
    coordX = *(u32 *)(coordXTable + coordIndex);
    *(u32 *)(child + 0x14) = *(u32 *)(parent + 8) - ((coordX + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*coordIndexPtr + 1) * 0x40;
    posTable += 0x127C;
    coordY = *(u32 *)(posTable + coordIndex);
    *(u32 *)(child + 0x18) = *(u32 *)(parent + 0xC) - ((coordY + 0xFFFF8000) & 0xFFFF0000);
}
