extern void sub_080C31E8(void *script, void *slot, s32 command, s32 handler);

/* Clears the current byte of the entity's secondary script-state slot (+0x17)
 * and dispatches command 6 through the interpreter table at 0x08671BD8. */
void sub_0801088C(void *entity) {
    u8 *self = (u8 *)entity;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
    {
        s32 *handlerTable = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 6, *handlerTable);
    }
}
