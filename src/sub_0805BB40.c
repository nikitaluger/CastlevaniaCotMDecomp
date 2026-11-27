s32 sub_08005910(s32 a, s32 b);
void setAnimationFrame(void *, void *, s32, s32);
void stepAnimationTrack(void *, void *);
void sub_080C31E4(void *, void *, void *);

extern u8 gMainWorkspace[];
extern s32 D_080CFE04[];
extern void *gScriptStepCallbackTable;

/* Entity update: when the animation state at work+0x34 has its bit-2 flag set,
 * refresh it to frame 5 and steer toward the position held in the global at
 * gMainWorkspace (+0x1750/+0x174C): add or subtract a state-indexed speed from
 * D_080CFE04 to the movement state's velocity at +8, depending on the bearing
 * quadrant, then finalize the animation bytes and run the next command step. */
void sub_0805BB40(void *entity)
{
    u8 *obj = (u8 *)entity;
    void *sprite = *(void **)(obj + 0x38);
    u8 *work = *(u8 **)(obj + 0x3C);
    u8 *anim = work + 0x34;
    u8 *move = work + 0x48;
    void **handlers;
    u8 *animState;
    u8 *animState2;
    s32 zero;

    *(u8 *)(*(u8 **)(work + 0x28) + 2) = 0;
    *(u8 *)(*(u8 **)(work + 0x28) + 3) = 0;
    stepAnimationTrack(sprite, anim);
    if (*(u8 *)anim & 2) {
        u8 *pos;
        s32 angle;
        s32 dir;
        setAnimationFrame(sprite, anim, 5, 1);
        pos = gMainWorkspace;
        angle = sub_08005910(*(s32 *)(pos + 0x1750) - *(s32 *)(work + 0x0C), *(s32 *)(pos += 0x174C) - *(s32 *)(work + 0x08));
        dir = angle & 0xC000;
        if (dir == 0x4000) goto case_sub;
        if (dir > 0x4000) goto upper;
        if (dir == 0) goto case_add;
        goto end_adj;
    upper:
        if (dir == 0x8000) goto case_add;
        if (dir == 0xC000) goto case_sub;
        goto end_adj;
    case_add:
        pos = gMainWorkspace;
        *(s32 *)(move + 8) = sub_08005910(*(s32 *)(pos + 0x1750) - *(s32 *)(work + 0x0C), *(s32 *)(pos += 0x174C) - *(s32 *)(work + 0x08)) + D_080CFE04[*move];
        goto end_adj;
    case_sub:
        pos = gMainWorkspace;
        *(s32 *)(move + 8) = sub_08005910(*(s32 *)(pos + 0x1750) - *(s32 *)(work + 0x0C), *(s32 *)(pos += 0x174C) - *(s32 *)(work + 0x08)) - D_080CFE04[*move];
    end_adj:
        animState = *(u8 **)(work + 0x28);
        zero = 0;
        *(u8 *)(animState + 2) = 8;
        animState2 = *(u8 **)(work + 0x28);
        *(u8 *)(animState2 + 3) = 1;
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        handlers = &gScriptStepCallbackTable;
        sub_080C31E4(obj + 0x18, obj + 0x22, *handlers);
    }
}
