extern void spawnContactEffectChildA(void *, s16, s16, s16, s16);
extern void spawnContactEffectChildB(void *, s16, s16, s16, s16);

/* On a hit, spawn a contact effect at the component's fixed-point world
 * position offset by the target's position, choosing child A or B from the
 * component's pending-spawn flag; with no target, clear those flags and the
 * target pointer. */
void spawnContactEffectOnHit(u8 *self, u8 *target) {
    u8 *comp = *(u8 **)(self + 0x3C);

    if (target == NULL) {
        *(u16 *)comp = (SPAWN_STATE_CLEAR_CHILDREN & *(u16 *)comp) | SPAWN_STATE_ACTIVE;
        *(void **)(comp + 0x18) = target;
    }

    if (*(u16 *)comp & SPAWN_STATE_CHILD_A) {
        u8 *parent = *(u8 **)(self + 0x38);
        s32 effectX, effectY, rawX, rawY;
        if (*(u16 *)(parent + 2) & ORIGIN_FLIP_X) {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += FIXED_TRUNC_BIAS;
            effectX = (rawX >> 16) - *(s16 *)(target + 0xA);
        } else {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += FIXED_TRUNC_BIAS;
            effectX = (rawX >> 16) + *(s16 *)(target + 0xA);
        }
        if (*(u16 *)(parent + 2) & ORIGIN_FLIP_Y) {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += FIXED_TRUNC_BIAS;
            effectY = (rawY >> 16) - *(s16 *)(target + 0xC);
        } else {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += FIXED_TRUNC_BIAS;
            effectY = (rawY >> 16) + *(s16 *)(target + 0xC);
        }
        spawnContactEffectChildA(self, (s16)effectX, (s16)effectY, *(s16 *)(target + 6), *(s16 *)(target + 8));
    } else if (*(u16 *)comp & SPAWN_STATE_CHILD_B) {
        u8 *parent = *(u8 **)(self + 0x38);
        s32 effectX, effectY, rawX, rawY;
        if (*(u16 *)(parent + 2) & ORIGIN_FLIP_X) {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += FIXED_TRUNC_BIAS;
            effectX = (rawX >> 16) - *(s16 *)(target + 0xA);
        } else {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += FIXED_TRUNC_BIAS;
            effectX = (rawX >> 16) + *(s16 *)(target + 0xA);
        }
        if (*(u16 *)(parent + 2) & ORIGIN_FLIP_Y) {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += FIXED_TRUNC_BIAS;
            effectY = (rawY >> 16) - *(s16 *)(target + 0xC);
        } else {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += FIXED_TRUNC_BIAS;
            effectY = (rawY >> 16) + *(s16 *)(target + 0xC);
        }
        spawnContactEffectChildB(self, (s16)effectX, (s16)effectY, *(s16 *)(target + 6), *(s16 *)(target + 8));
    }
}
