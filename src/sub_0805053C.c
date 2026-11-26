extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080507E0(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E5CC[];

struct SubFlag { u8 a; u8 flag; };
struct MainFlag { u8 flag; };
struct StateFlag { u16 flag; };

/* Update a camera-driven effect: refresh its visibility and animation state,
   advance the script when the animation helper allows it, and copy the state
   coordinates into the main object. */
void sub_0805053C(u8 *arg0) {
    u8 *mainObj;
    u8 *state;
    u8 *p34;
    struct SubFlag *sub;
    u8 *scriptPtr;
    u8 *coordTable;
    u8 *camTable;
    u8 *coordXPtr;
    u32 index;
    u32 coordX;
    u32 coordY;
    u32 cmd;
    u8 *scriptBase;
    s32 scriptOffset;

    mainObj = *(u8 **)(arg0 + 0x38);
    state = *(u8 **)(arg0 + 0x3C);
    p34 = state + 0x34;
    sub = *(struct SubFlag **)(state + 0x28);
    sub->flag |= 1;
    {
        u8 zero = 0;
        if (sub_0805F9B4(*(s32 *)(state + 8), *(s32 *)(state + 0xC)) == 1) {
            ((struct MainFlag *)(mainObj + 0x2A))->flag &= 0xBF;
            ((struct SubFlag *)(*(u8 **)(state + 0x28)))->flag = zero;
        } else {
            ((struct MainFlag *)(mainObj + 0x2A))->flag |= 0x40;
            ((struct SubFlag *)(*(u8 **)(state + 0x28)))->flag = 1;
        }
    }

    if (*(u16 *)(*(u8 **)(state + 0x28) + 0x14) & 1) {
        ((struct StateFlag *)state)->flag |= 1;
    }

    if (sub_08013B5C(mainObj, state) != 0) goto common;

    *(u32 *)(arg0 + 0x14) = (u32)D_0866E5CC;
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
    scriptPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
    *(u8 *)(scriptPtr + 0x19) = *(u8 *)(scriptPtr + 0x19) + 1;
    scriptOffset = *(s16 *)(arg0 + 0x22) * 2;
    scriptBase = arg0;
    scriptBase += 0x18;
    cmd = *(u8 *)((u32)scriptBase + (u32)scriptOffset);
    sub_080C31E0((s32)arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + cmd * 4));
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    if ((*(u16 *)(arg0 + 2) & 0x8000) != 0) return;
    sub_080113A8(mainObj, p34);

common:
    sub_080507E0(mainObj, state);

    coordTable = gCameraState;
    camTable = gMainWorkspace;
    camTable += 0x18A8;
    index = ((u32)*camTable + 1) * 0x40;
    coordXPtr = coordTable + 0x1278;
    coordX = *(u32 *)(coordXPtr + index);
    *(u32 *)(mainObj + 0x14) = *(u32 *)(state + 8) - ((coordX + 0x8000) & 0xFFFF0000);
    index = ((u32)*camTable + 1) * 0x40;
    coordTable += 0x127C;
    coordY = *(u32 *)(coordTable + index);
    *(u32 *)(mainObj + 0x18) = *(u32 *)(state + 0xC) - ((coordY + 0xFFFF8000) & 0xFFFF0000);
}
