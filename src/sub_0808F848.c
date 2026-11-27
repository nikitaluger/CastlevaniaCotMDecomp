extern void stepAnimationTrack(void *, void *);
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866F92C[];

struct S2A { u8 flag; };

/* Run one script step: update the entity's proximity flag, dispatch the step's
 * handler, then apply the camera-relative position correction. */
void sub_0808F848(u8 *entity) {
    u8 *state;
    u8 *comp;
    u8 *compTarget;
    u8 *counterPtr;
    s32 close;
    u8 *script;
    u32 coordIdx;
    u8 *coordTable;
    u8 *camBase;
    u8 *xBase;
    u32 xOffset;
    u32 yOffset;
    u32 opcode;
    s32 stepOff;

    state = *(u8 **)(entity + 0x38);
    comp = *(u8 **)(entity + 0x3C);
    compTarget = comp + 0x18;
    close = isOutsideCameraBounds(*(s32 *)(comp + 0xC), *(s32 *)(comp + 0x10));
    if (close == 1) {
        ((struct S2A *)(state + 0x2A))->flag &= 0xBF;
    } else {
        ((struct S2A *)(state + 0x2A))->flag |= 0x40;
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866F92C;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    counterPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(counterPtr + 0x19) = *(u8 *)(counterPtr + 0x19) + 1;
    stepOff = *(s16 *)(entity + 0x22) * 2;
    script = entity;
    script += 0x18;
    opcode = *(u8 *)((u32)script + (u32)stepOff);
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + opcode * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;

    if ((*(u16 *)(entity + 2) & 0x8000) == 0) {
        if (*(s16 *)(comp + 0x16) == 1) {
            stepAnimationTrack(state, compTarget);
        }
        coordTable = gCameraState;
        camBase = gMainWorkspace;
        camBase += 0x18A8;
        coordIdx = ((u32)*camBase + 1) * 0x40;
        xBase = coordTable + 0x1278;
        xOffset = *(u32 *)(xBase + coordIdx);
        *(u32 *)(state + 0x14) = *(u32 *)(comp + 0xC) - ((xOffset + 0x8000) & 0xFFFF0000);
        coordIdx = ((u32)*camBase + 1) * 0x40;
        coordTable += 0x127C;
        yOffset = *(u32 *)(coordTable + coordIdx);
        *(u32 *)(state + 0x18) = *(u32 *)(comp + 0x10) - ((yOffset + 0xFFFF8000) & 0xFFFF0000);
    }
}
