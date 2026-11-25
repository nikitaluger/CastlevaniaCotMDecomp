struct S_080921A4_Obj {
    u8 _0[0x14];
    u32 animTable;      /* 0x14: dispatch table of action callbacks */
    u8 _1[0x22 - 0x18];
    s16 actionIndex;    /* 0x22: index into the per-entity action array */
    u8 _2[0x38 - 0x24];
    u32 field38;        /* 0x38 */
    u32 params;         /* 0x3C: parameter block for this action */
};
struct S_080921A4_Params {
    s32 id;             /* 0x00: index into the s16 value table */
    u8 _1[0x10 - 4];
    u32 accum;          /* 0x10: fixed-point accumulator */
    u8 _2[0x20 - 0x14];
    u16 *flagId;        /* 0x20: id tested by the flag query */
    u8 _3[4];
};
struct S_080921A4_Step {
    u8 _0[0x19];
    u8 subStep;         /* 0x19: action sub-step counter */
};
extern s32 sub_08007EA8(u16);
extern void sub_08011344(u32, u32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s16 D_08100624[];
extern u32 D_08671BD0;

/* Conditional entity action: test a flag, seed the action state from an s16
 * value table, play animation 3 (flag set) or 1 (clear), advance the action
 * sub-step, then dispatch the next action callback. */
void sub_080921A4(struct S_080921A4_Obj *action)
{
    u32 field38;
    struct S_080921A4_Params *params;
    u32 param24;
    s32 flagSet;

    field38 = action->field38;
    params = (struct S_080921A4_Params *)action->params;
    param24 = 0x24 + (u32)params;
    flagSet = sub_08007EA8(*params->flagId);
    if (flagSet != 0) {
        u8 *stepBase; u8 *step; u8 animIndex; u32 nextAction; u32 *effectArg;
        s16 *values;
        u32 off;
        values = D_08100624;
        off = params->id * 4;
        values += 1;
        sub_08011344(field38, param24, *(s16 *)((u8 *)values + off), 0);
        params->accum += 0x40000;
        ((struct S_080921A4_Step *)((u8 *)action + action->actionIndex * 2))->subStep = 0;
        effectArg = &D_08671BD0;
        stepBase = (u8 *)action + 0x18;
        sub_080C31E8(stepBase, (u8 *)action + 0x22, 3, *effectArg);
        ((struct S_080921A4_Step *)((u8 *)action + action->actionIndex * 2))->subStep++;
        step = stepBase + action->actionIndex * 2;
        animIndex = *step;
        nextAction = *(u32 *)((u8 *)action->animTable + animIndex * 4);
        sub_080C31E0(action, nextAction);
    } else {
        u8 *stepBase; u8 *step; u8 animIndex; u32 nextAction; u32 *effectArg;
        sub_08011344(field38, param24, D_08100624[params->id * 2], 0);
        ((struct S_080921A4_Step *)((u8 *)action + action->actionIndex * 2))->subStep = flagSet;
        effectArg = &D_08671BD0;
        stepBase = (u8 *)action + 0x18;
        sub_080C31E8(stepBase, (u8 *)action + 0x22, 1, *effectArg);
        ((struct S_080921A4_Step *)((u8 *)action + action->actionIndex * 2))->subStep++;
        step = stepBase + action->actionIndex * 2;
        animIndex = *step;
        nextAction = *(u32 *)((u8 *)action->animTable + animIndex * 4);
        sub_080C31E0(action, nextAction);
    }
}
