extern s32 sub_08005820(s32);
extern s32 signOf(s32);
extern s32 sub_080C31E0(s32, s32);
extern s32 sub_08005910(s32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 D_08671BFC;
extern u32 gMainObjTimerCallback;
extern u32 D_08671BD0;

/* World/player coordinates used as the reference point for aiming. */
struct S_02025FF0 { u8 _[0x174C]; s32 x174C; s32 x1750; };
extern struct S_02025FF0 gMainWorkspace;

/*
 * Aims a scripted entity: picks a left/right direction relative to the world
 * center, computes a target angle and turns the subject toward it, then
 * dispatches the current step's handler (or an end/turn callback).
 */
void sub_0804854C(u8 *task)
{
    u8 *subject = *(u8 **)(task + 0x3C);
    u8 *stateData = subject + 0x48;
    s32 direction = signOf(*(s32 *)(subject + 8));
    s32 baseAngle, angle;
    s32 aimX, aimY;
    u32 *angleSrc;
    u8 *stateEntry;
    u32 *endCallbacks;
    u32 *turnCallbacks;
    if (direction == 0) direction = 1;

    baseAngle = sub_08005820(0x2000);
    baseAngle *= direction;
    *(s32 *)(stateData + 0x0C) = baseAngle + 0xC000;

    angleSrc = &D_08671BFC;
    angle = sub_080C31E0(baseAngle + 0x10000, *angleSrc);
    aimX = gMainWorkspace.x174C + ((angle >> 8) << 14);

    angle = sub_080C31E0(*(s32 *)(stateData + 0x0C), *angleSrc);
    aimY = gMainWorkspace.x1750 + ((angle >> 8) << 14);

    if (*(s32 *)(stateData + 4) != 0)
        goto label_end;

    *(s32 *)(stateData + 8) = sub_08005910(aimY - *(s32 *)(subject + 0x0C), aimX - *(s32 *)(subject + 8));
    if (*(s32 *)(stateData + 4) == 0)
        goto label_turn;

label_end:
    {
        s16 stepIndex = *(s16 *)(task + 0x22);
        *(u8 *)(task + stepIndex * 2 + 0x19) = 0;
        endCallbacks = &gMainObjTimerCallback;
        stateEntry = task + 0x18;
        sub_080C31E4(stateEntry, task + 0x22, *endCallbacks);
        stepIndex = *(s16 *)(task + 0x22);
        *(u8 *)(task + stepIndex * 2 + 0x19) += 1;
        stepIndex = *(s16 *)(task + 0x22);
        stateEntry += stepIndex * 2;
        sub_080C31E0((s32)task, *(s32 *)(*(u8 **)(task + 0x14) + *(u8 *)stateEntry * 4));
        return;
    }

label_turn:
    {
        s16 stepIndex = *(s16 *)(task + 0x22);
        *(u8 *)(task + stepIndex * 2 + 0x19) = 0;
        turnCallbacks = &D_08671BD0;
        sub_080C31E8(turnCallbacks ? task + 0x18 : task + 0x18, task + 0x22, 2, *turnCallbacks);
    }
}
