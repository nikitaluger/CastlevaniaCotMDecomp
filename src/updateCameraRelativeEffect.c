extern s32 checkActorViewBounds(void *, void *);
extern void uploadPendingSpriteGraphic(s32, s32);
extern void sub_08014314(void *, s32);
extern s32 sub_08014328(s32, void *, void *);
extern void sub_080C31E0(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct MainFlags {
    u16 field0;
    u16 flag;
};

/* Update an effect: copy the owner's coordinates into the state, refresh the
   facing and animation flags, advance the script unless the visibility check
   stops it, and copy the state position back into the main object. */
void updateCameraRelativeEffect(u8 *arg0)
{
    u8 *mainObj;
    u8 *state;
    u8 *p48;
    u8 *scriptPtr;
    u8 *coordTable;
    u8 *camTable;
    u8 *coordXPtr;
    u32 index;
    u32 coordX;
    u32 coordY;
    u8 cmd;
    u8 *scriptBase;
    s32 scriptOffset;

    mainObj = *(u8 **)(arg0 + 0x38);
    state = *(u8 **)(arg0 + 0x3C);
    p48 = state + 0x48;
    *(u32 *)(state + 8) = *(u32 *)(arg0 + 0x4C);
    *(u32 *)(state + 0xC) = *(u32 *)(arg0 + 0x5C);

    if (*(u8 *)(arg0 + 0x6C) != 0)
        ((struct MainFlags *)mainObj)->flag |= 0x10;
    else
        ((struct MainFlags *)mainObj)->flag &= 0xFFEF;
    *(u16 *)mainObj = (*(u16 *)mainObj & 0xFFF) | ((*(u16 *)(state + 0x22) + 8) << 12);

    if (checkActorViewBounds(mainObj, state) == 1) {
        sub_080C31E0((void *)arg0, *(s32 *)(arg0 + 0x24));
        return;
    }
    uploadPendingSpriteGraphic(*(s32 *)(arg0 + 0x28), *(s32 *)p48);
    uploadPendingSpriteGraphic(*(s32 *)(arg0 + 0x28), *(s32 *)(p48 + 4));
    if (sub_08014328(*(s32 *)(arg0 + 0x28), mainObj, state) == 0) {
        *(u32 *)(arg0 + 0x14) = 0x0866DDD0;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        scriptPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(scriptPtr + 0x19) = *(u8 *)(scriptPtr + 0x19) + 1;
        scriptOffset = *(s16 *)(arg0 + 0x22) * 2;
        scriptBase = arg0;
        scriptBase += 0x18;
        cmd = *(u8 *)((u32)scriptBase + (u32)scriptOffset);
        sub_080C31E0((void *)arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + cmd * 4));
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    } else {
        sub_08014314(state, *(s32 *)p48);
        sub_08014314(state, *(s32 *)(p48 + 4));
    }

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
