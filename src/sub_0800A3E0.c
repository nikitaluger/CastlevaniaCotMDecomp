extern u16 D_080CAAAC[];
extern void sub_080C31E8(void *, void *, u16, u32);

/* Entity update: reset the current command slot's counter, then dispatch a
 * script command looked up from the work area's mode byte, passing the script
 * base, the slot field and the data pointer stored at 0x08671BD0. */
void sub_0800A3E0(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 *work = *(u8 **)(obj + 0x3C);
    s16 slot = *(s16 *)(obj + 0x22);
    u32 *pData;
    u16 *idTable;
    void *scriptBase;
    void *slotField;
    u8 mode;
    *(u8 *)(obj + slot * 2 + 0x19) = 0;
    pData = (u32 *)0x08671BD0;
    scriptBase = obj + 0x18;
    slotField = obj + 0x22;
    idTable = D_080CAAAC;
    mode = work[0x635];
    sub_080C31E8(scriptBase, slotField, idTable[mode], *pData);
}
