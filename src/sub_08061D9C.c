extern s32 sub_08061D74(u8);

/* Looks up the event record for the (map, x, y) triple in the 4-byte-entry
 * table and reports whether its id's progress flag is already set; the table
 * ends with an entry whose id is 0xFF. */
s32 sub_08061D9C(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = 0;
    int fieldOffset;
    u8 *base = (u8 *)0x080DAB3C;
    u8 *fields = base;
    u8 *fields2 = base;
    u8 *third = base + 3;
    u8 *entry = base;
    for (;;) {
        s32 off = i * 4;
        if (*entry == 0xFF) return 0;
        fieldOffset = (u32)fields + 1;
        if (*(u8*)(off + fieldOffset) == arg0) {
            fieldOffset = (u32)fields2 + 2;
            if (*(u8*)(off + fieldOffset) == arg1 &&
                *(u8*)(off + (u32)third) == arg2)
                return sub_08061D74(*entry);
        }
        entry += 4;
        i++;
    }
}
