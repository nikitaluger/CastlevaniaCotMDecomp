void sub_08013C5C(void *, void *);
s32 sub_080141AC(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

extern u32 gScriptStepCallbackTable;

/* Advances an entity's step script: handles sprite/motion state and target
 * interactions, dispatches the next handler, then updates world coordinates. */
void sub_0803FB20(void *entity) {
    void *sprite;
    void *motion;
    s32 handler;
    u8 *self = (u8*)entity;

    sprite = *(void **)(self + 0x38);
    motion = *(void **)(self + 0x3C);
    sub_08013C5C(self, sprite);
    if (sub_080141AC(sprite, motion) == 1)
        return;

    if (sub_08013558(sprite, motion, *(void **)((u8 *)motion + 0x28)) != 0)
        sub_08013978(self, *(void **)((u8 *)motion + 0x28));
    sub_080142C0(self, *(void **)((u8 *)motion + 0x28));

    if (*(u16 *)motion & 1) {
        u32 *scriptTable;
        u8 *stepBase;
        u8 stepValue;
        s32 stepOffset;
        sub_08013AC4(self);
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

    if (updateObjectDisplayState(sprite, motion) == 0) {
        u8 *stepBase;
        u8 stepValue;
        s32 stepOffset;
        *(u32 *)((u8 *)entity + 0x14) = 0x0866E0B0;
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
