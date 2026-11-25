extern void sub_080B71A4(s32);
extern void sub_080B7288(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Script-step callback: clears two companion flags, sets the script state's
 * velocity and a facing-dependent acceleration, then resets the current step,
 * redirects the script and dispatches the handler for the new step. */
void sub_080B4588(u8 *self) {
    u8 *companion = *(u8 **)(self + 0x38);
    u8 *scriptState = *(u8 **)(self + 0x3C);
    u8 *control = scriptState + 0x48;
    u8 *scriptPtr;
    s32 accel;
    s32 *pHelperTable;

    sub_080B71A4(*(s32 *)(control + 0x0C));
    sub_080B7288(*(s32 *)(control + 0x10));
    *(u32 *)(scriptState + 0x14) = 0xFFFD0000;
    accel = (*(u16 *)(companion + 0x02) & 0x10) ? 0xFFFE8000 : 0x18000;
    *(u32 *)(scriptState + 0x10) = accel;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    pHelperTable = (s32 *)0x08671BB0;
    scriptPtr = self + 0x18;
    sub_080C31E4(scriptPtr, self + 0x22, *pHelperTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptPtr += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)scriptPtr * 4));
}
