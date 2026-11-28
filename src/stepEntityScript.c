void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
void sub_08097F88(s32, void *, void *, void *);
void sub_08007E24(s32);
void sub_08098338(s32, void *);

extern u32 gMainObjTimerCallbacks;
extern u32 gEntityScriptHandlers;

/* Refresh an entity's graphics state, then dispatch the current script
 * command (or its early-exit path) and finish the step. */
/* Refresh a scripted entity's sprite attributes, effects and queued graphics, then dispatch its current script command (or the finish-state path) and end with the palette copy. */ void stepEntityScript(void *obj) {
    void *entity;
    void *state;
    void *stateField48;
    s32 scriptFunc;
    s32 zero = 0;
    u16 packedValue;
    u8 *self = (u8 *)obj;

    entity = *(void **)(self + 0x38);
    state = *(void **)(self + 0x3C);
    stateField48 = (u8 *)state + 0x48;

    packedValue = (*(u16 *)entity & 0xFFF) | ((*(u16 *)((u8 *)state + 0x22) + 8) << 12);
    *(u16 *)entity = packedValue | zero;
    sub_08097F88(0, entity, state, *(void **)((u8 *)state + 0x28));
    sub_08097F88(2, entity, state, *(void **)((u8 *)stateField48 + 4));
    uploadPendingSpriteGraphic(obj, *(void **)((u8 *)state + 0x28));
    uploadPendingSpriteGraphic(obj, *(void **)((u8 *)stateField48 + 4));

    if (*(u16 *)state & 1) {
        u32 *callbackTable;
        u8 *scriptPtr;
        u8 scriptByte;
        s32 scriptOffset;
        updateActorWorldPosition(obj);
        sub_08007E24(0xBB);
        *(u8 *)((u8 *)*(u32 **)((u8 *)state + 0x28) + 1) = zero;
        *(u8 *)((u8 *)*(u32 **)((u8 *)stateField48 + 4) + 1) = zero;
        {
            u8 *scriptBase;
            scriptBase = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(scriptBase + 0x19) = zero;
        }
        callbackTable = (u32 *)0x08671BB0;
        scriptPtr = self + 0x18;
        sub_080C31E4(scriptPtr, self + 0x22, *callbackTable);
        {
            u8 *scriptBase;
            scriptBase = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(scriptBase + 0x19) = *(u8 *)(scriptBase + 0x19) + 1;
        }
        scriptOffset = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
        scriptPtr += scriptOffset;
        scriptByte = *scriptPtr;
        scriptFunc = *(s32 *)((u32)(scriptByte * 4) + *(u32 *)(self + 0x14));
        sub_080C31E0((s32)obj, scriptFunc);
        return;
    }

    if (updateObjectDisplayState(entity, state) == 0) {
        u8 *scriptPtr;
        u8 scriptByte;
        s32 scriptOffset;
        *(u32 *)(self + 0x14) = (u32)&gEntityScriptHandlers;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        {
            u8 *scriptBase;
            scriptBase = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(scriptBase + 0x19) = *(u8 *)(scriptBase + 0x19) + 1;
        }
        scriptOffset = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
        scriptPtr = self;
        scriptPtr += 0x18;
        scriptPtr += scriptOffset;
        scriptByte = *scriptPtr;
        scriptFunc = *(s32 *)((u32)(scriptByte * 4) + *(u32 *)(self + 0x14));
        sub_080C31E0((s32)obj, scriptFunc);
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
    sub_08098338(1, entity);
    sub_08013C8C(obj, entity);
}
