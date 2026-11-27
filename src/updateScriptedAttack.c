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
extern s32 gScriptEventCallbacks[];

/* Per-frame update for a scripted attack object: probe the target and work
 * flags, run the hit/death response through its callback table, dispatch the
 * current script step, then place the sprite at a camera-relative position. */
void updateScriptedAttack(void *entity) {
    void *sprite;
    void *work;
    void *animTrack;
    struct ScriptedWorkFlags *workFlags;
    struct ScriptedHitTarget *target;
    s32 zero;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    animTrack = (u8 *)work + 0x34;
    workFlags = (struct ScriptedWorkFlags *)work;
    target = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
    target->hitBits |= SCRIPT_HIT_PROBE_BITS;
    zero = 0;
    if (isOutsideCameraBounds(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC)) == 1) {
        _call_via_r1(entity, *(s32 *)((u8 *)entity + 0x24));
        goto end;
    }
    if (hitTestEntities(*(void **)((u8 *)work + 0x28)) != 0) workFlags->hitFlags |= SCRIPT_WORK_HIT_BIT;
    target = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
    if (target->status & 1) workFlags->hitFlags |= SCRIPT_WORK_HIT_BIT;
    if (workFlags->hitFlags & SCRIPT_WORK_HIT_BIT) {
        target = *(struct ScriptedHitTarget **)((u8 *)work + 0x28);
        target->hitBits = zero;
        if (*((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x1A) != 2) {
            s32 *callbackSlot;
            playSound(SCRIPT_ATTACK_DEATH_SFX);
            *((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x1B) = zero;
            callbackSlot = gScriptEventCallbacks;
            _call_via_r3((u8 *)entity + 0x18, (u8 *)entity + 0x22, 2, *callbackSlot);
        }
    }
    if (updateObjectDisplayState(sprite, work) != 0) goto recycle;
    *(u32 *)((u8 *)entity + 0x14) = SCRIPTED_ATTACK_STEP_TABLE;
    *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
    {
        u8 *step = (u8 *)((s16)(*(u16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
        step[0x19] = step[0x19] + 1;
    }
    {
        s32 stepOff = (s16)(*(u16 *)((u8 *)entity + 0x22)) * 2;
        u8 *slots = (u8 *)entity;
        u8 opcode;
        slots += 0x18; slots += stepOff; opcode = *slots;
        _call_via_r1(entity, *(s32 *)(*(u32 *)((u8 *)entity + 0x14) + (u32)(opcode * 4)));
    }
    *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    if (*(u16 *)((u8 *)entity + 2) & SCRIPT_STEP_SKIP_ANIM) goto end;
    stepAnimationTrack(sprite, animTrack);
    advanceMotion(work, 0);
recycle:
    {
        u8 *camTable; u8 *camBase; u32 idx; u8 *colX; u8 *colY;
        camTable = gCameraState; camBase = gMainWorkspace; camBase += SCRIPT_SCROLL_PB_OFFSET;
        idx = ((u32)*camBase + 1) * SCRIPT_SCROLL_STRIDE;
        colX = camTable + SCRIPT_SCROLL_X_OFFSET;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 8) - ((*(s32 *)(colX + idx) + SCRIPT_SCROLL_BIAS_X) & SCRIPT_FIXED_FRAC_MASK);
        idx = ((u32)*camBase + 1) * SCRIPT_SCROLL_STRIDE;
        colY = camTable + SCRIPT_SCROLL_Y_OFFSET;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0xC) - ((*(s32 *)(colY + idx) + SCRIPT_SCROLL_BIAS_Y) & SCRIPT_FIXED_FRAC_MASK);
    }
end:
    ;
}
