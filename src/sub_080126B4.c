/* Convert a signed step distance and a cardinal direction (0, 0x4000, 0x8000
 * or 0xC000) into x/y displacement components written through dx and dy. */
void sub_080126B4(s32 distance, s32 direction, s32 *dx, s32 *dy) {
    switch (direction) {
    case 0xC000:
        *dx = distance;
        *dy = 0;
        return;
    case 0x4000:
        *dx = -distance;
        *dy = 0;
        return;
    case 0x0:
        *dx = 0;
        *dy = distance;
        return;
    case 0x8000:
        *dx = 0;
        *dy = -distance;
        return;
    default:
        *dy = 0;
        *dx = 0;
        return;
    }
}
