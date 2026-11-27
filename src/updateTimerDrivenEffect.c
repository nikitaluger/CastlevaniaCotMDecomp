extern s32 scaleByRandom(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern void updateFacingFlipTimer(s32, void *, void *, s32, s32);
extern void _call_via_r3(void *, void *, s32, s32);
struct EffectStepTimers { u8 _0[2]; u16 timer2; u16 timer4; };
struct EffectStepTimersSigned { u8 _0[4]; s16 timer4; };
struct S_02025FF0 { u8 _0[0x174C]; s32 targetX; };
extern struct S_02025FF0 gMainWorkspace;

/* Script step for a timer-driven effect: advance the facing and animation
 * timers, end the step at the focus target, otherwise reverse X velocity and
 * reload the motion timer (short near the target, long far from it). */
void updateTimerDrivenEffect(u8 *object) {
    s32 sprite = *(s32 *)(object + 0x38);
    u8 *state = *(u8 **)(object + 0x3C);
    u8 *animTrack = state + 0x34;
    u8 *timers = state + 0x48;
    s32 farFromTarget, useLongDelay, toTargetX, signedTimer;
    s32 timer4, timer2, newTimer;

    updateFacingFlipTimer(sprite, state, timers, 0x5A, 0x78);
    setAnimationFrame(sprite, animTrack, 0, 1);

    timer4 = ((struct EffectStepTimers *)timers)->timer4 - 1;
    ((struct EffectStepTimers *)timers)->timer4 = timer4;
    if ((timer4 << 0x10) <= 0) {
        ((struct EffectStepTimers *)timers)->timer4 = (u16)(scaleByRandom(0x3D) + 0x5A);
        if (absXFromFocus(*(s32 *)(state + 8)) <= 0x600000 &&
            absYFromFocus(*(s32 *)(state + 0xC)) <= 0x600000) {
            u8 *scriptStep = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
            s32 *stepCallback;
            *(u8 *)(scriptStep + 0x19) = 0;
            stepCallback = (s32 *)SCRIPT_STEP_CALLBACK_TABLE;
            _call_via_r3(object + 0x18, object + 0x22, 1, *stepCallback);
            return;
        }
        signedTimer = ((struct EffectStepTimersSigned *)timers)->timer4;
        if (signedTimer < 0) signedTimer += 3;
        ((struct EffectStepTimers *)timers)->timer4 = (u16)(signedTimer >> 2);
    }
    if (*(u16 *)(state + 2) & 2) {
        *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
        ((struct EffectStepTimers *)timers)->timer2 = (u16)(scaleByRandom(0x15) + 0x3C);
    }
    timer2 = ((struct EffectStepTimers *)timers)->timer2 - 1;
    ((struct EffectStepTimers *)timers)->timer2 = timer2;
    if ((timer2 << 0x10) > 0) return;

    useLongDelay = 0;
    farFromTarget = 0;
    if (absXFromFocus(*(s32 *)(state + 8)) > 0x400000) {
        farFromTarget = 1;
    }
    toTargetX = gMainWorkspace.targetX - *(s32 *)(state + 8);
    if ((toTargetX < 0 && *(s32 *)(state + 0x10) < 0) || (toTargetX > 0 && *(s32 *)(state + 0x10) > 0)) {
        if (farFromTarget != 0) goto check5;
        goto set15;
    }
    if (farFromTarget == 1) useLongDelay = 1;
check5:
    if (useLongDelay != 0) goto set15;
    newTimer = scaleByRandom(0x0B) + 0x14;
    goto store;
set15:
    newTimer = scaleByRandom(0x15) + 0x3C;
store:
    ((struct EffectStepTimers *)timers)->timer2 = newTimer;
    *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
}
