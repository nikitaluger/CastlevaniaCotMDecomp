void copyPoseAttrs(void *, void *);
extern u8 D_080CF1F8[];
extern u8 D_080CF230[];
extern u8 D_080CF268[];

/* Look up the parameter index matching the key at source+0x28, then copy that
 * entry from each of three tables into the three target objects. */
void sub_0803B140(u32 count, void *source, void *targets, void *lookup) {
    void **dst = (void **)targets;
    u16 entryIndex = 0;
    u32 i = 0;
    u32 tableA = (u32)D_080CF1F8;
    u16 *entry = (u16 *)lookup;
    u16 key;

    if (entryIndex < count) {
        key = *(u16 *)((u8 *)source + 0x28);
        for (; i < count; i++) {
            u16 entryKey = *entry;
            if (key == entryKey) entryIndex = entry[1];
            entry += 2;
        }
    }

    copyPoseAttrs(dst[0], (void *)((entryIndex << 3) + tableA));
    copyPoseAttrs(dst[1], (void *)((entryIndex << 3) + D_080CF230));
    copyPoseAttrs(dst[2], (void *)((entryIndex << 3) + D_080CF268));
}
