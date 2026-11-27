/* Clear the alternate sub-step byte (+0x17) of the actor's current script
 * step, then invoke the gMenuScriptCallback script-advance callback with the actor's
 * step table, step index and the gMenuState argument. */
extern void sub_080C31E8(void *, void *, void *, void *);

void sub_08010BFC(void *arg0) {
    u8 *self = (u8*)arg0;
    void **advanceCb;
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x17) = 0;
    advanceCb = (void**)0x08671BD8;
    sub_080C31E8(self + 0x18, self + 0x22, *(void**)0x020278D0, *advanceCb);
}
