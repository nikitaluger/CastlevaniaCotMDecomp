extern s32 updateObjectDisplayState(void *sprite, void *state);
extern void stepAnimationTrack(void *sprite, void *animState);
extern s32 sub_080C31E0(void *actor, void *handler);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Apply an actor's display state; if the frame was not fully handled, advance
 * its animation and recompute its screen coordinates from the camera table,
 * or switch its state handler when the animation's flag 2 fires. */
void sub_0802ED5C(void *actor)
{
    void *sprite;
    void *work;
    u8 *animState;

    sprite = *(void **)((u8 *)actor + 0x38);
    work = *(void **)((u8 *)actor + 0x3C);
    animState = (u8 *)work + 0x34;

    if (updateObjectDisplayState(sprite, work) == 0) {
        stepAnimationTrack(sprite, animState);
        if (*animState & 2) {
            sub_080C31E0(actor, *(void **)((u8 *)actor + 0x24));
            return;
        }
    }

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
