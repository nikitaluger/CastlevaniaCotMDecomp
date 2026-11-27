/* Zone-triggered object update: when the object lies inside the active region it
 * selects the "enter" animation/action, otherwise the "idle" one; it then advances
 * the script step and dispatches that step's callback. */
/* f22 = current script step, f38 = animation channel, f3C = parameter block,
 * f14 = step callback table */
struct S_Obj { u8 _0[0x14]; u32 f14; u8 _1[0x22-0x18]; s16 f22; u8 _2[0x38-0x24]; u32 f38; u32 f3C; };
/* f00 = animation-table index, f04 = state byte block, f14 = action result */
struct S_Params { s32 f00; u32 f04; u8 _p[0x14-8]; u16 f14; u16 f16; };
struct S_Sub { u8 _0[0x19]; u8 f19; };
extern s32 sub_0809329C(void *);       /* is the object inside the active region? */
extern void setObjectAnimationFrame(u32, u32, s32, s32); /* start an animation/action */
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32); /* begin a script action */
extern s16 D_08100684[];               /* action animation table */
extern u32 gScriptStepCallbacks;                 /* action command value */
void sub_08092F7C(struct S_Obj *obj)
{
    u32 animChannel;
    struct S_Params *params;
    u32 animInfo;
    s32 inZone;
    animChannel = obj->f38;
    params = (struct S_Params *)obj->f3C;
    animInfo = 0x1C + (u32)params;
    inZone = sub_0809329C(obj);
    if (inZone == 1) {
        u8 *stepData; u8 *cursor; u8 step; u32 callback; u32 *cmdTable;
        setObjectAnimationFrame(animChannel, animInfo, D_08100684[params->f00 * 2], 0);
        *(u8 *)(params->f04 + 1) = 0;
        params->f14 = (u16)inZone;
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19 = 0;
        cmdTable = &gScriptStepCallbacks;
        stepData = (u8 *)obj + 0x18;
        sub_080C31E8(stepData, (u8 *)obj + 0x22, 3, *cmdTable);
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19++;
        cursor = stepData + obj->f22 * 2;
        step = *cursor;
        callback = *(u32 *)((u8 *)obj->f14 + step * 4);
        sub_080C31E0(obj, callback);
    } else {
        u8 *stepData; u8 *cursor; u8 step; u32 callback; u32 *cmdTable;
        s16 stepIndex;
        s16 *actionTable;
        s32 offsetVal;
        u32 zero;
        u32 tableOff;
        u8 *stateBytes;
        stateBytes = (u8 *)params->f04;
        offsetVal = *(s32 *)((u8 *)params + 0x10);
        if (offsetVal < 0) offsetVal += 0xFFFF;
        offsetVal = (offsetVal >> 16) - 0x1F;
        zero = 0;
        *(s16 *)(stateBytes + 6) = offsetVal;
        actionTable = D_08100684;
        tableOff = params->f00 * 4;
        actionTable += 1;
        setObjectAnimationFrame(animChannel, animInfo, *(s16 *)((u8 *)actionTable + tableOff), 0);
        stepIndex = obj->f22;
        ((struct S_Sub *)((u8 *)obj + stepIndex * 2))->f19 = zero;
        cmdTable = &gScriptStepCallbacks;
        stepData = (u8 *)obj + 0x18;
        sub_080C31E8(stepData, (u8 *)obj + 0x22, 1, *cmdTable);
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19++;
        cursor = stepData + obj->f22 * 2;
        step = *cursor;
        callback = *(u32 *)((u8 *)obj->f14 + step * 4);
        sub_080C31E0(obj, callback);
    }
}
