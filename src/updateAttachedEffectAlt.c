void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 _call_via_r1(s32, s32);
void _call_via_r2(void *, void *, u32);

extern u32 gMainObjTimerCallbacks;

/* Update an effect attached to an owner: filter it against the camera view,
 * resolve contact and pending sprite graphics, then either run the hit script
 * step or copy the work coordinates back into the owner. */
void updateAttachedEffectAlt(void *entity) {
    void *mainObj;
    void *state;
    s32 handler;
    u8 *self = (u8*)entity;
    u8 zero;
    u32 owner1, owner2;

    mainObj = *(void **)(self + 0x38);
    state = *(void **)(self + 0x3C);
    applySpritePaletteVariant(self, mainObj);
    *(u8 *)(*(u8 **)(self + 0x30) + 0x80) = (zero = 0);
    if (checkActorViewBounds(mainObj, state) == 1)
        return;

    if (detectActorHit(mainObj, state, *(void **)((u8 *)state + 0x28)) != 0)
        spawnContactEffectOnHit(self, *(void **)((u8 *)state + 0x28));
    uploadPendingSpriteGraphic(self, *(void **)((u8 *)state + 0x28));

    if (*(u16 *)state & 1) {
        u32 *cueTable;
        u8 *scriptPtr;
        u8 scriptByte;
        s32 idx;
        updateActorWorldPosition(self);
        *(u8 *)(*(u8 **)(self + 0x30) + 0x7C) = 1;
        {
            u8 *parent = *(u8 **)(self + 0x30);
            parent = *(u8 **)(parent + 0x2C);
            if (parent) *(u8 *)(parent + 0x84) = 1;
        }
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = zero;
        }
        cueTable = &gMainObjTimerCallbacks;
        scriptPtr = (u8 *)entity + 0x18;
        _call_via_r2(scriptPtr, (u8 *)entity + 0x22, *cueTable);
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        idx = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        scriptPtr += idx;
        scriptByte = *scriptPtr;
        handler = *(s32 *)((u32)(scriptByte * 4) + *(u32 *)((u8 *)entity + 0x14));
        _call_via_r1((s32)entity, handler);
        return;
    }

    if (updateObjectDisplayState(mainObj, state) == 0) {
        u8 *scriptPtr;
        u8 scriptByte;
        s32 idx;
        *(u32 *)((u8 *)entity + 0x14) = ATTACHED_EFFECT_ALT_STEP_TABLE;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        idx = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        scriptPtr = (u8 *)entity;
        scriptPtr += 0x18;
        scriptPtr += idx;
        scriptByte = *scriptPtr;
        _call_via_r1((s32)entity, *(s32 *)((u32)(scriptByte * 4) + *(u32 *)((u8 *)entity + 0x14)));
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    }
    owner1 = *(vu32 *)((u8 *)entity + 0x30);
    *(s32 *)(owner1 + 0x5C) = *(s32 *)((u8 *)state + 0x08);
    owner2 = *(vu32 *)((u8 *)entity + 0x30);
    *(s32 *)(owner2 + 0x6C) = *(s32 *)((u8 *)state + 0x0C);
    syncSpriteToWorldPosition(entity, mainObj);
}
