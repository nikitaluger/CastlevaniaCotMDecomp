extern u8 D_00000009;        /* its address is the constant 9: number of records */
extern u8 D_08106E38[];       /* resource key table, 8 bytes per id */
extern u8 D_08106DCC[];       /* table of active resource records */

typedef struct { u32 key; s32 refCount; } ResourceSlot;
typedef struct { ResourceSlot *slot; u32 data; u32 param; } ResourceRecord;

/* Return 1 when resource `id` is loaded: find its key in the resource table,
 * then scan the active records for a matching slot with a positive ref count. */
s32 isResourceLoaded(u16 id)
{
    u16 idx = id;
    u32 i = 0;
    u16 count = (u16)((u32)&D_00000009);
    if (i < count) {
        u8 *base = D_08106E38;
        u32 *key = (u32 *)(base + (u32)idx * 8);
        u32 bound = count;
        ResourceRecord *rec = (ResourceRecord *)D_08106DCC;
        u32 mask = 0xFFFF;
        do {
            ResourceSlot *slot = rec->slot;
            if (slot != 0) {
                if (slot->key == *key) {
                    s32 refs = slot->refCount;
                    if ((refs & mask) != 0) {
                        if (refs >= 0) {
                            return 1;
                        }
                    }
                }
            }
            rec++;
            i++;
        } while (i < bound);
    }
    return 0;
}
