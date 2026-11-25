void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* When the object's trigger byte is set: runs the current script step, advances
 * that step's action byte and dispatches the new action's handler. */
void sub_080A2054(void *arg0) {
    u8 *self = arg0;
    if (*(s8 *)(self + 0x4C) != 0) {
        u8 *scriptState;
        s32 *scriptTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        scriptState = self + 0x18;
        sub_080C31E4(scriptState, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        scriptState = scriptState + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)((u32)*scriptState * 4 + *(u32 *)(self + 0x14)));
    }
}
