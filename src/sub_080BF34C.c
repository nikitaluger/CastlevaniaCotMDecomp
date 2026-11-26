/* Raster-effect state in the shared work area. */
struct S_02021E90 {
    u8 _0[0x1361];
    u8 active;      /* 0x1361 */
    u8 _1[0x1368 - 0x1362];
    u8 scanline;    /* 0x1368 */
    u8 mode;        /* 0x1369 */
};
extern struct S_02021E90 gCameraState;

/*
 * VBlank raster effect: waits for VBlank, sets BG0's horizontal/vertical
 * scroll for the current mode, then programs the scanline-timing register
 * from the effect's mode and scanline counter.
 */
void sub_080BF34C(void) {
    u8 mode, scanline, modeAgain;
    u32 scanlineWord;

    while (!(*(vu8 *)0x04000004 & 2)) { }
    *(vu16 *)0x04000000 &= 0xFEFF;
    mode = gCameraState.mode;
    switch (mode) {
    case 0:
        *(vu16 *)0x04000010 = mode;
        *(vu16 *)0x04000012 = 0x190;
        break;
    case 0x50:
        *(vu16 *)0x04000010 = 0;
        *(vu16 *)0x04000012 = 0x140;
        break;
    case 0x48:
        *(vu16 *)0x04000010 = 0;
        *(vu16 *)0x04000012 = 0x19C;
        break;
    }
    scanlineWord = gCameraState.scanline;
    scanline = (u8)scanlineWord;
    if (scanline == 0) {
        gCameraState.active = scanline;
        return;
    }
    gCameraState.active = 4;
    modeAgain = gCameraState.mode;
    switch (modeAgain) {
    case 0:
    case 0x50:
        *(vu8 *)0x04000005 = gCameraState.mode + 0x26 - gCameraState.scanline - 1;
        break;
    case 0x48:
        *(vu8 *)0x04000005 = ~(u8)scanlineWord + 0x4E;
        break;
    }
}
