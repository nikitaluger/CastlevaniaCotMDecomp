void *spawnBudgetedEffect(void *pool, s32 size);

/* Spawn an object of size 0x192 from the pool, but only while fewer than 0x14
 * already exist in the pool's object list; store x at +0x4C and param at +0x5C. */
void sub_080A54C0(void *pool, s32 x, s32 param) {
    u32 count = 0;
    u8 *obj = *(u8 **)((u8 *)pool + 0x30);
    if (obj != NULL) {
        do {
            if (*(s16 *)obj == 0x192) {
                count += 1;
            }
            obj = *(u8 **)(obj + 0x2C);
        } while (obj != NULL);
    }
    if (count <= 0x13U) {
        obj = spawnBudgetedEffect(pool, 0x192);
        if (obj != NULL) {
            *(s32 *)(obj + 0x4C) = x;
            *(s32 *)(obj + 0x5C) = param;
        }
    }
}
