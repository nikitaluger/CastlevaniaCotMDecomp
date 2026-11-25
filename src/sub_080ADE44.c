s32 sub_080141AC(void *, void *);
s32 sub_08016238(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Advances an entity's step script: reacts to sprite/motion state changes,
 * dispatches the next script handler, then updates world coordinates. */
void sub_080ADE44(void *entity) {
    void *sprite;
    void *motion;
    s32 handler;
    u8 *self = (u8*)entity;

    sprite = *(void **)(self + 0x38);
    motion = *(void **)(self + 0x3C);

    if (sub_080141AC(sprite, motion) == 1) {
        sub_080C31E0((s32)self, *(s32 *)(self + 0x24));
        return;
    }

    if (sub_08016238(*(void **)((u8 *)motion + 0x28)) != 0) {
        s32 tmp = 1 | *(u16 *)motion;
        *(u16 *)motion = tmp;
    }

    if (1 & *(u16 *)((u8 *)*(void **)((u8 *)motion + 0x28) + 0x14)) {
        s32 tmp = 1 | *(u16 *)motion;
        *(u16 *)motion = tmp;
    }

    if (*(u16 *)motion & 1) {
        u32 *scriptTable;
        u8 *stepBase;
        u8 stepValue;
        s32 stepOffset;
        *(u8 *)((u8 *)*(void **)((u8 *)motion + 0x28) + 0x01) = 0;
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = 0;
        }
        scriptTable = (u32 *)0x08671BB0;
        stepBase = (u8 *)entity + 0x18;
        sub_080C31E4(stepBase, (u8 *)entity + 0x22, *scriptTable);
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        stepBase += stepOffset;
        stepValue = *stepBase;
        handler = *(s32 *)((u32)(stepValue * 4) + *(u32 *)((u8 *)entity + 0x14));
        sub_080C31E0((s32)entity, handler);
        return;
    }

    if (sub_08013B5C(sprite, motion) == 0) {
        u8 *stepBase;
        u8 stepValue;
        s32 stepOffset;
        *(u32 *)((u8 *)entity + 0x14) = 0x086701BC;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        stepBase = (u8 *)entity;
        stepBase += 0x18;
        stepBase += stepOffset;
        stepValue = *stepBase;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(stepValue * 4) + *(u32 *)((u8 *)entity + 0x14)));
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    }
    sub_08013C8C(entity, sprite);
}
