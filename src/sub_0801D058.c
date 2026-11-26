void setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Start the actor's model animation at frame 0x1D; if its low status bits
   (0x64 & 2) are set, clear the current step's byte at +0x19 and run the
   0x08671BB0 script handler. */
void sub_0801D058(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 model = *(s32 *)(self + 0x38);
    u8 *anim = *(u8 **)(self + 0x3C) + 0x34;
    void **scriptFn;

    setAnimationFrame(model, anim, 0x1D, 1);
    if (2 & *(u16 *)(self + 0x64)) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptFn = (void **)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (s32)*scriptFn);
    }
}
