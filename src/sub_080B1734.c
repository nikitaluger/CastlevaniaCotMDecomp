extern u32 gMainObjTimerCallback;

void sub_080B300C(void);
void sub_080B307C(void);
void sub_080B31AC(void *);
void sub_0808D0A4(s32);
void sub_080C31E4(void *, void *, u32);

/* Boss-defeat sequence: flag one entity type, deactivate another plus this
 * object's children, play a sound, then clear the current step's progress and
 * run the script interpreter. */
void sub_080B1734(void *arg0) {
    u8 *self = (u8 *)arg0;
    void **scriptFn;

    *(u32 *)(*(u8 **)(self + 0x3C) + 0x54) = 0x10000;
    sub_080B300C();
    sub_080B307C();
    sub_080B31AC(self);
    sub_0808D0A4(0x11);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptFn = (void **)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, (s32)*scriptFn);
}
