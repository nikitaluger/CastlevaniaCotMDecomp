void stepAnimationTrack(void *, void *);
void moveObjectHorizontally(void *, u32, u32);
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

/* Scripted-effect update with an owner object: clear the effect's 0x48 timer
 * on a filtered interaction, handle contact and the kind-specific cue, then
 * advance the script program and give the owner a velocity kick unless the
 * owner's 0x06 flags say no. */
void sub_0802C190(void *self) {
    void *mainObj;
    void *state;
    void *state34;
    void *state48;
    void *owner;
    u8 *scriptPtr;
    u32 *p;
    u8 *base;
    u8 scriptByte;
    u32 jumpTable;
    s32 funcptr;
    s32 idx;

    mainObj = *(void **)((u8 *)self + 0x38);
    owner = *(void **)((u8 *)self + 0xAC);
    state = *(void **)((u8 *)self + 0x3C);
    state34 = (u8 *)state + 0x34;
    state48 = (u8 *)state + 0x48;
    if (checkActorViewBounds(mainObj, state) == 1) {
        *(u16 *)state48 = 0;
        return;
    }
    applySpritePaletteVariant(self, mainObj);
    if (sub_08013558(mainObj, state, *(void **)((u8 *)state + 0x28)) != 0)
        spawnContactEffectOnHit(self, *(void **)((u8 *)state + 0x28));
    uploadPendingSpriteGraphic(self, *(void **)((u8 *)state + 0x28));
    if (*(u16 *)state & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 2) {
            updateActorWorldPosition(self);
            *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
            p = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 2, *p);
        }
    }
    if (updateObjectDisplayState(mainObj, state) == 0) {
        *(u32 *)((u8 *)self + 0x14) = 0x0866DB34;
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
        if (!(*(u16 *)(*(u8 **)((u8 *)owner + 0x04) + 0x06) & 0x10)) {
            moveObjectHorizontally(state, 0x80000, 0x80000);
        }
    }
    sub_08013C8C(self, mainObj);
}
