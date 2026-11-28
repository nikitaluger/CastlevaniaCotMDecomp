s32 checkActorViewBounds(void *, void *);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
s32 updateMotionState(void *, void *, void *);
void clearMotionSpriteOverride(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 _call_via_r1(s32, s32);
void _call_via_r2(void *, void *, u32);

extern u32 gMainObjTimerCallbacks;
extern u32 D_0866DF44;

/* Update a scripted entity attachment: sync its sprite attributes and work
 * position, test camera bounds and contact, upload pending graphics, dispatch
 * the current script step from the 0x0866DF44 table, then advance its motion
 * state and screen position. */
void updateScriptedEffectAttachment(void *arg0) {
    void *obj;
    void *state;
    u8 *entity = (u8 *)arg0;

    obj = *(void **)(entity + 0x38);
    state = *(void **)(entity + 0x3C);

    *(u16 *)obj = (*(u16 *)obj & 0x0FFF) | ((u16)((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u32 *)((u8 *)state + 0x08) = *(u32 *)(entity + 0x5C);
    *(u32 *)((u8 *)state + 0x0C) = *(u32 *)(entity + 0x6C);

    if (checkActorViewBounds(obj, state) == 1)
        return;

    if (detectActorHit(obj, state, *(void **)((u8 *)state + 0x28)) != 0)
        spawnContactEffectOnHit(arg0, *(void **)((u8 *)state + 0x28));

    uploadPendingSpriteGraphic(*(void **)(entity + 0x28), *(void **)((u8 *)state + 0x28));
    uploadPendingSpriteGraphic(*(void **)(entity + 0x28), *(void **)((u8 *)state + 0x48));

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
        callbackTable = &gMainObjTimerCallbacks;
        callbackArgs = entity + 0x18;
        _call_via_r2(callbackArgs, entity + 0x22, *callbackTable);
        {
            u8 *entry;
            entry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(entry + 0x19) = *(u8 *)(entry + 0x19) + 1;
        }
        entryOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        callbackArgs += entryOffset;
        callbackIndex = *callbackArgs;
        _call_via_r1((s32)arg0, *(s32 *)((u32)(callbackIndex * 4) + *(u32 *)(entity + 0x14)));
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
        _call_via_r1((s32)arg0, *(s32 *)((u32)(callbackIndex * 4) + *(u32 *)(entity + 0x14)));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    }

    if (updateMotionState(*(void **)(entity + 0x28), obj, state) != 0) {
        clearMotionSpriteOverride(state, *(void **)((u8 *)state + 0x28));
        clearMotionSpriteOverride(state, *(void **)((u8 *)state + 0x48));
    }
    syncSpriteToWorldPosition(arg0, obj);
}
