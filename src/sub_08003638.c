/* Reset the first entry of both sprite-cursor buffers: the words at 0x03000C84
 * and 0x030026A4 point at the two cursors in IWRAM. */
void sub_08003638(s32 cursorA, s32 cursorB) {
    **(s32 **)0x03000C84 = cursorA;
    **(s32 **)0x030026A4 = cursorB;
}
