struct S {
    u8 _0[0x1361];
    u8 f1361;
    u8 _1[2];
    u8 f1364; u8 f1365; u8 f1366; u8 f1367; u8 f1368; u8 f1369;
    u8 f136A; u8 f136B; u8 f136C; u8 f136D; u8 f136E; u8 f136F;
    u8 f1370; u8 f1371; u8 f1372; u8 f1373;
    u8 f1374; u8 f1375; u8 f1376; u8 f1377; u8 f1378; u8 f1379;
    u8 f137A; u8 f137B;
};
struct HW { u8 _0[0x20]; u16 f20; u8 _1[2]; u16 f24; u8 _2[2]; u16 f28; u8 _3[2]; u16 f2C; };
extern struct S gCameraState;
extern struct HW gCrossfadeGfxState;
extern vu8 D_04000005;

/* Advance the scanline effect state: refresh the active step block, count down
 * its hold time, step the background scroll, copy the effect colors, and
 * program the VCOUNT compare register (0xE3 when idle). */
void sub_080BEC40(void) {
    u8 duration, hold;

    gCameraState.f1361 = 2;
    duration = gCameraState.f1364;
    gCameraState.f1374 = duration;
    gCameraState.f1375 = gCameraState.f1366;
    gCameraState.f1376 = gCameraState.f1367;
    gCameraState.f1377 = gCameraState.f1368;
    gCameraState.f1378 = gCameraState.f1369;
    gCameraState.f1379 = gCameraState.f136A;
    gCameraState.f137A = gCameraState.f136B;
    gCameraState.f137B = gCameraState.f136C;
    hold = gCameraState.f1365;
    if (hold != 0) {
        gCameraState.f1365 = hold - 1;
    } else {
        gCameraState.f1365 = duration;
        gCameraState.f136E = gCameraState.f136E + gCameraState.f136A;
    }
    gCameraState.f1370 = gCrossfadeGfxState.f20;
    gCameraState.f1371 = gCrossfadeGfxState.f24;
    gCameraState.f1372 = gCrossfadeGfxState.f28;
    gCameraState.f1373 = gCrossfadeGfxState.f2C;
    gCameraState.f136F = gCameraState.f136E;
    gCameraState.f136D = gCameraState.f1375;
    if (gCameraState.f136D == 0) {
        D_04000005 = 0xE3;
    } else {
        D_04000005 = gCameraState.f136D - 1;
    }
}
