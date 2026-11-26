extern s32 sub_0805F9B4(s32 x, s32 y); /* 1 when the point is outside the view */
extern void sub_080113A8(void *sprite, void *animState);
extern void sub_0801165C(void *work, s32 accelY);
extern void sub_080C31E0(void *actor, void *handler);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* If the actor leaves the view or its animation finishes, switch its state;
 * otherwise integrate its motion and recompute screen coordinates from the camera. */
void sub_08026BDC(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    u8 *animState = (u8 *)work + 0x34;
    if (sub_0805F9B4(*(s32 *)((u8 *)work + 0x08), *(s32 *)((u8 *)work + 0x0C)) == 1)
        goto SWITCH_STATE;
    sub_080113A8(sprite, animState);
    sub_0801165C(work, 0);
    if (*(u8 *)animState & 2)
        goto SWITCH_STATE;
    goto SET_COORDS;

SWITCH_STATE:
    sub_080C31E0(arg0, *(void **)(self + 0x24));
    return;

SET_COORDS:
    {
        u8 *coordTable = gCameraState;
        u8 *cameraIndex = gMainWorkspace;
        u8 *xBase;
        u8 *yBase;
        u32 coordOffset;

        cameraIndex += 0x18A8;

        coordOffset = ((u32)*cameraIndex + 1) * 0x40;
        xBase = coordTable + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(xBase + coordOffset) + 0x8000) & 0xFFFF0000);

        coordOffset = ((u32)*cameraIndex + 1) * 0x40;
        yBase = coordTable + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(yBase + coordOffset) + 0xFFFF8000) & 0xFFFF0000);
    }
}
