void sub_08097F88(s32, void *, void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
void sub_08007E24(s32);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
void sub_080A0154(s32, void *, void *, u8);
void sub_080A0194(s32, void *, void *, s32);
void sub_080A01E0(s32, void *, s32);
void sub_080A03C8(s32, void *, void *, u8);
void sub_08098338(s32, void *);

/*
 * Updates an enemy entity: sets sprite attributes from the motion step, runs
 * its attack/collision logic, and either finishes (restoring the saved handler)
 * or advances the script step and dispatches a new handler, then configures
 * its four hitbox descriptors.
 */
void sub_0809CB48(u8 *entity) {
    void *sprite;
    void *motion;
    u8 *motionEx;
    s32 handler;
    u8 zero;
    u16 spriteAttr;

    sprite = *(void **)(entity + 0x38);
    motion = *(void **)(entity + 0x3C);
    motionEx = (u8 *)motion + 0x48;
    spriteAttr = (*(u16 *)sprite & 0x0FFF) | ((u16)((*(u16 *)((u8 *)motion + 0x22) + 8) << 12));
    zero = 0;
    *(u16 *)sprite = spriteAttr;
    sub_08097F88(3, sprite, motion, *(void **)((u8 *)motion + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)motion + 0x28));

    if (*(u16 *)motion & 1) {
        u32 *scriptFn;
        u8 *stepTable;
        u8 stepByte;
        s32 stepOffset;
        updateActorWorldPosition(entity);
        sub_08007E24(0xB4);
        *(u8 *)(*(u8 **)((u8 *)motion + 0x28) + 1) = zero;
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = zero;
        }
        scriptFn = (u32 *)0x08671BB0;
        stepTable = entity + 0x18;
        sub_080C31E4(stepTable, entity + 0x22, *scriptFn);
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        stepTable += stepOffset;
        stepByte = *stepTable;
        handler = *(s32 *)((u32)(stepByte * 4) + *(u32 *)(entity + 0x14));
        sub_080C31E0((s32)entity, handler);
        return;
    }

    if (updateObjectDisplayState(sprite, motion) == 0) {
        u8 *stepTable;
        u8 stepByte;
        s32 stepOffset;
        *(u32 *)(entity + 0x14) = 0x0866FCA0;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        stepTable = entity;
        stepTable += 0x18;
        stepTable += stepOffset;
        stepByte = *stepTable;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(stepByte * 4) + *(u32 *)(entity + 0x14)));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    }
    sub_080A0154(*(s32 *)((u8 *)motionEx + 0x18), sprite, motion, *(u8 *)((u8 *)motion + 0x88));
    sub_080A0194(*(s32 *)((u8 *)motionEx + 0x1C), sprite, motion, -*(s32 *)((u8 *)motionEx + 0x38));
    sub_080A01E0(*(s32 *)((u8 *)motionEx + 0x24), motion, -*(s32 *)((u8 *)motionEx + 0x38));
    sub_080A03C8(*(s32 *)((u8 *)motionEx + 0x28), sprite, motion, *(u8 *)((u8 *)motionEx + 0x0D));
    sub_08098338(1, sprite);
    sub_08013C8C(entity, sprite);
}
