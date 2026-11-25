extern u8 D_08106DCC[];
extern u8 D_08106E38[];
extern void sub_080C0ABC(s32, s32);
extern void sub_080C0368(void *);

inline u8 *inline_fn(u8 **arg0, u32 arg1) { return (*arg0) + arg1; }

/* Sound-record dispatcher: resolve a 16-bit ID through the entry table
 * (D_08106E38) and record table (D_08106DCC); start the record with
 * sub_080C0ABC when its value differs from the entry (or its second word is
 * zero), otherwise release it via sub_080C0368 when that word is negative. */
void sub_080C04B8(u32 soundId) {
    u32 entryOff;
    u8 *records;
    u8 *entries;
    u8 **entriesPtr;
    s32 *record;
    s32 value;
    s32 secondWord;
    entryOff = soundId << 16;
    records = D_08106DCC;
    entries = D_08106E38;
    entryOff >>= 13;
    value = *(u16 *)((entryOff + entries) + 4);
    record = *(s32 **)(records + (value * 12));
    value = *record;
    entriesPtr = &entries;
    if (value != *(s32 *)inline_fn(entriesPtr, entryOff)) {
        sub_080C0ABC((s32)record, *(s32 *)inline_fn(entriesPtr, entryOff));
    } else {
        secondWord = *(s32 *)((u8 *)record + 4);
        if (*(u16 *)((u8 *)record + 4) == 0) {
            sub_080C0ABC((s32)record, value);
        } else if (secondWord < 0) {
            sub_080C0368(record);
        }
    }
}
