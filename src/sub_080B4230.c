void sub_080114DC(s32, s32, s32, s32);
void sub_08011528(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Runs animation 0x11 on the actor, submits its frame data and, once the
 * status byte reports completion (bit 1), clears the script byte at +0x17 and
 * dispatches the handler from table D_08671BD8. */
void sub_080B4230(void *self) {
    s32 animState;
    s32 *handlerTable;
    s32 animController;
    s8 *selfBytes;
    void *work;

    animController = *(s32 *)((u8 *)self + 0x38);
    selfBytes = (s8 *)self;
    work = *(void **)(selfBytes + 0x3C);
    animState = (s32)work + 0x34;
    sub_080114DC(animController, animState, 0x11, 0);
    sub_08011528(animController, animState);
    if (2 & *(u8 *)((u8 *)work + 0x34)) {
        *(s8 *)((s8 *)((*(s16 *)(selfBytes + 0x22) * 2) + self) + 0x17) = 0;
        handlerTable = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *handlerTable);
    }
}
