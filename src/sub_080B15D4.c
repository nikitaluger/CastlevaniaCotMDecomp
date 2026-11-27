s32 signOf(s32);
s32 startScriptOnce(s32, s32, s32);
void sub_080B1960(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Moving-effect update: runs the object's motion, sets its horizontal direction
 * from its position relative to the scroll limit once it has started moving,
 * and after 24 frames switches it to state 3 and advances the script. */
void sub_080B15D4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *obj = *(u8 **)(self + 0x4C);
    s32 *scriptHandlers;
    sub_080B1960(work, obj);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 4) {
        if (signOf(*(s32 *)(work + 8)) == -1) {
            *(u8 *)(obj + 0x35) = 0xFF;
        } else {
            *(u8 *)(obj + 0x35) = 1;
        }
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x18) {
        startScriptOnce((s32)obj, 3, 1);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptHandlers = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
}
