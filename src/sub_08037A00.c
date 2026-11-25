/* Updates an entity: runs its sprite/collision helpers, then either finishes
 * the script (firing the saved handler) or advances the script step and
 * dispatches a new handler, falling back to hitbox upkeep. */
void sub_08013C5C(void *, void *);
s32 sub_080141AC(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080142C0(void *, void *);
void sub_08014314(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

extern u32 D_0866DE5C;
extern u32 D_08671BB0;

void sub_08037A00(void *entity) {
    void *sprite;
    void *motion;
    void *motionEx;
    s32 handler;

    sprite = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    motionEx = (u8 *)motion + 0x48;
    sub_08013C5C(entity, sprite);
    if (sub_080141AC(sprite, motion) == 1) {
        *(u8 *)(((void **)motionEx)[3] + 1) = 0;
        *(u8 *)(((void **)motionEx)[4] + 1) = 0;
        return;
    }
    if (sub_08013558(sprite, motion, *(void **)((u8 *)motion + 0x28)) != 0)
        sub_08013978(entity, *(void **)((u8 *)motion + 0x28));
    sub_080142C0(entity, *(void **)((u8 *)motion + 0x28));
    sub_080142C0(entity, ((void **)motionEx)[3]);
    sub_080142C0(entity, ((void **)motionEx)[4]);
    if (*(u16 *)motion & 1) {
        u32 *scriptFn;
        u8 *stepTable;
        u8 stepByte;
        u32 handlerTable;
        s32 stepOffset;
        sub_08013AC4(entity);
        *(u8 *)(((void **)motionEx)[3] + 1) = 0;
        *(u8 *)(((void **)motionEx)[4] + 1) = 0;
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = 0;
        }
        scriptFn = (u32 *)&D_08671BB0;
        stepTable = (u8 *)entity + 0x18;
        sub_080C31E4(stepTable, (u8 *)entity + 0x22, *scriptFn);
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        stepTable += stepOffset;
        stepByte = *stepTable;
        handlerTable = *(u32 *)((u8 *)entity + 0x14);
        handler = *(s32 *)((u32)(stepByte * 4) + handlerTable);
        sub_080C31E0((s32)entity, handler);
        return;
    } else {
        if (sub_08013B5C(sprite, motion) == 0) {
            u8 *stepData;
            u8 *stepTable;
            u8 stepByte;
            u32 handlerTable;
            s32 stepOffset;
            *(u32 *)((u8 *)entity + 0x14) = (u32)0x0866DE5C;
            *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
            stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
            stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
            stepTable = (u8 *)entity;
            stepTable += 0x18;
            stepTable += stepOffset;
            stepByte = *stepTable;
            handlerTable = *(u32 *)((u8 *)entity + 0x14);
            sub_080C31E0((s32)entity, *(s32 *)((u32)(stepByte * 4) + handlerTable));
            *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
        } else {
            sub_08014314(motion, ((void **)motionEx)[3]);
            sub_08014314(motion, ((void **)motionEx)[4]);
        }
        sub_08013C8C(entity, sprite);
    }
}
