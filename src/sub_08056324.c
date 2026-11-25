extern void sub_080C31E4(void *script, void *slot, s32 handler);

/* Reset the current command slot's counter and re-run the entity's command
 * script through the interpreter table in IWRAM (0x08671BB0). */
void sub_08056324(void *entity)
{
    void **handlerTable;
    *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
    handlerTable = (void **)0x08671BB0;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*handlerTable);
}
