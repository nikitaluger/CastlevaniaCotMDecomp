extern s32 playSound(s32);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern s32 hitTestEntities(void *);
extern s32 isOutsideCameraBounds(s32, s32);
extern void _call_via_r1(void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gScriptEventCallbacks[];

/* Per-frame update for a scripted entity with a mover work state: probe the
 * sensor, run the hit/death response, dispatch the current script step through
 * the mover-family handler table, then write the mover's camera-scroll-
 * relative screen position. */
void updateScriptedMoverAlt(void *self) {
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
    target->hitBits |= SCRIPT_HIT_PROBE_BITS;

    if (isOutsideCameraBounds(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC)) == 1) {
        _call_via_r1(self, *(s32 *)((u8 *)self + 0x24));
        goto end;
    }
    if (hitTestEntities(*(void **)((u8 *)work + 0x28)) != 0) workFlags->hitFlags |= SCRIPT_WORK_HIT_BIT;
    if ((*(struct ScriptedHitTarget **)((u8 *)work + 0x28))->status & 1) workFlags->hitFlags |= SCRIPT_WORK_HIT_BIT;
    if (workFlags->hitFlags & SCRIPT_WORK_HIT_BIT) {
        if (*((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x1A) != 1) {
            u32 *eventCallback;
            playSound(SCRIPT_DEATH_SFX);
            *((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x1B) = 0;
            eventCallback = gScriptEventCallbacks;
            _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *eventCallback);
        }
    }
    if (updateObjectDisplayState(sprite, work) != 0) goto recycle;
    *(u32 *)((u8 *)self + 0x14) = SCRIPTED_MOVER_ALT_STEP_TABLE;
    *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
    {
        u8 *step = (u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        step[0x19] = step[0x19] + 1;
    }
    {
        s32 stepOff = (s16)(*(u16 *)((u8 *)self + 0x22)) * 2;
        u8 *slots = (u8 *)self;
        u8 opcode;
        slots += 0x18; slots += stepOff; opcode = *slots;
        _call_via_r1(self, *(s32 *)(*(u32 *)((u8 *)self + 0x14) + (u32)(opcode * 4)));
    }
    *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
    if (*(u16 *)((u8 *)self + 2) & SCRIPT_STEP_SKIP_ANIM) goto end;
    stepAnimationTrack(sprite, animTrack);
    advanceMotion(work, 0);
recycle:
    {
        struct ScriptedHitTarget *target2;
        u8 *camTable;
        u8 *camBase;
        u32 idx;
        u8 *scrollX;
        u8 *scrollY;

        target2 = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
        target2->status = 0;
        camTable = gCameraState;
        camBase = gMainWorkspace;
        camBase += SCRIPT_SCROLL_PB_OFFSET;
        idx = ((u32)*camBase + 1) * SCRIPT_SCROLL_STRIDE;
        scrollX = camTable + SCRIPT_SCROLL_X_OFFSET;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 8) - ((*(s32 *)(scrollX + idx) + SCRIPT_SCROLL_BIAS_X) & SCRIPT_FIXED_FRAC_MASK);
        idx = ((u32)*camBase + 1) * SCRIPT_SCROLL_STRIDE;
        scrollY = camTable + SCRIPT_SCROLL_Y_OFFSET;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0xC) - ((*(s32 *)(scrollY + idx) + SCRIPT_SCROLL_BIAS_Y) & SCRIPT_FIXED_FRAC_MASK);
    }
end:
    ;
}
