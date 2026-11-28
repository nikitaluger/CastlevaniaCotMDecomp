extern u8 gScriptedPropAnimData[];
void *isGameStatusFlagSet(u32);
void playSound(u32);
void startEffectTimer(void *, u32, void *);
void _call_via_r3(void *, void *, u32, u32);
void _call_via_r2(void *, void *, u32);
void _call_via_r1(void *, void *);

/* Spawn step for a scripted prop: point the sprite at its animation data, set
 * up the work object's movement, hook the entity's update callback and (when
 * the progress flag is set) reserve a 0x34-byte helper plus its spawn script,
 * scale and sound effect; then clear the step byte, run the script interpreter
 * and dispatch the next step (also on the failure path). */
void setupScriptedPropEffectStep(void *entity)
{
    u8 *self = (u8 *)entity;
    u8 *work = *(u8 **)(self + 0x6C);
    u8 *motion = work + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    void *helper;
    u8 zero;

    *(u32 *)(sprite + 0x24) = (u32)gScriptedPropAnimData;
    *(u32 *)(work + 4) = 0x00400000;
    *(u32 *)(motion + 4) = 0;
    *(u32 *)(motion + 0x2C) = 0;
    *(u8 *)(work + 0x34) = 1;
    *(u32 *)(motion + 0x18) = *(u32 *)(self + 0x24);
    *(u32 *)(self + 0x24) = SCRIPT_PROP_UPDATE_CALLBACK;

    helper = isGameStatusFlagSet(0x34);
    if (helper != 0) {
        s16 idx;
        u8 *stepBase;
        u32 scale;
        u32 *interpreter;
        *(u32 *)(motion + 4) = 0x008A0000;
        *(u32 *)(sprite + 0x24) = (u32)(gScriptedPropAnimData + 0xFFFFFE70);
        startEffectTimer(work + 0x20, 0, (void *)SCRIPT_PROP_TIMER_DATA);
        zero = 0;
        scale = 0x100;
        *(u16 *)(sprite + 4) = scale;
        playSound(scale + 0xC0);

        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = zero;
        interpreter = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
        stepBase = self + 0x18;
        _call_via_r3(stepBase, self + 0x22, 4, *interpreter);

        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) += 1;
        idx = *(s16 *)(self + 0x22);
        stepBase += idx * 2;
        {
            u8 step = *stepBase;
            void *handler = ((void **) *(u32 *)(self + 0x14))[step];
            _call_via_r1(self, handler);
        }
    } else {
        s16 idx;
        u8 *stepBase;
        u32 *interpreter;
        playSound(0x19A);

        idx = *(s16 *)(self + 0x22);
        zero = (u8)(u32)helper;
        *(u8 *)(self + idx * 2 + 0x19) = zero;
        interpreter = (u32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        stepBase = self + 0x18;
        _call_via_r2(stepBase, self + 0x22, *interpreter);

        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) += 1;
        idx = *(s16 *)(self + 0x22);
        stepBase += idx * 2;
        {
            u8 step = *stepBase;
            void *handler = ((void **) *(u32 *)(self + 0x14))[step];
            _call_via_r1(self, handler);
        }
    }
}
