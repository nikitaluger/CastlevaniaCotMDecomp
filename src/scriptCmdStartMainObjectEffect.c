extern void startEffectTimer(void *, s32, void *);
extern void setSpriteScreenPosition(void *, void *);
extern void advanceRoomScroll(void *, s32);
extern void _call_via_r1(void *, u32);
extern void _call_via_r2(void *, void *, void *);
extern u8 gMainWorkspace[];

/*
 * Script command that starts a timer-driven main-object effect: it gates on
 * the current main-object mode, seeds the effect work state from the workspace
 * coordinate tables, positions the sprite, starts its animation timer and
 * dispatches the next script step.
 */
void scriptCmdStartMainObjectEffect(u8 *script)
{
    u8 *work;
    u8 *sprite;
    u8 *pos;
    u8 *base;
    u8 *base2;
    u8 *coordTable;
    u8 *anim;
    u16 *effectMode;
    s16 stepIndex;
    u8 command;

    work = *(u8 **)(script + 0x6C) + 4;
    sprite = *(u8 **)(script + 0x38);
    pos = work;
    base = gMainWorkspace;

    if ((u8)(base[MAIN_OBJ_GATE_BYTE] - 0x10) > 1 || base[MAIN_OBJ_WORK_STATE] == 2) {
        _call_via_r1(script, *(u32 *)(script + 0x24));
        return;
    }
    advanceRoomScroll(script, 4);
    effectMode = (u16 *)(script + 0x84);
    *(u32 *)pos = *(u32 *)(base + ((effectMode[0] == 2) ? MAIN_OBJ_EFFECT_X_ALT : MAIN_OBJ_EFFECT_X));
    if (*(u16 *)(script + 0x84) == 2) {
        coordTable = gMainWorkspace;
        *(u32 *)(pos + 4) = *(u32 *)(coordTable + MAIN_OBJ_EFFECT_Y_ALT) + MAIN_OBJ_EFFECT_Y_BIAS;
    } else {
        coordTable = gMainWorkspace;
        *(u32 *)(pos + 4) = *(u32 *)(coordTable + MAIN_OBJ_EFFECT_Y) + MAIN_OBJ_EFFECT_Y_BIAS;
    }
    setSpriteScreenPosition(sprite, pos);
    startEffectTimer(work + 0x2C, 0, (void *)MAIN_OBJ_TIMER_EFFECT_ANIM_TABLE);
    base2 = gMainWorkspace;
    {
        s32 value = (base2[MAIN_OBJ_MODE_BYTE] != MAIN_OBJ_MODE_SPECIAL) ? MAIN_OBJ_EFFECT_VALUE_A : MAIN_OBJ_EFFECT_VALUE_B;
        *(u32 *)(pos + 0x10) = value;
        {
            u8 *state = base2 + MAIN_OBJ_WORK_STATE;
            value = 0;
            *state = value | 1;
        }
        {
            s32 reset = 0;
            *(u16 *)(sprite + 4) = 0x400 | reset;
            *(u16 *)(sprite + 6) = 0x400;
            *(u16 *)(sprite + 8) = value;
            stepIndex = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET);
            *(u8 *)(script + stepIndex * 2 + 0x19) = reset;
        }
    }
    {
        void **cb = (void **)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        anim = script + SCRIPT_STEP_BASE_OFFSET;
        _call_via_r2(anim, script + SCRIPT_STEP_INDEX_OFFSET, *cb);
    }
    stepIndex = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET);
    *(u8 *)(script + stepIndex * 2 + 0x19) += 1;
    stepIndex = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET);
    anim += stepIndex * 2;
    command = *anim;
    _call_via_r1(script, *(u32 *)((*(u32 **)(script + SCRIPT_STEP_TABLE_OFFSET)) + command));
}
