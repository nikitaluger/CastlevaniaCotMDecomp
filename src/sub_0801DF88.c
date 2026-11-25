void sub_080C31E4(void *, void *, s32);

/* If the entity's script state asks for a restart (s16 at scriptState+0x52),
 * clear the current command step counter and reinstall the global command
 * script (pointer at 0x08671BB0) for this entity's script slot. */
void sub_0801DF88(void *arg0) {
    u8 *obj = arg0;
    u8 *scriptState = *(u8 **)(obj + 0x3C);
    s16 *restart = (s16 *)(scriptState + 0x48);
    if (restart[5] != 0) {
        void **scriptTable;
        ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19] = 0;
        scriptTable = (void **)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*scriptTable);
    }
}
