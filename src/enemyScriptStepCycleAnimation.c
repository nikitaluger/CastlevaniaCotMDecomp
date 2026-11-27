extern s32 nextRandomWord(void);
extern void playSound(u16);
extern void forceAnimationFrame(s32, u8 *, s32, s32);
extern void setObjectAnimation(s32, u8 *, s32, s32);
extern void advanceAnimTrack(s32, u8 *);
extern void setSpriteFacingToTarget(s32, s32);
extern void sub_0809A610(void *);
extern void setEffectBehavior(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gMenuScriptCallback;
extern u32 gScriptStepCallbacks;
extern u32 gMainObjTimerCallbacks;

/* Enemy script-step handler: run the shared enemy pre-update, advance the
 * animation track, and while its flag bit 0x2 is set use a tick counter to
 * choose between re-dispatching the script through the menu/script/timer
 * callback tables, forcing an animation frame and facing the target, or
 * restarting the animation with an effect, sound and timer callback. */
void enemyScriptStepCycleAnimation(void *scriptThread)
{
    s32 sprite;
    int stepScale;
    u8 *animTrack;
    s32 *worldXPtr;
    u8 *work;
    u8 *stepState;
    s32 tick;
    s32 zero;
    s16 stepIndex;
    u8 *self;
    u8 *stepByte;
    u8 *tickPtr;
    u32 *callbackTable;

    sprite = *((s32 *) (((u8 *) scriptThread) + 0x38));
    work = *((u8 **) (((u8 *) scriptThread) + 0x3C));
 do { animTrack = work + 0x34; } while (0);
    stepState = work + 0x48;
    sub_0809A610(scriptThread);
    advanceAnimTrack(sprite, animTrack);
    if ((*animTrack) & 2)
    {
        tickPtr = work + 0x6A;
        tick = (*((u8 *) tickPtr)) + 1;
        zero = 0;
        worldXPtr = (s32 *) (work + 8);
        *((u8 *) tickPtr) = tick;
        if ((tick & 0xF) == 2)
        {
            if (tick & 0x80)
            {
                stepIndex = *((s16 *) (((u8 *) scriptThread) + 0x22));
                stepByte = (u8 *) ((stepIndex * 2) + ((u32) scriptThread));
                stepByte[0x17] = zero;
                callbackTable = &gMenuScriptCallback;
                sub_080C31E8(((u8 *) scriptThread) + 0x18, ((u8 *) scriptThread) + 0x22, 3, *callbackTable);
            }
            else
            {
                setObjectAnimation(sprite, animTrack, 0xF, zero);
                setEffectBehavior(*((s32 *) (stepState + 8)), zero);
                stepScale = 2;
                stepIndex = *((s16 *) (((u8 *) scriptThread) + 0x22));
                stepByte = (u8 *) (((u32) (stepIndex * stepScale)) + ((u32) scriptThread));
                stepByte[0x19] = zero;
                callbackTable = &gScriptStepCallbacks;
                sub_080C31E8((self = (u8 *) scriptThread) + 0x18, ((u8 *) scriptThread) + 0x22, 4, *callbackTable);
            }
        }
        else
            if ((nextRandomWord() & 3) == 0)
            {
                forceAnimationFrame(sprite, animTrack, zero, zero);
                setSpriteFacingToTarget(sprite, *worldXPtr);
            }
            else
            {
                setObjectAnimation(sprite, animTrack, 0xF, zero);
                setSpriteFacingToTarget(sprite, *((s32 *) (work + 8)));
                *((u8 *) (work + 0x69)) = zero;
                setEffectBehavior(*((s32 *) (stepState + 8)), zero);
                playSound(0x165);
                stepIndex = *((s16 *) (((u8 *) scriptThread) + 0x22));
                stepByte = (u8 *) (((u32) (stepIndex * 2)) + ((u32) scriptThread));
                stepByte[0x19] = zero;
                callbackTable = &gMainObjTimerCallbacks;
                sub_080C31E4(((u8 *) scriptThread) + 0x18, ((u8 *) scriptThread) + 0x22, *callbackTable);
            }
    }
}
