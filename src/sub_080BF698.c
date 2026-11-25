extern u8 D_02021E90[];

/* Display-mode update: flag the pending display change (D_02021E90[0x1361]=8),
 * take the current DISPCNT, wait for the display to reach VBlank if it is
 * still active, then apply DISPCNT with its mode bits cleared and write the
 * saved byte at D_02021E90[0x1367] to 0x04000005. */
void sub_080BF698(void) {
    s32 dispcnt;
    D_02021E90[0x1361] = 8;
    dispcnt = -8 & *(vu16 *)0x04000000;
    if (!(*(vu8 *)0x04000004 & 1) && !(*(vu8 *)0x04000004 & 2)) {
        while (1) {
            if (*(vu8 *)0x04000004 & 2)
                break;
        }
    }
    *(vu16 *)0x04000000 = dispcnt;
    *(vu8 *)0x04000005 = D_02021E90[0x1367];
}
