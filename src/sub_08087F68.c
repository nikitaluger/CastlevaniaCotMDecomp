extern void startEffectTimer(s32, s32, s32);
extern void stepDelayTimer(s32, s32);
extern void sub_0806D588(void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern s32 gMainObjTimerCallbacks[];

/* Configures an FX object and its child entity for a scripted effect (sprite pointer,
 * effect spawn, movement seeds, position update), then advances the actor's script
 * step, posts a message and dispatches the next behavior handler. */
void sub_08087F68(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *child = *(u8 **)(self + 0x6C);
    u8 *childData = child + 4;
    u8 *fx = *(u8 **)(self + 0x38);
    *(s32 *)(fx + 0x24) = 0x08506368;
    startEffectTimer((s32)(child + 0x20), 0, (s32)0x085063F0);
    stepDelayTimer((s32)(child + 0x20), (s32)fx);
    *(s32 *)(child + 4) = 0xFFD80000;
    *(s32 *)(childData + 4) = 0xFE << 15;
    *(s32 *)(childData + 8) = 0x80 << 10;
    sub_0806D588(fx);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *msgPtr = gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *msgPtr);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *step = self + 0x18;
        s16 stepIdx = *(s16 *)(self + 0x22);
        step += stepIdx * 2;
        sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *step * 4));
    }
}
