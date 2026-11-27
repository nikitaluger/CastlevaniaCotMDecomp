extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, s32, void *, void *);
extern void sub_0806BA20(s32, void *, void *);
extern void sub_080694D8(s32, void *, void *);
extern void sub_0806AB04(void *, s32, void *, void *);
extern void sub_0806A884(s32, void *);
extern s32 stepDelayTimer(void *, s32);
extern void startEffectTimer(void *, s32, s32);
extern void sub_0806932C(void *, void *);
extern u16 sub_0806BCD8(void *, s32, void *, void *);
extern void sub_0806C6B0(void *, s32, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Mutable AI/motion state stored in the work block at +4. */
struct EffectState {
    u8 pad00[8];
    s32 velX;        /* 0x08 */
    s32 velY;        /* 0x0C: countdown advanced from ENEMY_PARAM_TABLE */
    u8 pad10[0x40 - 0x10];
    s32 action;      /* 0x40: value 1 takes the cancel transition */
    s32 tableIndex;  /* 0x44: row index into ENEMY_PARAM_TABLE */
    u8 pad48[4];
    s32 f4C;         /* 0x4C */
    s32 f50;         /* 0x50 */
};
/* Work block reached through actor+0x6C: AI state at +4, effect timer at
   +0x2C, follow-up script command at +0xC8. */
struct SpawnObj {
    u8 pad00[0xC8];
    s32 command;     /* 0xC8 */
};

/* Advance an actor's AI countdown from ENEMY_PARAM_TABLE, then run the
   alternate action-step cues: cancel, fail and follow-up script commands. */
void updateActorAiAlternateStep(u8 *actor) {
    u8 *hitbox;
    u8 *work = *(u8 **)(actor + 0x6C);
    u8 *ai = work + 4;
    s32 target = *(s32 *)(actor + 0x38);
    s32 check = syncViewPosition(ai, ai);
    s32 motionTable, tableOffset;

    if (check != 0) return;

    resetActionResultState(actor, target, ai, ai);
    sub_0806BA20(target, ai, ai);
    motionTable = ENEMY_PARAM_TABLE;
    tableOffset = ((struct EffectState *)ai)->tableIndex * ENEMY_PARAM_ENTRY_SIZE;
    ((struct EffectState *)ai)->velY = ((struct EffectState *)ai)->velY + *(s32 *)(motionTable + tableOffset);
    motionTable += 4;
    {
        s32 maxValue = *(s32 *)(motionTable + tableOffset);
        if (((struct EffectState *)ai)->velY > maxValue) ((struct EffectState *)ai)->velY = maxValue;
    }
    sub_080694D8(target, ai, ai);
    sub_0806AB04(actor, target, ai, ai);
    if (((struct EffectState *)ai)->action == 1) {
        u8 *stateByte;
        s32 *cmdTable;
        ((struct EffectState *)ai)->f4C = check;
        ((struct EffectState *)ai)->f50 = check;
        ((struct EffectState *)ai)->velX = check;
        stateByte = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
        *(u8 *)(stateByte + 0x19) = check;
        cmdTable = (s32 *)SCRIPT_STEP_CALLBACK_TABLE;
        sub_080C31E8(actor + 0x18, actor + 0x22, ACTION_ALT_STEP_CANCEL, *cmdTable);
    }
    sub_0806A884(target, ai);
    hitbox = work + 0x2C;
    if (stepDelayTimer(hitbox, target) == 0) {
        u8 *stateByte;
        s32 *cmdTable;
        startEffectTimer(hitbox, 0, (void *)ACTION_ALT_ANIM_FAIL);
        stateByte = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
        *(u8 *)(stateByte + 0x19) = check;
        cmdTable = (s32 *)SCRIPT_STEP_CALLBACK_TABLE;
        sub_080C31E8(actor + 0x18, actor + 0x22, ACTION_ALT_STEP_FAIL, *cmdTable);
    }
    sub_0806932C(actor, ai);
    *(s32 *)((u8 *)work + 0xC8) = (u16)sub_0806BCD8(actor, target, ai, ai);
    if (((struct SpawnObj *)work)->command != 0) {
        u8 *stateByte;
        s32 *cmdTable;
        stepDelayTimer(hitbox, target);
        stateByte = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
        *(u8 *)(stateByte + 0x19) = check;
        cmdTable = (s32 *)SCRIPT_STEP_CALLBACK_TABLE;
        sub_080C31E8(actor + 0x18, actor + 0x22, ((struct SpawnObj *)work)->command, *cmdTable);
    }
    sub_0806C6B0(actor, target, ai, ai);
}
