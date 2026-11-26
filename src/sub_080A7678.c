extern u32 D_081020D4[];
extern u32 gMainObjTimerCallback;

/* Script-step callback: update the control block shared with the companion,
 * then, when a trigger flag is set and its counter is zero, load a mode value
 * from the D_081020D4 table into the script state, reset the current script
 * step and dispatch the script handler. */
void sub_080A7678(void *entity) {
    u32 companion;
    void *scriptState;
    s32 control;
    s32 triggerValue;
    s32 *tablePtr;

    companion = *((u32 *)((u8 *)entity + 0x38));
    scriptState = *((void **)((u8 *)entity + 0x3C));
    control = (s32)scriptState + 0x48;
    sub_080A860C(entity, control);
    sub_080A8940(companion, control);
    if (*((u8 *)((u8 *)scriptState + 0x120)) != 0) {
        triggerValue = *((s32 *)((u8 *)scriptState + 0x110));
        if (triggerValue == 0) {
            *((u32 *)((u8 *)scriptState + 0x130)) = D_081020D4[*((u8 *)((u8 *)entity + 0x4C))];
            *((s8 *)((u8 *)entity + *((s16 *)((u8 *)entity + 0x22)) * 2 + 0x19)) = (s8)triggerValue;
            tablePtr = &gMainObjTimerCallback;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *tablePtr);
        }
    }
}
