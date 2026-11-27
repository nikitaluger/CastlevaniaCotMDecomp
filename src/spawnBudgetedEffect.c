extern void *createChildObject(s32);
extern s32 sub_0805FBCC;

/* Spawns one budgeted object: while the shared slot counter at 0x020279E0 is
 * positive, allocate via createChildObject, consume a slot and install sub_0805FBCC
 * as the destructor (which refunds the slot). Returns NULL if none available. */
void *spawnBudgetedEffect(s32 parent) {
    void *obj;
    if (((s32)(*((s16 *)0x020279E0))) > 0) {
        obj = createChildObject(parent);
        if (obj != NULL) {
            *((s16 *)0x020279E0) = ((u16)(*((s16 *)0x020279E0))) - 1;
            *((s32 **)(0x24 + ((s8 *)obj))) = &sub_0805FBCC;
            return obj;
        }
    }
    if (obj) {
        return NULL;
    } else {
        return NULL;
    }
}
