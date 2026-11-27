struct S_02025FF0
{
    u8 _0[0x174C];
    u32 targetX; /* 0x174C */
    u32 targetY; /* 0x1750 */
};
extern struct S_02025FF0 gMainWorkspace;
extern u32 gTrigFuncTable;
extern u32 gMainObjTimerCallbacks;
s32 getAngleFromDelta(s32, s32);
void sub_08005E80(s32);
void setObjectAnimation(void *, void *, s32, s32);
void sub_08011EE8(void *, s32, s32);
void setSpriteFacingToTarget(void *, s32);
void setEffectBehavior(s32, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Enemy script-step handler: face the shared target and seed the base X
   velocity, apply gravity for low opcodes, activate a spawned effect for
   opcode 0x28, and for 0x3C aim a trig-looked-up shot at the target. */
void enemyScriptStepAimAtPlayer(void *scriptThread)
{
    void *thread = scriptThread;
    void *sprite = *((void **) (((u8 *) thread) + 0x38));
    void *work = *((void **) (((u8 *) thread) + 0x3C));
    void *animTrack = (void *) (((u8 *) work) + 0x34);
    void *stepState = (void *) (((u8 *) work) + 0x48);
    setSpriteFacingToTarget(sprite, *((s32 *) (((u8 *) work) + 0x08)));
    {
        s32 baseVelX;
        if ((*((u16 *) (((u8 *) sprite) + 0x02))) & 0x10)
        {
            baseVelX = (s32) 0xFFFF8000;
        }
        else
        {
            baseVelX = 0x8000;
        }
        *((s32 *) (((u8 *) work) + 0x10)) = baseVelX;
    }
    {
        s16 stepIndex = *((s16 *) (((u8 *) thread) + 0x22));
        u8 opcode = *((u8 *) ((((u8 *) thread) + (stepIndex * 2)) + 0x19));
        if (opcode <= 9)
        {
            sub_08011EE8(work, 0x16C1, 0);
        }
    }
    {
        s16 stepIndex = *((s16 *) (((u8 *) thread) + 0x22));
        u8 opcode = *((u8 *) ((((u8 *) thread) + (stepIndex * 2)) + 0x19));
        if (opcode == 0x28)
        {
            setEffectBehavior(*((s32 *) (((u8 *) stepState) + 0x08)), 1);
        }
    }
    {
        s16 stepIndex = *((s16 *) (((u8 *) thread) + 0x22));
        u8 opcode = *((u8 *) ((((u8 *) thread) + (stepIndex * 2)) + 0x19));
        if (opcode == 0x3C)
        {
            s32 shotAngle;
            shotAngle = getAngleFromDelta(gMainWorkspace.targetY - (*((s32 *) (((u8 *) work) + 0x0C))), gMainWorkspace.targetX - (*((s32 *) (((u8 *) work) + 0x08))));
            {
                u32 wrappedAngle = (u32) (shotAngle + 0xFFFF5FFF);
                if (wrappedAngle <= 0x3FFE)
                {
                    if ((*((u16 *) (((u8 *) sprite) + 0x02))) & 0x10)
                    {
                        shotAngle = 0xE000;
                    }
                    else
                    {
                        shotAngle = 0xA000;
                    }
                }
            }
            {
                u32 *trigFunc = &gTrigFuncTable;
                *((s32 *) (((u8 *) work) + 0x10)) = (s32) ((sub_080C31E0(shotAngle + 0x4000, *trigFunc) >> 8) << 11);
                *((s32 *) (((u8 *) work) + 0x14)) = (s32) ((sub_080C31E0(shotAngle, *trigFunc) >> 8) << 11);
            }
            setObjectAnimation(sprite, animTrack, 0x26, 0);
            sub_08005E80(0x164);
            *((u8 *) ((((u8 *) thread) + ((*((s16 *) (((u8 *) thread) + 0x22))) * 2)) + 0x19)) = 0;
            {
                u32 *callbackTable = &gMainObjTimerCallbacks;
                sub_080C31E4(((u8 *) thread) + 0x18, ((u8 *) thread) + 0x22, *callbackTable);
            }
        }
    }
}
