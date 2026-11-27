/* Main update for a scripted companion entity: run the visibility/owner updates,
 * perform the one-time spawn action when flagged, then - if its logic allows -
 * dispatch the current script step's callback from the per-entity handler table
 * and refresh the animation/timer state. */
void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, u32, u32);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);   /* visibility/validity check */
void sub_080142C0(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

void sub_0803E830(void *self) {
    void *owner;
    void *params;
    void *animState;
    void *timers;
    u8 *stepBase;
    u32 *actionTable;
    u8 *stepPtr;
    u8 stepId;
    u32 callbackTable;
    s32 callback;
    s32 stepOffset;

    owner = *(void **)((u8 *)self + 0x38);
    params = *(void **)((u8 *)self + 0x3C);
    animState = (u8 *)params + 0x34;
    timers = (u8 *)params + 0x48;
    if (sub_080141AC(owner, params) == 1) {
        sub_080C31E0((s32)self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    sub_08013C5C(self, owner);
    if (sub_08013558(owner, params, *(void **)((u8 *)params + 0x28)) != 0)
        sub_08013978(self, *(void **)((u8 *)params + 0x28));
    sub_080142C0(self, *(void **)((u8 *)params + 0x28));
    if (*(u16 *)params & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 2) {
            sub_08013AC4(self);
            *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
            actionTable = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 2, *actionTable);
        }
    }
    if (updateObjectDisplayState(owner, params) == 0) {
        *(u32 *)((u8 *)self + 0x14) = 0x0866E04C;
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
        sub_08011EE8(params, *(u32 *)((u8 *)timers + 0x04), 0);
    }
    sub_08013C8C(self, owner);
}
