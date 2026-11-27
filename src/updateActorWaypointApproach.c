extern void setAnimationFrame(s32, void *, s32, s32);
extern void setSpriteFlip(s32, s32);
extern s32 absXFromFocus(s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern s32 sub_08014A6C(void *, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gTrigFuncTable[];
extern u32 gScriptStepCallbacks[];

/*
 * Advances a script-driven actor's waypoint approach: refreshes its animation,
 * builds the target from the current scroll row, marks the target as reached
 * when the actor is close, rotates its facing angle, and either finishes the
 * approach or, when the tracked X leaves the focus range, resets the script
 * step; otherwise it moves the actor toward the target and applies its flip.
 */
void updateActorWaypointApproach(u8 *actor) {
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *steer = work + 0x48;
    s32 targetX, targetY;
    u8 *scrollBase;
    u32 clearByte;

    setAnimationFrame(sprite, animTrack, 0, 1);
    scrollBase = gCameraState;
    {
        u8 *workspace = gMainWorkspace;
        u8 *frameCounter = workspace + 0x18A8;
        u32 scrollRow = (*(u8 *)frameCounter + 1) << 6;
        u8 *scrollXBase = scrollBase + 0x1278;
        targetX = *(s32 *)(scrollXBase + scrollRow) + WAYPOINT_SCREEN_X_BIAS;
    }
    targetY = *(s32 *)(steer + 0x20);
    if (sub_08014A04(work, targetX, targetY, WAYPOINT_NEAR_DX, WAYPOINT_NEAR_DY) == 1) {
        if (*(s16 *)(steer + 0xA) == 1) *(u16 *)(steer + 0xC) = 1;
    }
    if (*(u8 *)(animTrack + 1) == 1 && *(s32 *)(animTrack + 4) == 1) {
        *(u16 *)(steer + 4) = 0;
    }
    {
        void **trigFuncs = (void **)gTrigFuncTable;
        s32 trigInput = divInt32(*(s16 *)(steer + 4) << 0x10, WAYPOINT_ANGLE_DIVISOR);
        *(u32 *)(steer + 0) = _call_via_r1((void *)trigInput, *trigFuncs) * 2;
    }
    {
        u16 nextAngle = *(u16 *)(steer + 4) + 1;
        clearByte = 0;
        *(u16 *)(steer + 4) = nextAngle;
    }
    if (*(s16 *)(steer + 0xC) == 1) {
        if (sub_08014A6C(work, *(s32 *)(steer + 0x54), WAYPOINT_SHRINK_STEP, 0) == 1) {
            u8 *stepEntry = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
            stepEntry[0x19] = clearByte;
            {
                void **callbacks = (void **)gScriptStepCallbacks;
                _call_via_r3(actor + 0x18, actor + 0x22, WAYPOINT_STEP_ARRIVED, *callbacks);
            }
        }
    } else {
        if (absXFromFocus(*(s32 *)(steer + 0x1C)) > WAYPOINT_FOCUS_CUTOFF) {
            u8 *stepEntry = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
            stepEntry[0x19] = clearByte;
            {
                void **callbacks = (void **)gScriptStepCallbacks;
                _call_via_r3(actor + 0x18, actor + 0x22, WAYPOINT_STEP_RESET, *callbacks);
            }
            return;
        }
        sub_08014B1C(work, steer + 0x50, targetX, targetY);
        setSpriteFlip(sprite, *(s32 *)(steer + 0x54));
    }
}
