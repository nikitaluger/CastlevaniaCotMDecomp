void sub_08013C5C(void *, void *);
s32 sub_080141AC(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

extern u32 gMainObjTimerCallback;

/* Advance one step of an entity's script: refresh its component state, run the
 * script callback for the current step, then apply the position correction. */
void sub_0804CE7C(void *entity) {
    void *state;
    void *comp;
    s32 handler;
    u8 *self = (u8*)entity;

    state = *(void **)(self + 0x38);
    comp = *(void **)(self + 0x3C);
    sub_08013C5C(self, state);
    if (sub_080141AC(state, comp) == 1)
        return;

    if (sub_08013558(state, comp, *(void **)((u8 *)comp + 0x28)) != 0)
        sub_08013978(self, *(void **)((u8 *)comp + 0x28));
    sub_080142C0(self, *(void **)((u8 *)comp + 0x28));

    if (*(u16 *)comp & 1) {
        u32 *hookSlot;
        u8 *script;
        u8 opcode;
        s32 stepOff;
        sub_08013AC4(self);
        {
            u8 *counterPtr;
            counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(counterPtr + 0x19) = 0;
        }
        hookSlot = (u32 *)0x08671BB0;
        script = (u8 *)entity + 0x18;
        sub_080C31E4(script, (u8 *)entity + 0x22, *hookSlot);
        {
            u8 *counterPtr;
            counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(counterPtr + 0x19) = *(u8 *)(counterPtr + 0x19) + 1;
        }
        stepOff = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        script += stepOff;
        opcode = *script;
        handler = *(s32 *)((u32)(opcode * 4) + *(u32 *)((u8 *)entity + 0x14));
        sub_080C31E0((s32)entity, handler);
        return;
    }

    if (sub_08013B5C(state, comp) == 0) {
        u8 *script;
        u8 opcode;
        s32 stepOff;
        *(u32 *)((u8 *)entity + 0x14) = 0x0866E4E4;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        {
            u8 *counterPtr;
            counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(counterPtr + 0x19) = *(u8 *)(counterPtr + 0x19) + 1;
        }
        stepOff = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        script = (u8 *)entity;
        script += 0x18;
        script += stepOff;
        opcode = *script;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(opcode * 4) + *(u32 *)((u8 *)entity + 0x14)));
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    }
    sub_08013C8C(entity, state);
}
