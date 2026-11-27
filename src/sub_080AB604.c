void setObjectAnimation(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

/* Script step: play animation frame 6 and clear the aim state's +0x10 flag,
 * then clear the step byte, run the script interpreter, advance the step byte
 * and dispatch the handler for the new step. */
void sub_080AB604(void *entity)
{
    void *sprite;
    u8 *aim;
    void *anim;
    s16 stepIndex;
    u8 *stepBase;

    sprite = *(void **)((u8 *)entity + 0x38);
    aim = *(u8 **)((u8 *)entity + 0x3C);
    anim = aim + 0x34;
    aim += 0x48;
    setObjectAnimation(sprite, anim, 6, 0);
    aim[0x10] = 0;

    stepIndex = *(s16 *)((u8 *)entity + 0x22);
    ((u8 *)entity)[stepIndex * 2 + 0x19] = 0;

    {
        void **interpreter = &gScriptStepCallbackTable;
        stepBase = (u8 *)entity + 0x18;
        sub_080C31E4(stepBase, (u8 *)entity + 0x22, *interpreter);
    }

    stepIndex = *(s16 *)((u8 *)entity + 0x22);
    ((u8 *)entity)[stepIndex * 2 + 0x19]++;

    stepIndex = *(s16 *)((u8 *)entity + 0x22);
    stepBase = stepBase + stepIndex * 2;
    sub_080C31E0(entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + stepBase[0] * 4));
}
