void sub_08005E80(s32);

struct S_02025FF0_18A8 { u8 _0[0x18A8]; u8 v; };
extern struct S_02025FF0_18A8 gMainWorkspace;
extern u8 gCameraState[];

/* Detect a change to the actor's sound trigger, play its sound effect and
 * mirror the flag into the state, then rebuild the sprite's position from the
 * room coordinate table. */
void sub_080B052C(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    s8 *soundFlag = (s8 *)(self + 0x4C);
    s8 *prevSoundFlag = (s8 *)(self + 0x50);
    u8 savedFlag = *(u8 *)soundFlag;
    u8 *coordTable;
    u32 coordOffset;
    u8 *xBase;
    u8 *yBase;

    if (*soundFlag != *prevSoundFlag) {
        s32 playFlag;
        *prevSoundFlag = (s8)savedFlag;
        if (*soundFlag == 0) {
            playFlag = 0;
        } else {
            sub_08005E80(0x171);
            playFlag = 1;
            *soundFlag = 0;
        }
        *(u8 *)(*(u8 **)(state + 0x28) + 1) = (u8)playFlag;
    }

    coordTable = gCameraState;
    coordOffset = (gMainWorkspace.v + 1) * 0x40;
    xBase = coordTable + 0x1278;
    *(s32 *)((u8 *)sprite + 0x14) = *(s32 *)((u8 *)state + 0x08) - ((*(s32 *)(xBase + coordOffset) + 0x8000) & 0xFFFF0000);

    coordOffset = (gMainWorkspace.v + 1) * 0x40;
    yBase = coordTable + 0x127C;
    *(s32 *)((u8 *)sprite + 0x18) = *(s32 *)((u8 *)state + 0x0C) - ((*(s32 *)(yBase + coordOffset) + 0xFFFF8000) & 0xFFFF0000);
}
