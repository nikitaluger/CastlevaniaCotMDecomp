s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C5C(void *, void *);
void sub_080C31E8(void *, void *, u32, u32);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
s32 sub_080C31E0(s32, s32);

/* Animation update: advances an entity's animation/state bytes, dispatches per-frame
 * handlers, and calls the entity's update function when the animation finishes. */
void sub_0804A88C(void *arg0) {
    void *obj;
    void *state;
    u8 *stateBytePtr;
    u32 *handlerSlot;
    u8 *stateByteBase;
    u8 funcIndexByte;
    u32 funcTable;
    s32 func;
    s32 idx;

    obj = *(void **)((u8 *)arg0 + 0x38);
    state = *(void **)((u8 *)arg0 + 0x3C);
    sub_08013C5C(arg0, obj);
    if (sub_080141AC(obj, state) == 1) {
        sub_080C31E0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    if (sub_08013558(obj, state, *(void **)((u8 *)state + 0x28)) != 0)
        sub_08013978(arg0, *(void **)((u8 *)state + 0x28));
    sub_080142C0(arg0, *(void **)((u8 *)state + 0x28));
    if (*(u16 *)state & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x1A) != 6) {
            sub_08013AC4(arg0);
            *(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x1B) = 0;
            handlerSlot = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 6, *handlerSlot);
        }
    }
    if (updateObjectDisplayState(obj, state) == 0) {
        *(u32 *)((u8 *)arg0 + 0x14) = 0x0866E41C;
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
        stateByteBase = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stateByteBase + 0x19) = *(u8 *)(stateByteBase + 0x19) + 1;
        idx = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        stateBytePtr = (u8 *)arg0;
        stateBytePtr += 0x18;
        stateBytePtr += idx;
        funcIndexByte = *stateBytePtr;
        funcTable = *(u32 *)((u8 *)arg0 + 0x14);
        func = *(s32 *)((u32)(funcIndexByte * 4) + funcTable);
        sub_080C31E0((s32)arg0, func);
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    }
    sub_08013C8C(arg0, obj);
}
