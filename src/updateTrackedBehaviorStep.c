extern void setObjectAnimation(void *, void *, s16, s32);
extern void sub_08011528(void *, void *);
extern void sub_08011EE8(void *, u32, s32);
extern s32 moduloInt(u32, u32);
extern s32 signOf(s32);
extern s32 absXFromFocus(s32);
extern s32 sub_0801459C(u8 *, u32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_080C31E4(void *, void *, u32);
extern s16 gBehaviorAnimKinds[];
extern u32 gBehaviorSpeeds[];
extern u32 gBehaviorRanges[];
extern u32 gMainObjTimerCallbacks;
extern u32 gScriptStepCallbacks;
extern u32 gMenuScriptCallback;

/* Step callback for a tracked behaviour: select the variant's animation and
 * flip-sensitive speed, advance the movement track, then dispatch a new step
 * handler on timer wrap or distance thresholds. */
void updateTrackedBehaviorStep(u8 *entity) {
    void *sprite = *(void **)(entity + 0x38);
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *track = work + 0x34;
    u8 *behavior = work + 0x48;
    s32 xSign, timer;
    u32 speed, zero;

    setObjectAnimation(sprite, track, gBehaviorAnimKinds[*(u8 *)(behavior + 0x20)], 1);
    sub_08011528(sprite, track);
    speed = gBehaviorSpeeds[*(u8 *)(behavior + 0x20)];
    if ((*(u16 *)((u8 *)sprite + 2) & SPRITE_OAM_FLIP_X) == 0) {
        speed = (u32)-(s32)speed;
    }
    *(u32 *)(work + 0x10) = speed;
    sub_08011EE8(work, BEHAVIOR_SPEED_PARAM, 0);
    zero = 0;
    timer = *(u16 *)(behavior + 0x1C) - 1;
    *(u16 *)(behavior + 0x1C) = timer | zero;
    if ((timer << 16) == 0) {
        u32 stateCount = *(u32 *)(behavior + 0x18) + 1;
        *(u32 *)(behavior + 0x18) = stateCount;
        if (moduloInt(stateCount, 3) == 0) {
            u32 *callback;
            (entity + *(s16 *)(entity + 0x22) * 2)[0x17] = zero;
            callback = &gMenuScriptCallback;
            sub_080C31E8(entity + 0x18, entity + 0x22, BEHAVIOR_STEP_ALT, *callback);
        } else {
            u32 *callback;
            (entity + *(s16 *)(entity + 0x22) * 2)[0x17] = zero;
            callback = &gMenuScriptCallback;
            sub_080C31E8(entity + 0x18, entity + 0x22, BEHAVIOR_STEP_RESET, *callback);
        }
        return;
    }
    xSign = signOf(*(u32 *)(work + 8));
    if ((*(u16 *)((u8 *)sprite + 2) & SPRITE_OAM_FLIP_X) ? (xSign == 1) : (xSign == -1)) {
        if (absXFromFocus(*(u32 *)(work + 8)) > BEHAVIOR_FAR_X) {
            *(u8 *)(behavior + 0x20) = 1;
            return;
        }
    }
    xSign = signOf(*(u32 *)(work + 8));
    if (!((*(u16 *)((u8 *)sprite + 2) & SPRITE_OAM_FLIP_X) ? (xSign == 1) : (xSign == -1))) {
        if (absXFromFocus(*(u32 *)(work + 8)) > (s32)gBehaviorRanges[*(u8 *)(behavior + 0x20)]) {
            u32 *callback;
            (entity + *(s16 *)(entity + 0x22) * 2)[0x19] = 0;
            callback = &gMainObjTimerCallbacks;
            sub_080C31E4(entity + 0x18, entity + 0x22, *callback);
            return;
        }
    }
    xSign = signOf(*(u32 *)(work + 8));
    if ((*(u16 *)((u8 *)sprite + 2) & SPRITE_OAM_FLIP_X) ? (xSign == 1) : (xSign == -1)) {
        if (sub_0801459C(work, BEHAVIOR_FOCUS_RANGE) != 0) {
            u32 *callback;
            (entity + *(s16 *)(entity + 0x22) * 2)[0x19] = 0;
            callback = &gScriptStepCallbacks;
            sub_080C31E8(entity + 0x18, entity + 0x22, BEHAVIOR_STEP_RESET, *callback);
        }
    }
}
