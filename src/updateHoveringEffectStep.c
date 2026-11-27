s32 scaleByRandom(s32);
void setAnimationFrame(s32, void *, s32, s32);
s32 absXFromFocus(s32);
s32 absYFromFocus(s32);
void updateFacingFlipTimer(s32, void *, void *, s32, s32);
void _call_via_r3(void *, void *, s32, u32);
extern struct MainWorkspaceView gMainWorkspace;

/* Advance a hovering effect's facing and velocity timers. Finish the step and
   hand control back to the script when both coordinates are near the focus,
   reverse the X velocity when the effect drifts away from its target, and pick
   the longer delay while it is still far from the target. */
void updateHoveringEffectStep(u8 *entity)
{
    u8 *self = entity;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *motion = work + 0x48;

    updateFacingFlipTimer(sprite, work, motion, HOVER_FLIP_MIN_DELAY, HOVER_FLIP_MAX_DELAY);
    setAnimationFrame(sprite, animTrack, 0, 1);

    *(s16 *)(motion + 4) = *(s16 *)(motion + 4) - 1;
    if (*(s16 *)(motion + 4) <= 0)
    {
        *(u16 *)(motion + 4) = (u16)(scaleByRandom(HOVER_FACING_TIMER_SPAN) +
                                     HOVER_FACING_TIMER_BASE);
        if (absXFromFocus(*(s32 *)(work + 8)) > HOVER_END_DISTANCE) goto div;
        if (absYFromFocus(*(s32 *)(work + 0xC)) > HOVER_END_DISTANCE) goto div;
        {
            s16 scriptIndex = *(s16 *)(self + 0x22);
            u32 *callback;
            *(u8 *)(scriptIndex * 2 + (self + 0x19)) = 0;
            callback = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
            _call_via_r3(self + 0x18, self + 0x22, 1, callback[0]);
            return;
        }
    div:
        {
            s32 signedTimer = *(s16 *)(motion + 4);
            *(s16 *)(motion + 4) = ((s32)(signedTimer + ((u32)signedTimer >> 31))) >> 1;
        }
    }

    if (*(u16 *)(work + 2) & HOVER_WORK_FLAG_REVERSE)
    {
        *(s32 *)(work + 0x10) = -*(s32 *)(work + 0x10);
        *(u16 *)(motion + 2) = (u16)(scaleByRandom(HOVER_VEL_SHORT_SPAN) +
                                     HOVER_VEL_SHORT_BASE);
    }

    *(s16 *)(motion + 2) = *(s16 *)(motion + 2) - 1;
    if (*(s16 *)(motion + 2) <= 0)
    {
        s32 useLongDelay = 0;
        s32 farFromTarget = 0;
        s32 toTargetX;

        if (absXFromFocus(*(s32 *)(work + 8)) > HOVER_FAR_X_DISTANCE)
            farFromTarget = 1;

        toTargetX = gMainWorkspace.targetX - *(s32 *)(work + 8);
        if ((toTargetX < 0 && *(s32 *)(work + 0x10) < 0) ||
            (toTargetX > 0 && *(s32 *)(work + 0x10) > 0))
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

        *(u16 *)(motion + 2) = (u16)(scaleByRandom(HOVER_VEL_LONG_SPAN) +
                                     HOVER_VEL_LONG_BASE);
        goto after_set;

set25:
        *(u16 *)(motion + 2) = (u16)(scaleByRandom(HOVER_VEL_SHORT_SPAN) +
                                     HOVER_VEL_SHORT_BASE);
after_set:
        *(s32 *)(work + 0x10) = -*(s32 *)(work + 0x10);
    }
}
