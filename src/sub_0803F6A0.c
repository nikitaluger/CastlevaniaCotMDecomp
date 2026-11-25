void sub_080C31E4(void *, void *, s32);

/* If the entity's sprite descriptor requests a script restart (bit 1 of +0x5C),
 * clear the current command step counter and dispatch the next command from the
 * global command table. */
void sub_0803F6A0(void *entity) {
    if (2 & *(u16 *)((u8 *)entity + 0x5C)) {
        ((u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2))[0x19] = 0;
        {
            s32 *scriptTable;
            scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptTable);
        }
    }
}
