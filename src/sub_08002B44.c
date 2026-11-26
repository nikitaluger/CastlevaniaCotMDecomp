extern u16 gCameraState[];
extern u16 D_0866CA04[];
extern void sub_08000A40(void);
extern void sub_08000BF0(void);
extern void sub_080012C4(s32);
extern void sub_08003AA0(void);

/* Stage setup: record the stage's value from the stage table (8-byte entries) in
 * the work area, clear its word at +0x550, then wipe the sprite and object
 * arrays and rebuild the stage's object storage. */
void sub_08002B44(s16 stage) {
    vu16 *vp = (vu16 *)gCameraState;
    u16 stageValue = D_0866CA04[stage * 4];
    u16 zero = vp[8];
    zero = 0;
    gCameraState[8] = stageValue;
    *(u32 *)((u8 *)gCameraState + 0x550) = zero;
    sub_08000A40();
    sub_080012C4(0x80);
    sub_08003AA0();
    sub_08000BF0();
}
