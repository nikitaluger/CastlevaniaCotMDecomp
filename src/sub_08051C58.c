extern void *spawnBudgetedEffect(void*, s32);
extern void _call_via_r1(void*, void*);

/* Spawn the 8 numbered children (ids 0..7 stored at child+0x6C) of this
 * spawner, then one extra object; if any allocation fails, hand control to
 * the spawner's callback at +0x24. */
void sub_08051C58(void *obj) {
    u32 index = 0;
    void *child;
    for (;;) {
        child = spawnBudgetedEffect(obj, 0x144);
        if (child == NULL) {
            _call_via_r1(obj, *(void**)((u8*)obj + 0x24));
            return;
        }
        *(u8*)((u8*)child + 0x6C) = index;
        index++;
        if (index > 7) break;
    }
    if (spawnBudgetedEffect(obj, 0x145) == NULL) {
        _call_via_r1(obj, *(void**)((u8*)obj + 0x24));
    }
}
