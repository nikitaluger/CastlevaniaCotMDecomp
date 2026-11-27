void stepAnimationTrack(void *, void *);
void advanceMotion(void *, u32);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

/* Runs one tick of a scripted entity: refreshes its owner/target state, does
 * a one-time action when flagged, then dispatches the current script step. */
void sub_0805C174(void *arg0)
{
    void *owner;
    void *actor;
    void *animState;
    u8 *stepState;
    u32 *actionTable;
    u8 *stepByte;
    u8 stepId;
    u32 scriptCallbacks;
    s32 callback;
    s32 stepOffset;

    owner = *(void **)((u8 *)arg0 + 0x38);
    actor = *(void **)((u8 *)arg0 + 0x3C);
    animState = (u8 *)actor + 0x34;
    if (sub_080141AC(owner, actor) == 1) {
        return;
    }
    sub_08013C5C(arg0, owner);
    if (sub_08013558(owner, actor, *(void **)((u8 *)actor + 0x28)) != 0)
        sub_08013978(arg0, *(void **)((u8 *)actor + 0x28));
    sub_080142C0(arg0, *(void **)((u8 *)actor + 0x28));
    if (*(u16 *)actor & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x1A) != 1) {
            sub_08013AC4(arg0);
            *(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x1B) = 0;
            actionTable = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, *actionTable);
        }
    }
    if (updateObjectDisplayState(owner, actor) == 0) {
        /* 0x0866E920 is this entity's script-step callback table. */
        *(u32 *)((u8 *)arg0 + 0x14) = 0x0866E920;
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
        stepState = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stepState + 0x19) = *(u8 *)(stepState + 0x19) + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        stepByte = (u8 *)arg0;
        stepByte += 0x18;
        stepByte += stepOffset;
        stepId = *stepByte;
        scriptCallbacks = *(u32 *)((u8 *)arg0 + 0x14);
        callback = *(s32 *)((u32)(stepId * 4) + scriptCallbacks);
        sub_080C31E0((s32)arg0, callback);
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
        if (*(u16 *)((u8 *)arg0 + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(owner, animState);
        advanceMotion(actor, 0);
    }
    sub_08013C8C(arg0, owner);
}
