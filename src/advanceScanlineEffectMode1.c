extern struct ScanlineEffectStepState gCameraState;
extern struct CrossfadeColorTable gCrossfadeGfxState;
extern vu8 gVcountCompare;

/* Advance the active scanline crossfade step (mode 1): snapshot the step
 * parameters, count down the hold timer and bump the scroll when it expires,
 * copy the four fade colours, and program the VCOUNT compare byte (0xE3 while
 * idle). */
void advanceScanlineEffectMode1(void) {
    u8 duration, hold;

    gCameraState.mode = 1;
    duration = gCameraState.stepDuration;
    gCameraState.savedDuration = duration;
    gCameraState.savedParam0 = gCameraState.param0;
    gCameraState.savedParam1 = gCameraState.param1;
    gCameraState.savedParam2 = gCameraState.param2;
    gCameraState.savedParam3 = gCameraState.param3;
    gCameraState.savedScrollStep = gCameraState.scrollStep;
    gCameraState.savedParam5 = gCameraState.param5;
    gCameraState.savedParam6 = gCameraState.param6;
    hold = gCameraState.holdTimer;
    if (hold != 0) {
        gCameraState.holdTimer = hold - 1;
    } else {
        gCameraState.holdTimer = duration;
        gCameraState.scrollAccum = gCameraState.scrollAccum + gCameraState.scrollStep;
    }
    gCameraState.fadeColor0 = gCrossfadeGfxState.color0;
    gCameraState.fadeColor1 = gCrossfadeGfxState.color1;
    gCameraState.fadeColor2 = gCrossfadeGfxState.color2;
    gCameraState.fadeColor3 = gCrossfadeGfxState.color3;
    gCameraState.scrollPrevious = gCameraState.scrollAccum;
    gCameraState.activeLines = gCameraState.savedParam0;
    if (gCameraState.activeLines == 0) {
        gVcountCompare = 0xE3;
    } else {
        gVcountCompare = gCameraState.activeLines - 1;
    }
}
