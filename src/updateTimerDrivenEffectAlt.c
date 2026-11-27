extern s32 scaleByRandom(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *gScriptStepCallbacks;
struct P48u { u8 _0[2]; u16 timer2; u16 timer4; };
struct P48s { u8 _0[4]; s16 timer4; };
struct S_02025FF0 { u8 _0[0x174C]; s32 targetX; };
extern struct S_02025FF0 gMainWorkspace;

/* Timer-driven effect update: advance the facing and animation timers, return
   to the script when both coordinates are close to the target, and reverse the
   horizontal velocity when the effect moves away from it. */
void updateTimerDrivenEffectAlt(u8 *arg0) {
    s32 mainObj = *(s32 *)(arg0 + 0x38);
    u8 *state = *(u8 **)(arg0 + 0x3C);
    u8 *p34 = state + 0x34;
    u8 *p48 = state + 0x48;
    s32 farFromTarget, useLongDelay, toTargetX, signedTimer;
    s32 timer4, timer2, newTimer;

    sub_080149A4(mainObj, state, p48, 0x5A, 0x78);
    setAnimationFrame(mainObj, p34, 0, 1);

    timer4 = ((struct P48u *)p48)->timer4 - 1;
    ((struct P48u *)p48)->timer4 = timer4;
    if ((timer4 << 0x10) <= 0) {
        ((struct P48u *)p48)->timer4 = (u16)(scaleByRandom(0x3D) + 0x5A);
        if (absXFromFocus(*(s32 *)(state + 8)) <= 0x380000 &&
            absYFromFocus(*(s32 *)(state + 0xC)) <= 0x380000) {
            u8 *scriptPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            s32 *scriptJump;
            *(u8 *)(scriptPtr + 0x19) = 0;
            scriptJump = (s32 *)0x08671BD0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, *scriptJump);
            return;
        }
        signedTimer = ((struct P48s *)p48)->timer4;
        if (signedTimer < 0) signedTimer += 3;
        ((struct P48u *)p48)->timer4 = (u16)(signedTimer >> 2);
    }
    if (*(u16 *)(state + 2) & 2) {
        *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
        ((struct P48u *)p48)->timer2 = (u16)(scaleByRandom(0x15) + 0x46);
    }
    timer2 = ((struct P48u *)p48)->timer2 - 1;
    ((struct P48u *)p48)->timer2 = timer2;
    if ((timer2 << 0x10) > 0) return;

    useLongDelay = 0;
    farFromTarget = 0;
    if (absXFromFocus(*(s32 *)(state + 8)) > 0x200000) {
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
    newTimer = scaleByRandom(0x10) + 0x28;
    goto store;
set15:
    newTimer = scaleByRandom(0x15) + 0x46;
store:
    ((struct P48u *)p48)->timer2 = newTimer;
    *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
}
