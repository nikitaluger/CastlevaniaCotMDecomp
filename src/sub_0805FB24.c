extern void *sub_080014D0(void *parent, s32 type);
extern void sub_0805FBCC(void *obj);

/* Spawn budget for this object class, at 0x020279E0 (released on despawn). */
#define gSpawnBudget (*(s16 *)0x020279E0)

/*
 * Allocates one object of `type` under `parent` as long as the class spawn
 * budget is positive, decrements the budget and installs the slot-releasing
 * destructor at +0x24. Returns NULL when the budget is exhausted or the
 * allocation fails.
 */
void *sub_0805FB24(void *parent, s32 type) {
    void *obj;

    if (gSpawnBudget > 0) {
        obj = sub_080014D0(parent, type);
        if (obj != NULL) {
            gSpawnBudget = (u16)gSpawnBudget - 1;
            *(void **)((u8 *)obj + 0x24) = (void *)sub_0805FBCC;
            return obj;
        }
    }
    return NULL;
}
