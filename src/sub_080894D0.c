extern void startEffectTimer(void *a, s32 b, void *c);
extern void stepDelayTimer(void *a, void *b);
extern void sub_0806D588(void *a);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);

extern u8 D_08506368[];
extern u8 D_08506444[];
extern u32 gMainObjTimerCallbacks;

/* Points the FX object at its sprite data, spawns an effect from the child, seeds
 * the child's movement values, updates the FX position, then advances the actor's
 * script step, posts a message and dispatches the next behavior handler. */
void sub_080894D0(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *child = *(u8 **)(self + 0x6C);
    u8 *childData = child + 4;
    u8 *fx = *(u8 **)(self + 0x38);
    u8 *fxPos;

    *(void **)(fx + 0x24) = D_08506368;
    fxPos = child + 0x20;
    startEffectTimer(fxPos, 0, D_08506444);
    stepDelayTimer(fxPos, fx);
    *(u32 *)(child + 4) = 0xFFF00000;
    *(u32 *)(childData + 4) = 0x7F0000;
    *(u32 *)(childData + 8) = 0x20000;
    sub_0806D588(fx);

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        u32 *msgPtr = &gMainObjTimerCallbacks;
        u8 *step = self + 0x18;
        sub_080C31E4(step, self + 0x22, (void *)*msgPtr);
        {
            s16 stepIdx = *(s16 *)(self + 0x22);
            (*(u8 *)(stepIdx * 2 + self + 0x19))++;
            stepIdx = *(s16 *)(self + 0x22);
            step += stepIdx * 2;
            {
                u8 handler = *step;
                void **handlerTable = *(void ***)(self + 0x14);
                sub_080C31E0(self, handlerTable[handler]);
            }
        }
    }
}
