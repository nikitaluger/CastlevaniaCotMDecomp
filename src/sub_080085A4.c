extern u16 D_080CA8D0[];

/* Script command: sets the substate at +0x0C to 2, copies the u16 argument at
 * D_080CA8D0[cursor] into +0x10, and advances the cursor (+0x04) past it. */
void sub_080085A4(void *arg0) {
    s32 *p = (s32 *)arg0;
    s32 cursor = p[1] + 1;
    p[1] = cursor;
    p[3] = 2;
    p[4] = (s32)D_080CA8D0[cursor];
    p[1] = cursor + 1;
}
