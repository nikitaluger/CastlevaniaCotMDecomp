extern u32 D_08671BC0[];

void stepAnimationTimer(s32, s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Ticks the object part's frame animation; when its countdown reaches zero it
 * clears a flag on each linked object and runs the next script step, then
 * advances the part's frames (0x0C frames of 8 ticks). */
void sub_080562A8(u8 *arg0) {
    u32 *sprite;
    u8 *work;
    u8 *animator;
    u8 *part;
    s32 countdown;
    u8 *stepBase;
    u8 *stepIndexPtr;
    u32 *scriptHandlers;
    u8 *node;

    sprite = *(u32 **)(arg0 + 0x38);
    work = *(u8 **)(arg0 + 0x3C);
    animator = work + 0x34;
    part = work + 0x48;
    countdown = *(s32 *)(part + 0xC) - 1;
    *(s32 *)(part + 0xC) = countdown;
    if (countdown == 0) {
        node = *(u8 **)(arg0 + 0x30);
        scriptHandlers = D_08671BC0;
        stepBase = arg0 + 0x18;
        stepIndexPtr = arg0 + 0x22;
        if (node != NULL) {
            do {
                *(u8 *)(node + 0x6C) = 0;
                node = *(u8 **)(node + 0x2C);
            } while (node != NULL);
        }
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(stepBase, stepIndexPtr, *scriptHandlers);
    }
    stepAnimationTimer((s32)sprite, (s32)animator, part, 0x0C, 8);
}
