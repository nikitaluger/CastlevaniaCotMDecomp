extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallbacks;

/* Entity update: arm a 90-unit timer in the work area, notify the linked
 * object, then reset the current command slot's counter and dispatch the
 * next script command. */
void sub_0801BB04(void *arg0) {
    u8 *work;
    void *linked;
    s16 slot;
    u32 *scriptFuncPtr;

    work = *(u8 **)((u8 *)arg0 + 0x3C);
    work += 0x48;
    *(u16 *)(work + 0x16) = 0x5A;
    linked = *(void **)((u8 *)arg0 + 0x30);
    if (linked != 0) {
        sub_080C31E0(linked, *(s32 *)((u8 *)linked + 0x24));
    }
    slot = *(s16 *)((u8 *)arg0 + 0x22);
    *((u8 *)arg0 + slot * 2 + 0x19) = 0;
    scriptFuncPtr = (u32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptFuncPtr);
}
