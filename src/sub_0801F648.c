extern void sub_080C31E4(void *, void *, s32);

/* Restart the entity's command script with fresh timers: set two u16 fields in
 * the script state (state+8 = 10, state+0x28 = 6), clear the current step
 * counter and reinstall the global command script (pointer at 0x08671BB0). */
void sub_0801F648(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    u8 *state = *(u8 **)(obj + 0x3C) + 0x48;
    u8 zero = 0;
    void **scriptTable;

    *(u16 *)(state + 8) = 0xA;
    *(u16 *)(state + 0x28) = 6;
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    scriptTable = (void **)0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*scriptTable);
}
