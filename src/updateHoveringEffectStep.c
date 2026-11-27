s32 scaleByRandom(s32);
void setAnimationFrame(s32, void *, s32, s32);
s32 absXFromFocus(s32);
s32 absYFromFocus(s32);
void sub_080149A4(s32, void *, void *, s32, s32);
void sub_080C31E8(void *, void *, s32, u32);
struct S_02025FF0 { u8 _[0x174C]; s32 targetX; };
extern struct S_02025FF0 gMainWorkspace;

/* Timer-driven effect update: advance the facing and animation timers, return
   to the script when both coordinates are close to the target, and reverse the
   horizontal velocity when the effect moves away from it. */
void updateHoveringEffectStep(u8 *arg0)
{
    u8 *self = arg0;
    u8 *mainObj = *(u8 **)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *anim = state + 0x34;
    u8 *body = state + 0x48;

    sub_080149A4(mainObj, state, body, 0x5A, 0x78);
    setAnimationFrame(mainObj, anim, 0, 1);

    *(s16 *)(body + 4) = *(s16 *)(body + 4) - 1;
    if (*(s16 *)(body + 4) <= 0)
    {
        *(u16 *)(body + 4) = (u16)(scaleByRandom(0x3D) + 0x5A);
        if (absXFromFocus(*(s32 *)(state + 8)) > 0x600000) goto div;
        if (absYFromFocus(*(s32 *)(state + 0xC)) > 0x600000) goto div;
        {
            s16 scriptIndex = *(s16 *)(self + 0x22);
            u32 *scriptJump;
            *(u8 *)(scriptIndex * 2 + (self + 0x19)) = 0;
            scriptJump = (u32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *scriptJump);
            return;
        }
    div:
        {
            s32 signedTimer = *(s16 *)(body + 4);
            *(s16 *)(body + 4) = ((s32)(signedTimer + ((u32)signedTimer >> 31))) >> 1;
        }
    }

    if (*(u16 *)(state + 2) & 2)
    {
        *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
        *(u16 *)(body + 2) = (u16)(scaleByRandom(0x0B) + 0x1E);
    }

    *(s16 *)(body + 2) = *(s16 *)(body + 2) - 1;
    if (*(s16 *)(body + 2) <= 0)
    {
        s32 useLongDelay = 0;
        s32 farFromTarget = 0;
        s32 toTargetX;

        if (absXFromFocus(*(s32 *)(state + 8)) > 0x400000)
            farFromTarget = 1;

        toTargetX = gMainWorkspace.targetX - *(s32 *)(state + 8);
        if ((toTargetX < 0 && *(s32 *)(state + 0x10) < 0) ||
            (toTargetX > 0 && *(s32 *)(state + 0x10) > 0))
        {
            if (farFromTarget != 0)
                goto check_delay;
            goto set25;
        }
        else
        {
            if (farFromTarget == 1)
                useLongDelay = 1;
        }

check_delay:
        if (useLongDelay != 0)
            goto set25;

        *(u16 *)(body + 2) = (u16)(scaleByRandom(6) + 0x0A);
        goto after_set;

set25:
        *(u16 *)(body + 2) = (u16)(scaleByRandom(0x0B) + 0x1E);
after_set:
        *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
    }
}
