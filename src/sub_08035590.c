extern void applySpritePaletteVariant(void *, void *);
extern void sub_08035DB4(void *, void *, void *);
extern s32 checkActorViewBounds(void *, void *);
extern s32 sub_08013558(void *, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void updateActorWorldPosition(void *);
extern void sub_0803B1A4(void *);
extern void sub_0803B1B4(void *, void *);
extern void sub_0803B1F4(void *, void *, void *);
extern s32 updateObjectDisplayState(void *, void *);
extern void syncSpriteToWorldPosition(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* byte at task + stepOffset + 0x19: the sub-state of the current step */
struct SubState { u8 _0[0x19]; u8 state; };

/*
 * Runs one frame of a scripted task: syncs the actor/subject pair, handles a
 * hit, and dispatches the handler selected by the current step from the
 * function table at task+0x14 (or the end handler when the subject is done).
 */
void sub_08035590(void *task) {
    u8 *self = (u8 *)task;
    u8 *actor = *(u8 **)(self + 0x38);
    u8 *subject = *(u8 **)(self + 0x3C);
    u8 *stateData;

    applySpritePaletteVariant(task, actor);
    sub_08035DB4(task, subject, actor);
    if (checkActorViewBounds(actor, subject) == 1) return;
    if (sub_08013558(actor, subject, *(void **)(subject + 0x28)) != 0)
        spawnContactEffectOnHit(task, *(void **)(subject + 0x28));
    stateData = subject + 0x54;
    sub_0803B1F4(task, subject, stateData);
    if (*(u16 *)subject & 1) {
        updateActorWorldPosition(self);
        sub_0803B1A4(stateData);
        {
            s32 stepOffset;
            u8 *stateEntry;
            s32 *endCallbacks;
            u8 handlerIndex;

            stepOffset = *(s16 *)(self + 0x22) * 2;
            *(u8 *)((u32)stepOffset + (u32)self + 0x19) = 0;
            endCallbacks = (s32 *)0x08671BB0;
            stateEntry = self;
            stateEntry += 0x18;
            sub_080C31E4(stateEntry, self + 0x22, *endCallbacks);
            stepOffset = *(s16 *)(self + 0x22) * 2;
            *(u8 *)((u32)stepOffset + (u32)self + 0x19) = *(u8 *)((u32)stepOffset + (u32)self + 0x19) + 1;
            stepOffset = *(s16 *)(self + 0x22) * 2;
            stateEntry += stepOffset;
            handlerIndex = *(u8 *)stateEntry;
            sub_080C31E0(self, *(void **)(handlerIndex * 4 + *(u32 *)(self + 0x14)));
        }
        return;
    }
    if (updateObjectDisplayState(actor, subject) == 0) {
        s32 stepOffset;
        u8 *stateEntry;
        u8 handlerIndex;
        *(u32 *)(self + 0x14) = 0x0866DDB4;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        stepOffset = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)stepOffset + (u32)self + 0x19) = *(u8 *)((u32)stepOffset + (u32)self + 0x19) + 1;
        stepOffset = *(s16 *)(self + 0x22) * 2;
        stateEntry = self;
        stateEntry += 0x18;
        stateEntry += stepOffset;
        handlerIndex = *(u8 *)stateEntry;
        sub_080C31E0(self, *(void **)(handlerIndex * 4 + *(u32 *)(self + 0x14)));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    } else {
        sub_0803B1B4(subject, stateData);
    }
    syncSpriteToWorldPosition(self, actor);
}
