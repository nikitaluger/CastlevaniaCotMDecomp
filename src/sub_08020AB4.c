extern void sub_080C31E4(void *, void *, s32);

/* Restart the entity's command script with fresh timers: set two u16 fields in
 * the script state (state+8 = 8, state+0x1C = 3), clear the current step
 * counter and reinstall the global command script (pointer at 0x08671BB0). */
void sub_08020AB4(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 *state = *(u8 **)(obj + 0x3C) + 0x48;
    void **scriptTable;
    u8 zero;
    zero = 0;
    *(u16 *)(state + 8) = 8;
    *(u16 *)(state + 0x1C) = 3;
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    scriptTable = (void **)0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*scriptTable);
}
