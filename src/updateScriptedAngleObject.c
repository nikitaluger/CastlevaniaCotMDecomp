extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 _call_via_r1(s32, s32);
extern s32 absXFromFocus(s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern s32 scaleByRandom(s32);
extern s32 rollProbability(s32);
extern u32 gTrigFuncTable;
extern void *gScriptStepCallbacks;
extern u32 gAngleObjectStepTable[];

typedef void (*StepFn)(void *);

/* Refreshes a scripted object's angle animation, caches a trig result for the
 * current angle, then picks the next script step from distance, timer and chance. */
void updateScriptedAngleObject(void *object)
{
    u8 *self = (u8 *)object;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *stepState = work + 0x48;
    s32 workDistance;
    s32 stepDistance;
    s32 timer;
    s32 angleDivided;
    s32 trigValue;
    s32 nextAngle;
    u32 *trigFn;
    s32 zero;

    setAnimationFrame(sprite, animTrack, 0, 1);
    if (*(u8 *)(animTrack + 1) == 1 && *(u32 *)(animTrack + 4) == 1)
        *(u16 *)(stepState + 0x24) = 0;
    trigFn = &gTrigFuncTable;
    angleDivided = divInt32((s32)(*(s16 *)(stepState + 0x24) << 16), 0x3C);
    trigValue = _call_via_r1(angleDivided, *trigFn);
    *(u32 *)(stepState + 0x20) = (u32)(trigValue << 1);
    nextAngle = *(u16 *)(stepState + 0x24) + 1;
    zero = 0;
    *(u16 *)(stepState + 0x24) = nextAngle;
    workDistance = absXFromFocus(*(s32 *)(work + 8));
    stepDistance = absXFromFocus(*(s32 *)(stepState + 0));
    if (stepDistance > ANGLE_OBJECT_FAR_LIMIT) {
        void **cbp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 2, *cbp);
        goto end;
    }
    timer = *(u16 *)(stepState + 0x1C) - 1;
    *(u16 *)(stepState + 0x1C) = timer;
    if ((timer << 16) >= 0)
        goto advance;
    *(u16 *)(stepState + 0x1C) = scaleByRandom(0x3D) + 0x3C;
    if (workDistance > ANGLE_OBJECT_NEAR_LIMIT)
        goto status_check;
    if (rollProbability(ANGLE_OBJECT_CHANCE) == 1) {
        void **cbp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 4, *cbp);
        goto end;
    } else {
        void **cbp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 3, *cbp);
        goto end;
    }
status_check:
    if (*(s16 *)(stepState + 0x14) == 1) {
        void **cbp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 3, *cbp);
        goto end;
    }
advance:
    *(u32 **)(self + 0x14) = gAngleObjectStepTable;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) =
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) + 1;
    {
        s32 stepByteIndex = *(s16 *)(self + 0x22) * 2;
        u8 *scriptSteps = self + 0x18;
        ((StepFn)(*(u32 **)(self + 0x14))[*(u8 *)(scriptSteps + stepByteIndex)])(self);
    }
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
end:
}
