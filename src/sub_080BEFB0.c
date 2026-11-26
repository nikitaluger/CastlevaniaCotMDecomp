struct S_02021E90_befb0 {
    u8 _0x000[0x1361];
    u8 transition;  /* 0x1361: screen-transition state */
    u8 _pad1[2];
    u8 displayMode; /* 0x1364: value written to DISPCNT's high byte */
    u8 displayModeSaved;
    u8 _pad2[0x1368 - 0x1366];
    u32 fadeStep;   /* 0x1368 */
    u32 fadeTimer;  /* 0x136C */
};
extern struct S_02021E90_befb0 gCameraState;

/* Program the screen transition: set state 9, save the current display mode,
 * initialize the fade step and timer, and write the new display mode to
 * DISPCNT's high byte. */
void sub_080BEFB0(void) {
    gCameraState.transition = 9;
    gCameraState.displayModeSaved = gCameraState.displayMode;
    gCameraState.fadeStep = 0x10;
    gCameraState.fadeTimer = 0;
    *(vu8 *)0x04000005 = gCameraState.displayMode - 1;
}
