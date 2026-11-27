void stepAnimationTrack(void *, void *);
void advanceMotion(void *, u32);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

#define AI_SCRIPT_OPS 0x0866E56C   /* this variant's opcode jump table */
#define AI_SPECIAL_CALL_TABLE 0x08671BDC

/* Runs one step of an entity's behaviour script: handles contact/death flags,
 * dispatches the current opcode through the actor's jump table, then updates
 * the entity's world position. */
void sub_0804F114(void *entity) {
    void *parent;
    void *component;
    u8 *scriptPlayer;
    u8 *opcodePtr;
    u32 *callTable;
    u8 *stepPtr;
    u8 opcode;
    u32 opcodeTable;
    s32 handler;
    s32 pcOffset;

    parent = *(void **)((u8 *)entity + 0x38);
    component = *(void **)((u8 *)entity + 0x3C);
    scriptPlayer = (u8 *)component + 0x34;
    if (sub_080141AC(parent, component) == 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x1A) != 0) {
            sub_080C31E0((s32)entity, *(s32 *)((u8 *)entity + 0x24));
        }
        return;
    }
    sub_08013C5C(entity, parent);
    if (sub_08013558(parent, component, *(void **)((u8 *)component + 0x28)) != 0)
        sub_08013978(entity, *(void **)((u8 *)component + 0x28));
    sub_080142C0(entity, *(void **)((u8 *)component + 0x28));
    if (*(u16 *)component & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x1A) != 5) {
            sub_08013AC4(entity);
            *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x1B) = 0;
            callTable = (u32 *)AI_SPECIAL_CALL_TABLE;
            sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 5, *callTable);
        }
    }
    if (updateObjectDisplayState(parent, component) == 0) {
        *(u32 *)((u8 *)entity + 0x14) = AI_SCRIPT_OPS;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        stepPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;
        pcOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        opcodePtr = (u8 *)entity;
        opcodePtr += 0x18;
        opcodePtr += pcOffset;
        opcode = *opcodePtr;
        opcodeTable = *(u32 *)((u8 *)entity + 0x14);
        handler = *(s32 *)((u32)(opcode * 4) + opcodeTable);
        sub_080C31E0((s32)entity, handler);
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
        if (*(u16 *)((u8 *)entity + 2) & 0x8000) return;
        stepAnimationTrack(parent, scriptPlayer);
        advanceMotion(component, 0);
    }
    sub_08013C8C(entity, parent);
}
