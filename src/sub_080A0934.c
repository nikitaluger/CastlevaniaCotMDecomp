/* Updates an entity: sets sprite attributes from the motion step, runs its
 * animation/collision helpers, and either finishes (playing a cue and firing
 * the saved handler) or advances the script step and dispatches a new handler,
 * then reconfigures its animation state. */
void sub_08097F88(s32, void *, void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
s32 sub_08007E24(s32);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
void sub_080A2E98(void *, void *, void *);
void sub_08098338(s32, void *);

void sub_080A0934(u8 *entity) {
    void *motion;
    void *sprite;
    u8 zero;
    u8 *animState;
    u16 spriteAttr;
    u8 *reserved48;
    s32 handler;

    sprite = *(void **)(entity + 0x38);
    motion = *(void **)(entity + 0x3C);
    animState = (u8 *)motion + 0x34;
    spriteAttr = (*(u16 *)sprite & 0x0FFF) | ((u16)((*(u16 *)((u8 *)motion + 0x22) + 8) << 12));
    zero = 0;
    *(u16 *)sprite = spriteAttr;
    sub_08097F88(0, sprite, motion, *(void **)((u8 *)motion + 0x28));
    sub_08097F88(2, sprite, motion, *(void **)((u8 *)motion + 0x48));
    sub_080142C0(entity, *(void **)((u8 *)motion + 0x28));
    sub_080142C0(entity, *(void **)((u8 *)motion + 0x48));

    if (*(u16 *)motion & 1) {
        u32 *scriptFn;
        u8 *stepTable;
        u8 stepByte;
        s32 stepOffset;
        sub_08013AC4(entity);
        sub_08007E24(0xB5);
        *(u8 *)(*(u8 **)((u8 *)motion + 0x28) + 1) = zero;
        *(u8 *)(*(u8 **)((u8 *)motion + 0x48) + 1) = zero;
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

    if (sub_08013B5C(sprite, motion) == 0) {
        u8 *stepTable;
        u8 stepByte;
        s32 stepOffset;
        *(u32 *)(entity + 0x14) = 0x0866FE08;
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
    sub_080A2E98(animState, *(void **)((u8 *)motion + 0x28), *(void **)((u8 *)motion + 0x48));
    sub_08098338(1, sprite);
    sub_08013C8C(entity, sprite);
}
