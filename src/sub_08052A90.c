s32 sub_080141AC(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
extern u32 gScriptStepCallbackTable;

/* Animation update: mirrors a child-object flag into the entity's state, dispatches a
 * handler, then calls the function selected by the per-animation state byte. */
void sub_08052A90(void *arg0) {
    void *obj;
    void *state;

    obj = *(void **)((u8 *)arg0 + 0x38);
    state = *(void **)((u8 *)arg0 + 0x3C);
    if (sub_080141AC(obj, state) == 1) {
        sub_080C31E0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    if (1 & *(u16 *)((u8 *)*(void **)((u8 *)state + 0x28) + 0x14)) {
        s32 flags = 1 | *(u16 *)state;
        *(u16 *)state = flags;
    }
    if (1 & *(u16 *)state) {
        u32 *handlerSlot;
        u8 *statePtr;
        u8 funcIndex;
        s32 idx;
        ((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2)[0x19] = 0;
        handlerSlot = &gScriptStepCallbackTable;
        statePtr = (u8 *)arg0 + 0x18;
        sub_080C31E4(statePtr, (u8 *)arg0 + 0x22, *handlerSlot);
        ((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2)[0x19]++;
        idx = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        statePtr += idx;
        funcIndex = *statePtr;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(funcIndex * 4) + *(u32 *)((u8 *)arg0 + 0x14)));
        return;
    }
    if (updateObjectDisplayState(obj, state) == 0) {
        u8 *statePtr;
        u8 funcIndex;
        s32 idx;
        *(u32 *)((u8 *)arg0 + 0x14) = 0x0866E66C;
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
        ((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2)[0x19]++;
        idx = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        statePtr = (u8 *)arg0;
        statePtr += 0x18;
        statePtr += idx;
        funcIndex = *statePtr;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(funcIndex * 4) + *(u32 *)((u8 *)arg0 + 0x14)));
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    }
    sub_08013C8C(arg0, obj);
}
