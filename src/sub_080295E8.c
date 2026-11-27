void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, s32, s32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

extern u32 sScriptStepCallbacks;

/* Scripted-effect update: filter the effect/main-object pair through the
 * interaction check, apply contact and position handling, optionally run the
 * kind-specific effect with its sound cue, then advance the effect's script
 * program through the per-kind jump table unless the script asks to hold. */
void sub_080295E8(void *self) {
    void *mainObj;
    void *state;
    void *state34;
    u8 *scriptPtr;
    u8 *base;
    u8 scriptByte;
    u32 jumpTable;
    s32 funcptr;
    s32 idx;
    u32 *p1, *p2;

    mainObj = *(void **)((u8 *)self + 0x38);
    state = *(void **)((u8 *)self + 0x3C);
    state34 = (u8 *)state + 0x34;
    if (checkActorViewBounds(mainObj, state) == 1) {
        return;
    }
    applySpritePaletteVariant(self, mainObj);
    if (sub_08013558(mainObj, state, *(void **)((u8 *)state + 0x28)) != 0) {
        spawnContactEffectOnHit(self, *(void **)((u8 *)state + 0x28));
        if (!(*(u16 *)state & 0x0D)) {
            if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 2) {
                *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
                p1 = &sScriptStepCallbacks;
                sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 2, *p1);
            }
        }
    }
    uploadPendingSpriteGraphic(self, *(void **)((u8 *)state + 0x28));
    if (*(u16 *)state & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 3) {
            updateActorWorldPosition(self);
            *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
            p2 = &sScriptStepCallbacks;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 3, *p2);
        }
    }
    if (updateObjectDisplayState(mainObj, state) == 0) {
        *(u32 *)((u8 *)self + 0x14) = 0x0866DA4C;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        base = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        idx = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
        scriptPtr = (u8 *)self;
        scriptPtr += 0x18;
        scriptPtr += idx;
        scriptByte = *scriptPtr;
        jumpTable = *(u32 *)((u8 *)self + 0x14);
        funcptr = *(s32 *)((u32)(scriptByte * 4) + jumpTable);
        sub_080C31E0((s32)self, funcptr);
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
        if (*(u16 *)((u8 *)self + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(mainObj, state34);
        sub_08011EE8(state, 0x16C1, 0);
    }
    sub_08013C8C(self, mainObj);
}
