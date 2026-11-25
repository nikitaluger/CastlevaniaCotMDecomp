void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* When entity+0x4C is set, clear the current script action byte, advance the
 * script, bump the new action byte and dispatch the handler picked by the new
 * command byte from the table at +0x14. */
void sub_080BDCD8(void *arg0) {
    u8 *entity = arg0;
    if (*(s8 *)(entity + 0x4C) != 0) {
        u8 *scriptCmd;
        s32 *scriptTable;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        scriptCmd = entity + 0x18;
        sub_080C31E4(scriptCmd, entity + 0x22, *scriptTable);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) += 1;
        scriptCmd = scriptCmd + *(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)((u32)*scriptCmd * 4 + *(u32 *)(entity + 0x14)));
    }
}
