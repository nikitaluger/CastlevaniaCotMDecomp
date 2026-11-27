extern s32 updateObjectDisplayState(void *, void *);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
struct Sprite { u8 pad[0x2A]; u8 flags; };

/* Actor update: mirror the current step flag onto the sprite highlight bit, apply the
 * display state, and, when it was not handled, temporarily advance the step index to
 * dispatch the next handler before restoring it. Finally refresh screen coordinates. */
void sub_080A9944(void *entity) {
    u8 *self = entity;
    s32 sprite = *(s32 *)(self + 0x38);
    s32 work = *(s32 *)(self + 0x3C);

    if ((*(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) & 1) != 0) {
        ((struct Sprite *)sprite)->flags |= 0x40;
    } else {
        u8 *flagPtr = (u8 *)(sprite + 0x2A);
        *flagPtr &= 0xBF;
    }
    if (updateObjectDisplayState((void *)sprite, (void *)work) == 0) {
        int stepBaseOffset = 0x18;
        s32 stepIndex;
        s32 stepOffset;

        *(u32 *)(self + 0x14) = 0x0867008C;
        *(u16 *)(self + 0x22) += 1;
        ((u8 *)(self + (*(s16 *)(self + 0x22)) * 2))[0x19]++;
        stepIndex = *(s16 *)(self + 0x22);
        stepOffset = stepIndex << 1;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)(self + stepBaseOffset + stepOffset) * 4));
        *(u16 *)(self + 0x22) -= 1;
    }
    sub_08013C8C(self, sprite);
}
