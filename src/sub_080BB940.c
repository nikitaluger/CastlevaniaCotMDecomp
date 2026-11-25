extern void sub_080986C0(void *);

/* Advance the object's frame and, when its frame/direction byte (+0x25) changed,
 * nudge the horizontal speed at ctrl+0x0C by one unit: -0x10000 for frames 0/3,
 * +0x10000 for frames 1/2. */
void sub_080BB940(void *ctrl, void *obj) {
    u8 *framePtr = (u8 *)obj + 0x25;
    u8 oldFrame = *framePtr;
    sub_080986C0(obj);
    if (oldFrame != *framePtr) {
        switch (*framePtr) {
        case 0:
        case 3:
            *(u32 *)((u8 *)ctrl + 0x0C) += 0xFFFF0000;
            break;
        case 1:
        case 2:
            *(u32 *)((u8 *)ctrl + 0x0C) += 0x10000;
            break;
        }
    }
}
