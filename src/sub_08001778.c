extern void sub_080C31E4(void *script, void *slot, s32 handler);

/* Clears the current command byte of the entity's script and dispatches the
 * script through the interpreter table in IWRAM (0x08671BB0). */
void sub_08001778(void *entity)
{
    void **handlerTable;
    *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
    handlerTable = (void **)0x08671BB0;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*handlerTable);
}
