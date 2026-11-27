extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_08013AC4(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void sub_08013C5C(void *, s32);
extern void sub_08013C8C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern void sub_080142C0(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;

/* Runs one tick of a scripted entity: refreshes its owner/target state, does a
 * one-time action when flagged, then dispatches the current script step. */
void sub_08028E94(u8 *self) {
    s32 owner = *(s32 *)(self + 0x38);
    u8 *params = *(u8 **)(self + 0x3C);
    u8 *animState = params + 0x34;

    if (sub_080141AC(owner, params) == 1) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }
    sub_08013C5C(self, owner);
    if (sub_08013558(owner, params, *(void **)(params + 0x28)) != 0) {
        sub_08013978(self, *(void **)(params + 0x28));
    }
    sub_080142C0(self, *(void **)(params + 0x28));
    if (*(u16 *)params & 1) {
        u8 *stepCheck = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(stepCheck + 0x1A) != 2) {
            sub_08013AC4(self);
            {
                u8 *q = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
                u8 zero = 0;
                *(u8 *)(q + 0x1B) = zero;
                { void **actionTable = &sScriptStepCallbacks;
                  sub_080C31E8(self + 0x18, self + 0x22, 2, *actionTable); }
            }
        }
    }
    if (updateObjectDisplayState(owner, params) == 0) {
        *(void **)(self + 0x14) = (void *)0x0866DA30;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        {
            u8 *q = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            q[0x19] = (u8)(q[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)(self + 0x22)) * 2;
            u8 *stepBase = self + 0x18;
            u8 stepId = *(stepBase + stepOffset);
            void **callbackTable = *(void **)(self + 0x14);
            void *callback = callbackTable[stepId];
            sub_080C31E0(self, callback);
        }
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
        if (*(u16 *)(self + 0x02) & 0x8000) {
            return;
        }
        stepAnimationTrack(owner, animState);
        advanceMotion(params, 0);
    }
    sub_08013C8C(self, owner);
}
