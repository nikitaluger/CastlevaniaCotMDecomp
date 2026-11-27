/* Sync a scripted effect's position: update its in-view flag from the camera
 * bounds, drive its display state, then store its fixed-point position and
 * convert it to camera-relative screen coordinates. */
extern void stepAnimationTrack(void *, void *);
extern s32 updateObjectDisplayState(void *, void *);
extern s32 isOutsideCameraBounds(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct S2A { u8 flag; };

void updateScriptedEffectPosition(u8 *effect) {
    void *sprite;
    void *fxState;
    u8 *motion;
    s32 outsideView;

    sprite = *(void **)(effect + 0x38);
    fxState = *(void **)(effect + 0x3C);
    motion = (u8 *)fxState + 0x34;

    outsideView = isOutsideCameraBounds(*(s32 *)((u8 *)fxState + 8), *(s32 *)((u8 *)fxState + 0xC));
    if (outsideView == 1) {
        ((struct S2A *)((u8 *)sprite + 0x2A))->flag &= 0xBF;
    } else {
        ((struct S2A *)((u8 *)sprite + 0x2A))->flag |= 0x40;
    }
    if (updateObjectDisplayState(sprite, fxState) == 0) {
        stepAnimationTrack(sprite, motion);
    }

    *(s32 *)((u8 *)fxState + 8) = *(s16 *)(effect + 0x4C) << 16;
    *(s32 *)((u8 *)fxState + 0xC) = *(s16 *)(effect + 0x54) << 16;

    {
        u8 *gameState = gCameraState;
        u8 *camInfo = gMainWorkspace;
        u8 *camXBase;
        u8 *camYBase;
        u32 camIndex;

        camInfo += 0x18A8;

        camIndex = ((u32)*camInfo + 1) * 0x40;
        camXBase = gameState + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(s32 *)((u8 *)fxState + 8) - ((*(u32 *)(camXBase + camIndex) + 0x8000) & 0xFFFF0000);

        camIndex = ((u32)*camInfo + 1) * 0x40;
        camYBase = gameState + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(s32 *)((u8 *)fxState + 0xC) - ((*(u32 *)(camYBase + camIndex) + 0xFFFF8000) & 0xFFFF0000);
    }
}
