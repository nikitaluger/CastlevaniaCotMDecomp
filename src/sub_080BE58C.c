void *spawnBudgetedEffect(s32 parent, s32 type);

/* Spawn a kind-0x1D6 object under `parent` and store `value` in its +0x4C
 * field (nothing happens if the spawn budget is exhausted). */
void sub_080BE58C(s32 parent, s32 value) {
    void *obj;

    obj = spawnBudgetedEffect(parent, 0x1D6);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = value;
    }
}
