void sub_08013C5C(void*, void*);
s32 sub_080141AC(void*, void*);
s32 sub_08013558(void*, void*, void*);
void sub_08013978(void*, void*);
void sub_080142C0(void*, void*);
void sub_08013AC4(void*);
s32 sub_08013B5C(void*, void*);
void sub_08013C8C(void*, void*);
void sub_080C31E0(void*, void*);
void sub_080C31E8(void*, void*, s32, s32);
void sub_08005E80(s32);
void sub_080113A8(void*, void*);
extern s32 D_08671BDC;

/* Runs one step of an entity's scripted behaviour: checks visibility/contact,
 * handles a flip request with a sound cue, advances the step script and
 * dispatches the current opcode through the entity's jump table. */
void sub_08042C58(void *entity) {
    void *parent;
    void *component;
    void *scriptPlayer;
    void *flipStepPtr;
    void *dispatchStepPtr;
    s32 pcOffset;
    u8 *opcodePtr;
    u8 opcode;
    s32 *callTable;

    parent = *(void **)((u8 *)entity + 0x38);
    component = *(void **)((u8 *)entity + 0x3C);
    scriptPlayer = (u8 *)component + 0x34;
    if (sub_080141AC(parent, component) != 1 ||
        (((u8 *)((s32)((s16)*(u16 *)((u8 *)entity + 0x22) * 2) + (s32)entity))[0x1A] == 1)) {
        sub_08013C5C(entity, parent);
        if (sub_08013558(parent, component, *(void **)((u8 *)component + 0x28)) != 0)
            sub_08013978(entity, *(void **)((u8 *)component + 0x28));
        sub_080142C0(entity, *(void **)((u8 *)component + 0x28));
        if ((*(u16 *)component & 1) &&
            (((u8 *)((s32)((s16)*(u16 *)((u8 *)entity + 0x22) * 2) + (s32)entity))[0x1A] != 2)) {
            sub_08013AC4(entity);
            sub_08005E80(0x85);
            flipStepPtr = (void *)((s32)((s16)*(u16 *)((u8 *)entity + 0x22) * 2) + (s32)entity);
            *(u8 *)((u8 *)flipStepPtr + 0x1B) = 0;
            callTable = &D_08671BDC;
            sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 2, *callTable);
        }
        if (sub_08013B5C(parent, component) != 0) goto common;
        *(void **)((u8 *)entity + 0x14) = (void *)0x0866E1B4;
        *(u16 *)((u8 *)entity + 0x22) = (u16)(*(u16 *)((u8 *)entity + 0x22) + 1);
        dispatchStepPtr = (void *)((s32)((s16)*(u16 *)((u8 *)entity + 0x22) * 2) + (s32)entity);
        *(u8 *)((u8 *)dispatchStepPtr + 0x19) = (u8)(*(u8 *)((u8 *)dispatchStepPtr + 0x19) + 1);
        pcOffset = (s16)*(s16 *)((u8 *)entity + 0x22) * 2;
        opcodePtr = (u8 *)entity + 0x18;
        opcode = *(u8 *)(pcOffset + opcodePtr);
        sub_080C31E0(entity, *(void **)((u8 *)*(void **)((u8 *)entity + 0x14) + opcode * 4));
        *(u16 *)((u8 *)entity + 0x22) = (u16)(*(u16 *)((u8 *)entity + 0x22) - 1);
        if ((*(u16 *)((u8 *)entity + 0x02) & 0x8000) != 0) return;
        sub_080113A8(parent, scriptPlayer);
    common:
        sub_08013C8C(entity, parent);
    }
}
