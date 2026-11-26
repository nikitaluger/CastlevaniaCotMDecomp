extern void sub_080113A8(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern void sub_0801C4E0(void *);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct MainObjFlagByte { u8 flag; };

/* Update a camera-driven effect: refresh its visibility from the camera bounds,
   advance its command script when the animation helper allows it, then copy the
   state's world coordinates into the main object. */
void sub_0801C28C(u8 *obj) {
    u8 *mainObj;
    u8 *state;
    u8 *stateP34;
    s32 offCamera;
    u8 *scriptStep;
    u8 *coordTable;
    u8 *coordXPtr;
    u8 *camTable;
    u32 index;
    u32 camX;
    u32 camY;
    u32 cmd;
    u8 *scriptBase;
    s32 scriptOffset;

    mainObj = *(u8 **)(obj + 0x38);
    state = *(u8 **)(obj + 0x3C);
    stateP34 = state + 0x34;
    offCamera = sub_0805F9B4(*(s32 *)(state + 0x08), *(s32 *)(state + 0x0C));
    if (offCamera == 1) {
        ((struct MainObjFlagByte *)(mainObj + 0x2A))->flag &= 0xBF;
    } else {
        ((struct MainObjFlagByte *)(mainObj + 0x2A))->flag |= 0x40;
    }
    if (sub_08013B5C(mainObj, state) == 0) {
        *(u32 *)(obj + 0x14) = 0x0866D6CC;
        *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
        scriptStep = (u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj);
        *(u8 *)(scriptStep + 0x19) = *(u8 *)(scriptStep + 0x19) + 1;
        scriptOffset = *(s16 *)(obj + 0x22) * 2;
        scriptBase = obj;
        scriptBase += 0x18;
        cmd = *(u8 *)((u32)scriptBase + (u32)scriptOffset);
        sub_080C31E0((s32)obj, *(u32 *)(*(u32 *)(obj + 0x14) + cmd * 4));
        *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
        sub_0801C4E0(obj);
        if ((*(u16 *)(obj + 2) & 0x8000) != 0)
            return;
        sub_080113A8(mainObj, stateP34);
    }
    coordTable = gCameraState;
    camTable = gMainWorkspace;
    camTable += 0x18A8;
    index = ((u32)*camTable + 1) * 0x40;
    coordXPtr = coordTable + 0x1278;
    camX = *(u32 *)(coordXPtr + index);
    *(u32 *)(mainObj + 0x14) = *(u32 *)(state + 0x08) - ((camX + 0x8000) & 0xFFFF0000);
    index = ((u32)*camTable + 1) * 0x40;
    coordTable += 0x127C;
    camY = *(u32 *)(coordTable + index);
    *(u32 *)(mainObj + 0x18) = *(u32 *)(state + 0x0C) - ((camY + 0xFFFF8000) & 0xFFFF0000);
}
