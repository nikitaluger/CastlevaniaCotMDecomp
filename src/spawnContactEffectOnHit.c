extern void sub_08013F28(void *, s16, s16, s16, s16);
extern void sub_08013FDC(void *, s16, s16, s16, s16);

/* On a hit, spawn a contact effect at the midpoint between the entity's 0x3C
 * component and its target (variant chosen by the component's flag 4/8); with
 * no target, clear that component's active flags. */
void spawnContactEffectOnHit(u8 *self, u8 *target) {
    u8 *comp = *(u8 **)(self + 0x3C);

    if (target == NULL) {
        *(u16 *)comp = (0xFFF3 & *(u16 *)comp) | 1;
        *(void **)(comp + 0x18) = target;
    }

    if (*(u16 *)comp & 4) {
        u8 *parent = *(u8 **)(self + 0x38);
        s32 effectX, effectY, rawX, rawY;
        if (*(u16 *)(parent + 2) & 0x10) {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += 0xFFFF;
            effectX = (rawX >> 16) - *(s16 *)(target + 0xA);
        } else {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += 0xFFFF;
            effectX = (rawX >> 16) + *(s16 *)(target + 0xA);
        }
        if (*(u16 *)(parent + 2) & 0x20) {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += 0xFFFF;
            effectY = (rawY >> 16) - *(s16 *)(target + 0xC);
        } else {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += 0xFFFF;
            effectY = (rawY >> 16) + *(s16 *)(target + 0xC);
        }
        sub_08013F28(self, (s16)effectX, (s16)effectY, *(s16 *)(target + 6), *(s16 *)(target + 8));
    } else if (*(u16 *)comp & 8) {
        u8 *parent = *(u8 **)(self + 0x38);
        s32 effectX, effectY, rawX, rawY;
        if (*(u16 *)(parent + 2) & 0x10) {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += 0xFFFF;
            effectX = (rawX >> 16) - *(s16 *)(target + 0xA);
        } else {
            rawX = *(s32 *)(comp + 8);
            if (rawX < 0) rawX += 0xFFFF;
            effectX = (rawX >> 16) + *(s16 *)(target + 0xA);
        }
        if (*(u16 *)(parent + 2) & 0x20) {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += 0xFFFF;
            effectY = (rawY >> 16) - *(s16 *)(target + 0xC);
        } else {
            rawY = *(s32 *)(comp + 0xC);
            if (rawY < 0) rawY += 0xFFFF;
            effectY = (rawY >> 16) + *(s16 *)(target + 0xC);
        }
        sub_08013FDC(self, (s16)effectX, (s16)effectY, *(s16 *)(target + 6), *(s16 *)(target + 8));
    }
}
