extern u8 gMainWorkspace[];
extern s32 stepDelayTimer(s32, void *);
extern s32 sub_0806D450(void *, void *, void *);
extern s32 sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/*
 * Handles position mode for an entity: defers to the callback when a mode is
 * active, otherwise runs a countdown that resets its movement on expiry, then
 * fires the effect and finishes the callback for certain global states.
 */
void sub_0807ABFC(u8 *arg0) {
    u8 *subObj = *(u8 **)(arg0 + 0x6C);
    u8 *obj = subObj + 4;
    void *ctx = *(void **)(arg0 + 0x38);
    if (sub_0806D450(arg0, ctx, obj) > 0) {
        sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        return;
    }
    {
        u8 *globalState = gMainWorkspace;
        s32 countdown;
        *(u16 *)ctx = *(u16 *)(globalState + 0x18C2);
        countdown = *(s32 *)(obj + 0x10) - 1;
        *(s32 *)(obj + 0x10) = countdown;
        if (countdown == 0) {
            countdown = 0xFFFF8000;
            *(s32 *)(obj + 0x08) = countdown;
            *(s32 *)(obj + 0x0C) = 0x40000;
            *(u8 *)(*(u8 **)(obj + 0x2C) + 1) = 1 & *(u8 *)(globalState + 0x1510);
            *(u8 *)(arg0 + (*(s16 *)(arg0 + 0x22)) * 2 + 0x19) = 0;
            {
                const u32 *effectIds = (const u32 *)0x08671BB0;
                sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *effectIds);
            }
        }
        stepDelayTimer((s32)subObj + 0x20, ctx);
        sub_0806D588(ctx, obj);
        if (*(u8 *)(globalState + 0x173A) == 0x1C || (*(u8 *)(globalState + 0x14ED) == 0 && *(s32 *)(globalState + 0x10) != 0)) {
            sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        }
    }
}
