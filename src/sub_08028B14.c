extern s32 sub_0805F9B4(s32 a, s32 b);
extern void sub_080113A8(void *a, void *b);
extern s32 sub_080C31E0(void *a, void *b);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* If the actor leaves the view or its animation finishes, switch its state;
 * otherwise advance the animation and recompute its screen coordinates from
 * the camera table. */
void sub_08028B14(void *arg0)
{
    void *sprite;
    void *work;
    u8 *animState;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    animState = (u8 *)work + 0x34;

    if (sub_0805F9B4(*(s32 *)((u8 *)work + 0x08), *(s32 *)((u8 *)work + 0x0C)) == 1)
        goto CALL;
    sub_080113A8(sprite, animState);
    if (*animState & 2)
        goto CALL;
    goto COORD;

CALL:
    sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
    return;

COORD:
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
