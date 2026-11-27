extern s32 sub_080141AC(void *, void *);
extern void sub_08013C5C(void *, void *);
extern s32 sub_08013558(void *, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern s32 updateObjectDisplayState(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;
extern void sub_08013C8C(void *, void *);
extern void sub_080547E0(void *, void *);
extern void sub_08054864(void *, void *, s32);
extern void advanceMotion(void *, s32);

/* Scripted enemy update with an accumulating per-frame counter: run hit/damage
 * helpers, advance and dispatch the script, then accumulate the counter and
 * apply the extra movement/status updates before syncing the position. */
void sub_080542A8(u8 *arg0) {
    void *owner = *(void **)(arg0 + 0x38);
    u8 *comp = *(u8 **)(arg0 + 0x3C);
    u8 *status = comp + 0x34;
    u8 *counter = comp + 0x48;
    s32 counterValue;
    if (sub_080141AC(owner, comp) == 1) {
        return;
    }
    sub_08013C5C(arg0, owner);
    if (sub_08013558(owner, comp, *(void **)(comp + 0x28)) != 0) {
        sub_08013978(arg0, *(void **)(comp + 0x28));
    }
    sub_080142C0(arg0, *(void **)(comp + 0x28));
    if (*(u16 *)comp & 1) {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        if (stepSlot[0x1A] != 5) {
            sub_08013AC4(arg0);
            {
                u8 *step = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
                step[0x1B] = 0;
                { void **audioCmd = &sScriptStepCallbacks;
                  sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 5, *audioCmd); }
            }
        }
    }
    if (updateObjectDisplayState(owner, comp) == 0) {
        *(void **)(arg0 + 0x14) = (void *)0x0866E6F4;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        {
            u8 *step = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            step[0x19] = (u8)(step[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)(arg0 + 0x22)) * 2;
            u8 *scriptData = arg0 + 0x18;
            u8 handlerId = *(scriptData + stepOffset);
            void **handlers = *(void **)(arg0 + 0x14);
            void *handler = handlers[handlerId];
            sub_080C31E0(arg0, handler);
        }
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
        if (*(u16 *)(arg0 + 0x02) & 0x8000) {
            return;
        }
        *(u16 *)counter = (u16)(*(u16 *)counter + *(u16 *)(counter + 0x02));
        counterValue = *(s16 *)counter;
        sub_08054864(owner, status, counterValue);
        advanceMotion(comp, 0);
    }
    sub_080547E0(owner, comp);
    sub_08013C8C(arg0, owner);
}
