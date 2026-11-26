s32 sub_080141AC(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
s32 sub_08014328(void *, void *, void *);
void sub_08014314(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

extern u32 gMainObjTimerCallback;
extern u32 D_0866DF44;

/* Updates this entity's sprite and animation state, dispatches the callback
 * selected by its index, and runs the follow-up updates on its child objects. */
void sub_0803A6A0(void *arg0) {
    void *obj;
    void *state;
    u8 *entity = (u8 *)arg0;

    obj = *(void **)(entity + 0x38);
    state = *(void **)(entity + 0x3C);

    *(u16 *)obj = (*(u16 *)obj & 0x0FFF) | ((u16)((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u32 *)((u8 *)state + 0x08) = *(u32 *)(entity + 0x5C);
    *(u32 *)((u8 *)state + 0x0C) = *(u32 *)(entity + 0x6C);

    if (sub_080141AC(obj, state) == 1)
        return;

    if (sub_08013558(obj, state, *(void **)((u8 *)state + 0x28)) != 0)
        sub_08013978(arg0, *(void **)((u8 *)state + 0x28));

    sub_080142C0(*(void **)(entity + 0x28), *(void **)((u8 *)state + 0x28));
    sub_080142C0(*(void **)(entity + 0x28), *(void **)((u8 *)state + 0x48));

    if (*(u8 *)(entity + 0x7C) != 0) {
        u32 *callbackTable;
        u8 *callbackArgs;
        u8 callbackIndex;
        s32 entryOffset;
        {
            u8 *entry;
            entry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(entry + 0x19) = 0;
        }
        callbackTable = &gMainObjTimerCallback;
        callbackArgs = entity + 0x18;
        sub_080C31E4(callbackArgs, entity + 0x22, *callbackTable);
        {
            u8 *entry;
            entry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(entry + 0x19) = *(u8 *)(entry + 0x19) + 1;
        }
        entryOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        callbackArgs += entryOffset;
        callbackIndex = *callbackArgs;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(callbackIndex * 4) + *(u32 *)(entity + 0x14)));
        return;
    }

    {
        u8 *callbackArgs;
        u8 callbackIndex;
        s32 entryOffset;
        *(u32 *)(entity + 0x14) = (u32)&D_0866DF44;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        {
            u8 *entry;
            entry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(entry + 0x19) = *(u8 *)(entry + 0x19) + 1;
        }
        entryOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        callbackArgs = entity;
        callbackArgs += 0x18;
        callbackArgs += entryOffset;
        callbackIndex = *callbackArgs;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(callbackIndex * 4) + *(u32 *)(entity + 0x14)));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    }

    if (sub_08014328(*(void **)(entity + 0x28), obj, state) != 0) {
        sub_08014314(state, *(void **)((u8 *)state + 0x28));
        sub_08014314(state, *(void **)((u8 *)state + 0x48));
    }
    sub_08013C8C(arg0, obj);
}
