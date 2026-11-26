extern u8 gCameraState[];

/* Display-mode update: flag the pending display change (gCameraState[0x1361]=8),
 * take the current DISPCNT, wait for the display to reach VBlank if it is
 * still active, then apply DISPCNT with its mode bits cleared and write the
 * saved byte at gCameraState[0x1367] to 0x04000005. */
void sub_080BF698(void) {
    s32 dispcnt;
    gCameraState[0x1361] = 8;
    dispcnt = -8 & *(vu16 *)0x04000000;
    if (!(*(vu8 *)0x04000004 & 1) && !(*(vu8 *)0x04000004 & 2)) {
        while (1) {
            if (*(vu8 *)0x04000004 & 2)
                break;
        }
    }
    *(vu16 *)0x04000000 = dispcnt;
    *(vu8 *)0x04000005 = gCameraState[0x1367];
}
