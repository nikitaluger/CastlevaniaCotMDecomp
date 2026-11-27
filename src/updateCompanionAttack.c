extern s32 scaleByRandom(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern s32 signOf(s32);
extern void updateFacingFlipTimer(s32, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 gScriptStepCallbacks;
struct S_02025FF0 { u8 _[0x174C]; s32 focusX; };
extern struct S_02025FF0 gMainWorkspace;

/* Companion attack controller: keeps the entity's attack and turn countdowns,
 * dispatches its scripted attack when lined up with the player, and reverses
 * its horizontal direction on each turn. */
void updateCompanionAttack(u8 *companion)
{
    s32 owner = *(s32 *)(companion + 0x38);
    u8 *entity = *(u8 **)(companion + 0x3C);
    u8 *animTrack = entity + 0x34;
    u8 *timers = entity + 0x48;

    updateFacingFlipTimer(owner, entity, timers, 0x5A, 0x78);
    setAnimationFrame(owner, animTrack, 0, 1);

    /* attack countdown */
    *(s16 *)(timers + 4) = *(s16 *)(timers + 4) - 1;
    if (*(s16 *)(timers + 4) <= 0)
    {
        *(u16 *)(timers + 4) = (u16)(scaleByRandom(0x1F) + 0x3C);
        if (absXFromFocus(*(s32 *)(entity + 8)) <= 0x300000 &&
            absYFromFocus(*(s32 *)(entity + 0xC)) <= 0x200000)
        {
            s32 xSign = signOf(*(s32 *)(entity + 8));
            if (xSign == getSpriteFacingSign(owner))
            {
                s16 stepIndex = *(s16 *)(companion + 0x22);
                u32 *stepCallback;
                *(u8 *)(companion + stepIndex * 2 + 0x19) = 0;
                stepCallback = (u32 *)0x08671BD0;
                sub_080C31E8(companion + 0x18, companion + 0x22, 1, *stepCallback);
                return;
            }
        }
        *(u16 *)(timers + 4) = 0;
    }

    /* facing flag: flip direction */
    if (*(u16 *)(entity + 2) & 2)
    {
        *(s32 *)(entity + 0x10) = -*(s32 *)(entity + 0x10);
        *(u16 *)(timers + 2) = (u16)(scaleByRandom(0x15) + 0x28);
    }

    /* turn countdown */
    *(s16 *)(timers + 2) = *(s16 *)(timers + 2) - 1;
    if (*(s16 *)(timers + 2) <= 0)
    {
        s32 useLongDelay = 0;
        s32 farFromFocus = 0;
        s32 toFocusX;

        if (absXFromFocus(*(s32 *)(entity + 8)) > 0x280000)
            farFromFocus = 1;

        toFocusX = gMainWorkspace.focusX - *(s32 *)(entity + 8);
        if ((toFocusX < 0 && *(s32 *)(entity + 0x10) < 0) ||
            (toFocusX > 0 && *(s32 *)(entity + 0x10) > 0))
        {
            if (farFromFocus != 0)
                goto checkDelay;
            goto longDelay;
        }
        else
        {
            if (farFromFocus == 1)
                useLongDelay = 1;
        }

    checkDelay:
        if (useLongDelay != 0)
            goto longDelay;

        *(u16 *)(timers + 2) = (u16)(scaleByRandom(6) + 0x0F);
        goto afterDelay;

    longDelay:
        *(u16 *)(timers + 2) = (u16)(scaleByRandom(0x15) + 0x28);
    afterDelay:
        *(s32 *)(entity + 0x10) = -*(s32 *)(entity + 0x10);
    }
}
