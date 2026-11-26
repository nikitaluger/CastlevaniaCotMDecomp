void sub_08006404(void *);
void sub_08001480(void *, s32);
void sub_08061B4C(void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

extern u32 gMainWorkspace[];

/* Restores the saved graphics state, then starts one of two transitions based
 * on the global mode byte before clearing the animation frame and playing the
 * effect. */
void sub_08007AAC(void *obj) {
    u8 *self = (u8 *)obj;
    u32 modeOffset;
    u8 mode;
    s32 *lit;

    sub_08006404(obj);

    modeOffset = 0x18C4;
    mode = *(u8 *)((u8 *)gMainWorkspace + modeOffset);
    switch (mode) {
    case 1: {
        s32 paramA;
        s32 paramB;
        u32 coordsOffset;
        coordsOffset = 0x1728;
        paramA = *(s32 *)((u8 *)gMainWorkspace + coordsOffset);
        paramB = *(s32 *)((u8 *)gMainWorkspace + coordsOffset + 4);
        sub_08061B4C(obj, paramA, paramB);
        break;
    }
    case 2:
        sub_08001480(obj, 0x1A);
        break;
    default:
        break;
    }

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    lit = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *lit);
}
