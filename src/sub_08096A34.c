extern void sub_080113A8(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866FB24[];

struct S2A { u8 flag; };

/* Run one step of a scripted entity's program: flag whether the player is near,
 * dispatch the step's handler from the entity's jump table, then apply the
 * camera-relative position correction. */
void sub_08096A34(u8 *entity) {
    u8 *state;
    u8 *comp;
    u8 *compTarget;
    s32 nearby;
    u8 *stepCounterPtr;
    u8 *coordTable;
    u8 *xBase;
    u8 *camBase;
    u32 coordIdx;
    u32 xOffset;
    u32 yOffset;
    u32 opcode;
    u8 *script;
    s32 stepOff;

    state = *(u8 **)(entity + 0x38);
    comp = *(u8 **)(entity + 0x3C);
    compTarget = comp + 0x18;
    nearby = sub_0805F9B4(*(s32 *)(comp + 0xC), *(s32 *)(comp + 0x10));
    if (nearby == 1) {
        ((struct S2A *)(state + 0x2A))->flag &= 0xBF;
    } else {
        ((struct S2A *)(state + 0x2A))->flag |= 0x40;
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866FB24;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepCounterPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepCounterPtr + 0x19) = *(u8 *)(stepCounterPtr + 0x19) + 1;
    stepOff = *(s16 *)(entity + 0x22) * 2;
    script = entity;
    script += 0x18;
    opcode = *(u8 *)((u32)script + (u32)stepOff);
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + opcode * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;

    if ((*(u16 *)(entity + 2) & 0x8000) == 0) {
        if (*(s16 *)(comp + 0x16) == 1) {
            sub_080113A8(state, compTarget);
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
