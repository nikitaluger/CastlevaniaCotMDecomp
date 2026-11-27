void stepAnimationTrack(void *, void *);
void advanceMotion(void *, u32);
s32 updateObjectDisplayState(void *, void *);
s32 isOutsideCameraBounds(s32, s32);
void _call_via_r1(void *, s32);
void _call_via_r3(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gScriptEventCallbacks;
extern u32 gScriptedKind5EStepTable;

/* Per-frame update for a scripted kind-0x5E object: mark the linked collision
 * target, handle the cull/death response, dispatch one command from the
 * object's nested script table, then write its camera-relative screen
 * position. */
void updateScriptedKind5EObject(void *self) {
    void *sprite;
    void *work;
    void *animTrack;
    struct ScriptedWorkFlags *workFlags;
    struct ScriptedHitTarget *target;

    sprite = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    animTrack = (u8 *)work + 0x34;
    workFlags = (struct ScriptedWorkFlags *)work;
    target = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
    target->hitBits |= 1;

    if (isOutsideCameraBounds(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC)) == 1) {
        _call_via_r1(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }

    target = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
    if (target->status & 1) {
        workFlags->hitFlags |= SCRIPT_WORK_HIT_BIT;
    }

    if (workFlags->hitFlags & SCRIPT_WORK_HIT_BIT) {
        target = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
        target->hitBits &= SCRIPT_TARGET_HIT_CLEAR;
        if (*((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x1A) != 1) {
            u32 *eventCallback;
            *((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x1B) = 0;
            eventCallback = &gScriptEventCallbacks;
            _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *eventCallback);
        }
    }

    if (updateObjectDisplayState(sprite, work) == 0) {
        *(u32 *)((u8 *)self + 0x14) = (u32)&gScriptedKind5EStepTable;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        {
            u8 *step = (u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
            step[0x19] = step[0x19] + 1;
        }
        {
            s32 stepOff = (s16)(*(u16 *)((u8 *)self + 0x22)) * 2;
            u8 *slots = (u8 *)self;
            u8 opcode;
            slots += 0x18;
            slots += stepOff;
            opcode = *slots;
            _call_via_r1(self, *(s32 *)(*(u32 *)((u8 *)self + 0x14) + (u32)(opcode * 4)));
        }
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
        if (*(u16 *)((u8 *)self + 2) & SCRIPT_STEP_SKIP_ANIM) {
            return;
        }
        stepAnimationTrack(sprite, animTrack);
        advanceMotion(work, 0);
    }

    {
        struct ScriptedHitTarget *target2;
        u8 *camTable;
        u8 *camBase;
        u32 scrollIndex;
        u8 *scrollX;
        u8 *scrollY;

        target2 = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
        target2->status = 0;
        camTable = gCameraState;
        camBase = gMainWorkspace;
        camBase += SCRIPT_SCROLL_PB_OFFSET;
        scrollIndex = ((u32)*camBase + 1) * SCRIPT_SCROLL_STRIDE;
        scrollX = camTable + SCRIPT_SCROLL_X_OFFSET;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 8) - ((*(s32 *)(scrollX + scrollIndex) + SCRIPT_SCROLL_BIAS_X) & SCRIPT_FIXED_FRAC_MASK);
        scrollIndex = ((u32)*camBase + 1) * SCRIPT_SCROLL_STRIDE;
        scrollY = camTable + SCRIPT_SCROLL_Y_OFFSET;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0xC) - ((*(s32 *)(scrollY + scrollIndex) + SCRIPT_SCROLL_BIAS_Y) & SCRIPT_FIXED_FRAC_MASK);
    }
}
