extern void stepAnimationTrack(void *a, void *b);
extern s32 sub_080C31E0(void *a, void *b);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Tick the animation; when it ends, dispatch the next script step. Otherwise
 * recompute the sprite's screen coordinates from the camera table. */
void sub_08059D54(void *entity)
{
    void *sprite;
    void *work;
    void *anim;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    anim = (u8 *)work + 0x34;

    stepAnimationTrack(sprite, anim);
    if (*(u8 *)anim & 2) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }

    {
        u8 *coordTable;
        u8 *cameraIndex;
        u8 *xBase;
        u8 *yBase;
        u32 coordOffset;

        coordTable = gCameraState;
        cameraIndex = gMainWorkspace;
        cameraIndex += 0x18A8;

        coordOffset = ((u32)*cameraIndex + 1) * 0x40;
        xBase = coordTable + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(xBase + coordOffset) + 0x8000) & 0xFFFF0000);

        coordOffset = ((u32)*cameraIndex + 1) * 0x40;
        yBase = coordTable + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(yBase + coordOffset) + 0xFFFF8000) & 0xFFFF0000);
    }
}
