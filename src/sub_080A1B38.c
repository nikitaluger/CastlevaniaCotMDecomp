/* Advance an entity's behavior script: latch a halt flag from its state,
 * dispatch the current state callback, or run the normal script step and then
 * update the entity's position from the camera coordinate table. */
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

void sub_080A1B38(void *arg0) {
    void *script;
    void *state;
    s32 callback;
    u8 *self = (u8*)arg0;

    script = *(void **)(self + 0x38);
    state = *(void **)(self + 0x3C);

    if (1 & *(u16 *)((u8 *)*(void **)((u8 *)state + 0x28) + 0x14)) {
        s32 newFlags = 1 | *(u16 *)state;
        *(u16 *)state = newFlags;
    }

    if (*(u16 *)state & 1) {
        u32 *callbackTable;
        u8 *statePtr;
        u8 stateByte;
        s32 stateIndex;
        *(u8 *)((u8 *)*(void **)((u8 *)state + 0x28) + 0x01) = 0;
        {
            u8 *stateBytePtr;
            stateBytePtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(stateBytePtr + 0x19) = 0;
        }
        callbackTable = (u32 *)0x08671BB0;
        statePtr = (u8 *)arg0 + 0x18;
        sub_080C31E4(statePtr, (u8 *)arg0 + 0x22, *callbackTable);
        {
            u8 *stateBytePtr;
            stateBytePtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
        }
        stateIndex = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        statePtr += stateIndex;
        stateByte = *statePtr;
        callback = *(s32 *)((u32)(stateByte * 4) + *(u32 *)((u8 *)arg0 + 0x14));
        sub_080C31E0((s32)arg0, callback);
        return;
    }

    if (sub_08013B5C(script, state) == 0) {
        u8 *statePtr;
        u8 stateByte;
        s32 stateIndex;
        *(u32 *)((u8 *)arg0 + 0x14) = 0x0866FE5C;
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
        {
            u8 *stateBytePtr;
            stateBytePtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
        }
        stateIndex = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        statePtr = (u8 *)arg0;
        statePtr += 0x18;
        statePtr += stateIndex;
        stateByte = *statePtr;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(stateByte * 4) + *(u32 *)((u8 *)arg0 + 0x14)));
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    }
    sub_08013C8C(arg0, script);
}
