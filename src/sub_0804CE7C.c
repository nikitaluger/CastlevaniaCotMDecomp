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

extern u32 gScriptStepCallbackTable;

/* Advance one step of an entity's script: refresh its component state, run the
 * script callback for the current step, then apply the position correction. */
void sub_0804CE7C(void *entity) {
    void *state;
    void *comp;
    s32 handler;
    u8 *self = (u8*)entity;

    state = *(void **)(self + 0x38);
    comp = *(void **)(self + 0x3C);
    applySpritePaletteVariant(self, state);
    if (checkActorViewBounds(state, comp) == 1)
        return;

    if (sub_08013558(state, comp, *(void **)((u8 *)comp + 0x28)) != 0)
        spawnContactEffectOnHit(self, *(void **)((u8 *)comp + 0x28));
    uploadPendingSpriteGraphic(self, *(void **)((u8 *)comp + 0x28));

    if (*(u16 *)comp & 1) {
        u32 *hookSlot;
        u8 *script;
        u8 opcode;
        s32 stepOff;
        updateActorWorldPosition(self);
        {
            u8 *counterPtr;
            counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(counterPtr + 0x19) = 0;
        }
        hookSlot = (u32 *)0x08671BB0;
        script = (u8 *)entity + 0x18;
        sub_080C31E4(script, (u8 *)entity + 0x22, *hookSlot);
        {
            u8 *counterPtr;
            counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(counterPtr + 0x19) = *(u8 *)(counterPtr + 0x19) + 1;
        }
        stepOff = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        script += stepOff;
        opcode = *script;
        handler = *(s32 *)((u32)(opcode * 4) + *(u32 *)((u8 *)entity + 0x14));
        sub_080C31E0((s32)entity, handler);
        return;
    }

    if (updateObjectDisplayState(state, comp) == 0) {
        u8 *script;
        u8 opcode;
        s32 stepOff;
        *(u32 *)((u8 *)entity + 0x14) = 0x0866E4E4;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        {
            u8 *counterPtr;
            counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(counterPtr + 0x19) = *(u8 *)(counterPtr + 0x19) + 1;
        }
        stepOff = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        script = (u8 *)entity;
        script += 0x18;
        script += stepOff;
        opcode = *script;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(opcode * 4) + *(u32 *)((u8 *)entity + 0x14)));
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    }
    sub_08013C8C(entity, state);
}
