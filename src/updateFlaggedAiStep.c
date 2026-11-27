struct FlaggedAiEntity {
    u8 _0[0x14];
    u32 handlerTable;   /* +0x14: script opcode -> callback table */
    u8 _1[0x22 - 0x18];
    s16 stepIndex;      /* +0x22: current script step */
    u8 _2[0x38 - 0x24];
    u32 sprite;         /* +0x38 */
    u32 params;         /* +0x3C: FlaggedAiParams */
};
struct FlaggedAiParams {
    s32 mode;           /* +0x00: row of gFlaggedAiAnimTable */
    u8 _p[0x1c - 4];
    u32 flagHolder;     /* +0x1C: -> holder whose +2 is a status flag id */
    u32 _20;
};
struct FlaggedAiStep { u8 _0[0x19]; u8 stepFlag; };

extern s32 isGameStatusFlagSet(u16);
extern void setObjectAnimationFrame(u32, u32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s16 gFlaggedAiAnimTable[];
extern u32 gScriptStepCallbacks;

/* Runs one scripted AI step: the entity's status flag selects the flagged
 * animation row and step 4 instead of the idle row and step 1, then the current
 * opcode's callback is dispatched. */
void updateFlaggedAiStep(struct FlaggedAiEntity *entity)
{
    u32 sprite;
    struct FlaggedAiParams *params;
    u32 params20;
    s32 flagSet;

    sprite = entity->sprite;
    params = (struct FlaggedAiParams *)entity->params;
    params20 = 0x20 + (u32)params;
    flagSet = isGameStatusFlagSet(*(u16 *)(params->flagHolder + 2));
    if (flagSet != 0) {
        u8 *script; u8 *opcodePtr; u8 opcode; u32 handler; u32 *callTable;
        s16 *animTable; u32 tableOff; u32 zero; u32 anim; u8 *stateBytes;
        animTable = gFlaggedAiAnimTable;
        tableOff = params->mode * 4;
        animTable += 1;
        setObjectAnimationFrame(sprite, params20, *(s16 *)((u8 *)animTable + tableOff), 0);
        stateBytes = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        zero = 0;
        *(s16 *)(stateBytes + 6) = 10;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 8) = 6;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 10) = 4;
        stateBytes = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        anim = 0xFFFA;
        *(u16 *)(stateBytes + 12) = anim;
        ((struct FlaggedAiStep *)((u8 *)entity + entity->stepIndex * 2))->stepFlag = zero;
        callTable = &gScriptStepCallbacks;
        script = (u8 *)entity + 0x18;
        sub_080C31E8(script, (u8 *)entity + 0x22, 4, *callTable);
        ((struct FlaggedAiStep *)((u8 *)entity + entity->stepIndex * 2))->stepFlag++;
        opcodePtr = script + entity->stepIndex * 2;
        opcode = *opcodePtr;
        handler = *(u32 *)((u8 *)entity->handlerTable + opcode * 4);
        sub_080C31E0(entity, handler);
    } else {
        u8 *script; u8 *opcodePtr; u8 opcode; u32 handler; u32 *callTable;
        s16 *animTable; u32 tableOff; u32 zero; u32 anim; u8 *stateBytes;
        animTable = gFlaggedAiAnimTable;
        tableOff = params->mode * 4;
        setObjectAnimationFrame(sprite, params20, *(s16 *)((u8 *)animTable + tableOff), 0);
        stateBytes = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        zero = 0;
        *(s16 *)(stateBytes + 6) = 4;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 8) = 10;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 10) = (s16)flagSet;
        stateBytes = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        anim = 0xFFF6;
        *(u16 *)(stateBytes + 12) = anim;
        ((struct FlaggedAiStep *)((u8 *)entity + entity->stepIndex * 2))->stepFlag = zero;
        callTable = &gScriptStepCallbacks;
        script = (u8 *)entity + 0x18;
        sub_080C31E8(script, (u8 *)entity + 0x22, 1, *callTable);
        ((struct FlaggedAiStep *)((u8 *)entity + entity->stepIndex * 2))->stepFlag++;
        opcodePtr = script + entity->stepIndex * 2;
        opcode = *opcodePtr;
        handler = *(u32 *)((u8 *)entity->handlerTable + opcode * 4);
        sub_080C31E0(entity, handler);
    }
}
