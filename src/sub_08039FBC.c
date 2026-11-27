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

extern u32 gMainObjTimerCallbacks;

/* Owner-linked effect update: filter the interaction, apply contact handling,
 * raise the owner's hit flags, play the kind-specific cue and either dispatch a
 * script step or copy the state coordinates back into the owner. */
void sub_08039FBC(void *entity) {
    void *mainObj;
    void *state;
    s32 funcptr;
    u8 *self = (u8*)entity;
    u8 zero;
    u32 owner1, owner2;

    mainObj = *(void **)(self + 0x38);
    state = *(void **)(self + 0x3C);
    applySpritePaletteVariant(self, mainObj);
    *(u8 *)(*(u8 **)(self + 0x30) + 0x80) = (zero = 0);
    if (checkActorViewBounds(mainObj, state) == 1)
        return;

    if (sub_08013558(mainObj, state, *(void **)((u8 *)state + 0x28)) != 0)
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
        cueTable = (u32 *)0x08671BB0;
        scriptPtr = (u8 *)entity + 0x18;
        sub_080C31E4(scriptPtr, (u8 *)entity + 0x22, *cueTable);
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        idx = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        scriptPtr += idx;
        scriptByte = *scriptPtr;
        funcptr = *(s32 *)((u32)(scriptByte * 4) + *(u32 *)((u8 *)entity + 0x14));
        sub_080C31E0((s32)entity, funcptr);
        return;
    }

    if (updateObjectDisplayState(mainObj, state) == 0) {
        u8 *scriptPtr;
        u8 scriptByte;
        s32 idx;
        *(u32 *)((u8 *)entity + 0x14) = 0x0866DF24;
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
        sub_080C31E0((s32)entity, *(s32 *)((u32)(scriptByte * 4) + *(u32 *)((u8 *)entity + 0x14)));
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    }
    owner1 = *(vu32 *)((u8 *)entity + 0x30);
    *(s32 *)(owner1 + 0x5C) = *(s32 *)((u8 *)state + 0x08);
    owner2 = *(vu32 *)((u8 *)entity + 0x30);
    *(s32 *)(owner2 + 0x6C) = *(s32 *)((u8 *)state + 0x0C);
    sub_08013C8C(entity, mainObj);
}
