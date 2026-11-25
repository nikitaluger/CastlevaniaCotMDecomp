void sub_080C31E4(void *, void *, s32);

/* Script-step handler: once the entity has no children left, clear the current
 * slot's wait byte and restart script dispatch with the 0x08671BB4 handler. */
void sub_08010C2C(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 children = *(s32 *)(self + 0x30);
    if (children == 0) {
        s32 *handlers;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = (u8)children;
        handlers = (s32 *)0x08671BB4;
        sub_080C31E4(self + 0x18, self + 0x22, *handlers);
    }
}
