extern u8 gCameraState[];

/* Advance the expanding-window effect: bump its frame counter, recompute the
 * four edges of the window around its fixed centre (a short window in mode 4,
 * a tall one otherwise), and clear the active flag once the counter hits 0x10. */
void sub_0806111C(void) {
    gCameraState[0x145E] = gCameraState[0x145E] + 1;
    if (gCameraState[0x145F] == 4) {
        gCameraState[0x1460] = 0x20 - gCameraState[0x145E] * 2;
        gCameraState[0x1464] = 0x28 - gCameraState[0x145E] * 2;
        gCameraState[0x1462] = gCameraState[0x145E] * 2 + 0x20;
        gCameraState[0x1466] = gCameraState[0x145E] * 2 + 0x28;
    } else {
        gCameraState[0x1460] = 0x20 - gCameraState[0x145E] * 2;
        gCameraState[0x1464] = 0x78 - gCameraState[0x145E] * 2;
        gCameraState[0x1462] = gCameraState[0x145E] * 2 + 0x20;
        gCameraState[0x1466] = gCameraState[0x145E] * 2 + 0x78;
    }
    gCameraState[0x1468] = 0x3F;
    if (gCameraState[0x145E] == 0x10) {
        gCameraState[0x145D] = 0;
    }
}
