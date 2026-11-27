extern void *spawnBudgetedEffect(s32, s32);

/* Spawns a kind-0x1A7 object owned by `owner` and stores `variant` in its +0x4C field. */
void *sub_080B0614(s32 owner, u8 variant) {
    void *obj = spawnBudgetedEffect(owner, 0x1A7);
    if (obj != NULL) {
        *(u8 *)((u8 *)obj + 0x4C) = variant;
    }
    return obj;
}

extern void *spawnBudgetedEffect(s32, s32);

/* Spawns a kind-0x1A8 object and fills in its spawn parameters: +0x4C variant,
 * +0x5C value, +0x6C angle, +0x7C word and +0x8C sub-variant (0 unless variant==1). */
void *sub_080B063C(s32 owner, u8 variant, s32 value, s32 angle, u16 word, u8 subVariant) {
    void *obj = spawnBudgetedEffect(owner, 0x1A8);
    if (obj == NULL) return NULL;
    *(u8 *)((u8 *)obj + 0x4C) = variant;
    *(s32 *)((u8 *)obj + 0x5C) = value;
    *(s32 *)((u8 *)obj + 0x6C) = angle;
    *(u32 *)((u8 *)obj + 0x7C) = word;
    if (variant == 1) *(u8 *)((u8 *)obj + 0x8C) = subVariant;
    else *(u8 *)((u8 *)obj + 0x8C) = 0;
    return obj;
}

extern void *spawnBudgetedEffect(s32, s32);

/* Allocates three kind-0x1A9 objects (using the global at 0x02027860 as owner)
 * and stores them into out[0..2]. */
void sub_080B06CC(s32 *out) {
    s32 *slot = out;
    u32 i = 0;
    do {
        *slot = (s32)spawnBudgetedEffect(*(s32 *)0x02027860, 0x1A9);
        slot++;
        i++;
    } while (i <= 2);
}

extern s32 getAngleFromDelta(s32, s32);

/* Sets up three pre-allocated objects as a spread: same variant/value, angles
 * 45 degrees apart starting from the direction toward (x,y), and a flag set. */
void sub_080B06F4(void **objects, s32 x, s32 y) {
    void **slot = objects;
    s32 angle = getAngleFromDelta(*(s32 *)((u8 *)0x02025FF0 + 0x1750) - y,
                            *(s32 *)((u8 *)0x02025FF0 + 0x174C) - x) + (s32)0xFFFFE000;
    u32 i = 0;
    do {
        void *obj = *slot;
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
        *(s32 *)((u8 *)obj + 0x6C) = angle;
        obj = *slot;
        slot++;
        *(u8 *)((u8 *)obj + 0x7C) = 1;
        angle += 0x2000;
        i++;
    } while (i <= 2);
}
