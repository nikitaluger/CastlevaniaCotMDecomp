extern s32 isOutsideCameraBounds(s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_080C31E0(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E770[];

/* Advances one scripted behaviour step for an entity, plays a state-dependent
 * sound, then writes its camera-relative world position. */
void sub_08055B80(u8 *entity) {
    u8 *parent;
    u8 *component;
    u8 *scriptPlayer;
    u8 *stepPtr;
    u8 *tableBase;
    u8 *scrollIndexPtr;
    u8 *xTable;
    u8 *opcodePtr;
    u8 opcode;
    u32 tableOffset;
    u32 pcOffset;
    u32 xScroll;
    u32 yScroll;

    parent = *(u8 **)(entity + 0x38);
    component = *(u8 **)(entity + 0x3C);
    scriptPlayer = component + 0x34;
    if (isOutsideCameraBounds(*(u32 *)(component + 0x08), *(u32 *)(component + 0x0C)) == 1) {
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        return;
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866E770;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;
    pcOffset = *(s16 *)(entity + 0x22) * 2;
    opcodePtr = entity;
    opcodePtr += 0x18;
    opcode = *(u8 *)((u32)opcodePtr + pcOffset);
    sub_080C31E0(entity, *(s32 *)(*(u32 *)(entity + 0x14) + opcode * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & 0x8000) != 0) {
        return;
    }
    stepAnimationTrack(parent, scriptPlayer);
    if (*(s16 *)(entity + 0x7C) == 5) {
        advanceMotion(component, 0x795);
    } else {
        advanceMotion(component, 0x16C1);
    }
    tableBase = gCameraState;
    scrollIndexPtr = gMainWorkspace;
    scrollIndexPtr += 0x18A8;
    tableOffset = ((u32)*scrollIndexPtr + 1) * 0x40;
    xTable = tableBase + 0x1278;
    xScroll = *(u32 *)(xTable + tableOffset);
    *(u32 *)(parent + 0x14) = *(u32 *)(component + 8) - ((xScroll + 0x8000) & 0xFFFF0000);
    tableOffset = ((u32)*scrollIndexPtr + 1) * 0x40;
    tableBase += 0x127C;
    yScroll = *(u32 *)(tableBase + tableOffset);
    *(u32 *)(parent + 0x18) = *(u32 *)(component + 0xC) - ((yScroll + 0xFFFF8000) & 0xFFFF0000);
}
