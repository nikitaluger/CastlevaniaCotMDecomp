extern void sub_0808DC40(s32, s32, s32);
extern void sub_080A860C(void *, void *);
extern void decelerateTargetX(u16 *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *D_08671BC0;
extern void *gMainObjTimerCallbacks;

/* Refresh an actor's sprite attributes, tracker angle and speed from its AI
 * step flags, spawn an effect when flagged, then advance its script step from
 * one of two data tables once the actor is idle. */
void sub_080A7D40(void *arg0) {
    u16 *attributes;
    u8 *actor;
    u8 *ai;
    s16 stepIndex;
    s32 stepOffset;

    attributes = *(u16 **)((u8 *)arg0 + 0x38);
    actor = *(u8 **)((u8 *)arg0 + 0x3C);
    ai = actor + 0x48;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepOffset = stepIndex;
    stepOffset <<= 1;
    stepOffset += (u32)arg0;
    if (!(*(u8 *)((u8 *)stepOffset + 0x19) & 2)) {
        *attributes = (*attributes & 0x0FFF) | 0xE000;
    }

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepOffset = stepIndex;
    stepOffset <<= 1;
    stepOffset += (u32)arg0;
    if (!(*(u8 *)((u8 *)stepOffset + 0x19) & 7)) {
        sub_0808DC40(*(s32 *)(actor + 8), *(s32 *)(actor + 0xC), 8);
    }

    sub_080A860C(arg0, ai);
    decelerateTargetX(attributes, ai);

    if (*(u8 *)(actor + 0x120)) {
        if (*(s32 *)(actor + 0x110) == 0) {
            s32 counter;
            counter = *(u8 *)(actor + 0x158) + 1;
            *(u8 *)(actor + 0x158) = counter;
            if ((u8)counter <= 1) {
                stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
                *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) = 0;
                {
                    void **scriptTable = &D_08671BC0;
                    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
                }
            } else {
                stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
                *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) = 0;
                {
                    void **scriptTable = &gMainObjTimerCallbacks;
                    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
                }
            }
        }
    }
}
