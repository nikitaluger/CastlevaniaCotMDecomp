/* Main update for a scripted companion entity: run the visibility/owner updates,
 * perform the one-time spawn action when flagged, then - if its logic allows -
 * dispatch the current script step's callback from the per-entity handler table
 * and refresh the animation and timers. */
void sub_08005E80(u32);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, u32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
s32 checkActorViewBounds(void *, void *);   /* visibility/validity check */
void uploadPendingSpriteGraphic(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

static inline u8 zero8(void) { return 0; }
static inline u16 zero16(void) { return 0; }

void sub_08028074(void *self) {
    void *owner;
    void *params;
    void *animState;
    u8 *timers;
    u8 *stepBase;
    u32 *actionTable;
    u8 *stepPtr;
    u8 stepId;
    u32 callbackTable;
    s32 callback;
    s32 stepOffset;
    u8 zeroByte;
    u16 zeroHalf;

    owner = *(void **)((u8 *)self + 0x38);
    params = *(void **)((u8 *)self + 0x3C);
    animState = (u8 *)params + 0x34;
    timers = (u8 *)params + 0x48;
    if (checkActorViewBounds(owner, params) == 1) {
        return;
    }
    applySpritePaletteVariant(self, owner);
    if (sub_08013558(owner, params, *(void **)((u8 *)params + 0x28)) != 0)
        spawnContactEffectOnHit(self, *(void **)((u8 *)params + 0x28));
    uploadPendingSpriteGraphic(self, *(void **)((u8 *)params + 0x28));
    if (*(u16 *)params & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 3) {
            *(u32 *)((u8 *)timers + 0x18) = 0xB60;
            updateActorWorldPosition(self);
            sub_08005E80(0x8D);
            zeroHalf = zero16();
            zeroByte = zero8();
            *(u16 *)((u8 *)timers + 0x12) = zeroHalf;
            *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = zeroByte;
            actionTable = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 3, *actionTable);
        }
    }
    if (updateObjectDisplayState(owner, params) == 0) {
        *(u32 *)((u8 *)self + 0x14) = 0x0866DA00;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        stepBase = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        *(u8 *)(stepBase + 0x19) = *(u8 *)(stepBase + 0x19) + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
        stepPtr = (u8 *)self;
        stepPtr += 0x18;
        stepPtr += stepOffset;
        stepId = *stepPtr;
        callbackTable = *(u32 *)((u8 *)self + 0x14);
        callback = *(s32 *)((u32)(stepId * 4) + callbackTable);
        sub_080C31E0((s32)self, callback);
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
        if (*(u16 *)((u8 *)self + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(owner, animState);
        advanceMotion(params, *(u32 *)((u8 *)timers + 0x18));
    }
    sub_08013C8C(self, owner);
}
