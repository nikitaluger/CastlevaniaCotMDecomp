extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback[];

/* If the entity's sprite descriptor flags a script restart (bit 1 of +0x64),
 * clear the current command step counter and reinstall the global command
 * script for the entity's script slot. */
void sub_080270F8(void *arg0) {
    if (2 & *(u16 *)((u8 *)arg0 + 0x64)) {
        s16 slot = *(s16 *)((u8 *)arg0 + 0x22);
        s32 *scriptTable;
        *(u8 *)((u8 *)arg0 + slot * 2 + 0x19) = 0;
        scriptTable = gMainObjTimerCallback;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
    }
}
