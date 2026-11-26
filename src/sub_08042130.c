extern void copyPoseAttrs(void *, void *, void *);
extern u8 D_080CF4D0[][8];

/* Pick one of four parameter sets from a table according to a state value,
 * then copy it into the target object named by the caller. */
void sub_08042130(void *source, void *state) {
    u32 paramIndex = 0;
    u32 selector;
    *(u8 *)(*(u8 **)((u8 *)source + 4) + 1) = 1;
    selector = *(u16 *)((u8 *)state + 0x28) - 0x0E;
    if (selector <= 0x15) {
        switch (selector) {
            case 4:
                paramIndex = 2;
                break;
            case 9:
                paramIndex = 3;
                break;
            case 0:
            case 13:
            case 17:
            case 21:
                paramIndex = 1;
                break;
        }
    }
    copyPoseAttrs(*(void **)((u8 *)source + 4), D_080CF4D0[paramIndex], D_080CF4D0);
}
