s32 scaleByRandom(s32);
void setAnimationFrame(s32, void *, s32, s32);
s32 sub_08014900(s32);
s32 sub_0801491C(s32);
void sub_080149A4(s32, void *, void *, s32, s32);
void sub_080C31E8(void *, void *, s32, u32);
extern u32 gScriptStepCallbacks;
struct S_02025FF0 { u8 _[0x174C]; s32 field174C; };
extern struct S_02025FF0 gMainWorkspace;

/* Timer-driven effect update: advance the facing and event timers, hand control
 * back to the script when both coordinates are close to the target, and invert
 * the horizontal velocity when the effect drifts away from it. */
void sub_0802DB60(u8 *arg0)
{
    u8 *self = arg0;
    u8 *mainObj = *(u8 **)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *state34 = state + 0x34;
    u8 *state48 = state + 0x48;

    sub_080149A4(mainObj, state, state48, 0x5A, 0x78);
    setAnimationFrame(mainObj, state34, 0, 1);

    *(s16 *)(state48 + 4) = *(s16 *)(state48 + 4) - 1;
    if (*(s16 *)(state48 + 4) <= 0)
    {
        *(u16 *)(state48 + 4) = (u16)(scaleByRandom(0x3D) + 0x5A);
        if (sub_08014900(*(s32 *)(state + 8)) <= 0x800000 &&
            sub_0801491C(*(s32 *)(state + 0xC)) <= 0x600000)
        {
            s16 scriptIdx = *(s16 *)(self + 0x22);
            u32 *scriptJump;
            *(u8 *)(scriptIdx * 2 + (self + 0x19)) = 0;
            scriptJump = (u32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *scriptJump);
            return;
        }
    }

    if (*(u16 *)(state + 2) & 2)
    {
        *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
        *(u16 *)(state48 + 2) = (u16)(scaleByRandom(0x0B) + 0x1E);
    }

    *(s16 *)(state48 + 2) = *(s16 *)(state48 + 2) - 1;
    if (*(s16 *)(state48 + 2) <= 0)
    {
        s32 useLongDelay = 0;
        s32 farFromTarget = 0;
        s32 toTargetX;

        if (sub_08014900(*(s32 *)(state + 8)) > 0x400000)
            farFromTarget = 1;

        toTargetX = gMainWorkspace.field174C - *(s32 *)(state + 8);
        if ((toTargetX < 0 && *(s32 *)(state + 0x10) < 0) ||
            (toTargetX > 0 && *(s32 *)(state + 0x10) > 0))
        {
            if (farFromTarget != 0)
                goto checkDelay;
            goto shortDelay;
        }
        else
        {
            if (farFromTarget == 1)
                useLongDelay = 1;
        }

checkDelay:
        if (useLongDelay != 0)
            goto shortDelay;

        *(u16 *)(state48 + 2) = (u16)(scaleByRandom(6) + 0x0A);
        goto afterDelay;

shortDelay:
        *(u16 *)(state48 + 2) = (u16)(scaleByRandom(0x0B) + 0x1E);
afterDelay:
        *(s32 *)(state + 0x10) = -*(s32 *)(state + 0x10);
    }
}
