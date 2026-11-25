struct AIEntity {
    u8 _0[0x14];
    u32 handlerTable;   /* +0x14 */
    u8 _1[0x22-0x18];
    s16 scriptIndex;    /* +0x22 */
    u8 _2[0x38-0x24];
    u32 parent;         /* +0x38 */
    u32 params;         /* +0x3C */
};
struct AIParams {
    s32 mode;           /* +0x00 */
    u32 statusAddr;     /* +0x04 */
    u8 _p[0x14-8];
    u16 unk14;          /* +0x14 */
    u16 unk16;          /* +0x16 */
};
struct AIStep { u8 _0[0x19]; u8 stepFlag; };
extern s32 sub_0808FBB4(void *);
extern void sub_08011344(u32, u32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s16 D_081003AC[];
extern u32 D_08671BD0;

/* Runs one AI behaviour step for an entity, scheduling an action from a
 * mode-dependent table and dispatching the current opcode handler. */
void sub_0808F934(struct AIEntity *entity)
{
    u32 owner;
    struct AIParams *params;
    u32 params18;
    s32 result;

    owner = entity->parent;
    params = (struct AIParams *)entity->params;
    params18 = 0x18 + (u32)params;
    result = sub_0808FBB4(entity);
    if (result == 1) {
        u8 *script; u8 *opcodePtr; u8 opcode; u32 handler; u32 *callTable;
        s16 *table;
        u32 tableOffset;
        table = D_081003AC;
        tableOffset = params->mode * 4;
        table += 1;
        sub_08011344(owner, params18, *(s16 *)((u8 *)table + tableOffset), 0);
        *(u8 *)(params->statusAddr + 1) = 0;
        params->unk14 = (u16)result;
        ((struct AIStep *)((u8 *)entity + entity->scriptIndex * 2))->stepFlag = 0;
        callTable = &D_08671BD0;
        script = (u8 *)entity + 0x18;
        sub_080C31E8(script, (u8 *)entity + 0x22, 3, *callTable);
        ((struct AIStep *)((u8 *)entity + entity->scriptIndex * 2))->stepFlag++;
        opcodePtr = script + entity->scriptIndex * 2;
        opcode = *opcodePtr;
        handler = *(u32 *)((u8 *)entity->handlerTable + opcode * 4);
        sub_080C31E0(entity, handler);
    } else {
        u8 *script; u8 *opcodePtr; u8 opcode; u32 handler; u32 *callTable;
        s16 stepIndex;
        sub_08011344(owner, params18, D_081003AC[params->mode * 2], 0);
        stepIndex = entity->scriptIndex;
        ((struct AIStep *)((u8 *)entity + stepIndex * 2))->stepFlag = 0;
        callTable = &D_08671BD0;
        script = (u8 *)entity + 0x18;
        sub_080C31E8(script, (u8 *)entity + 0x22, 1, *callTable);
        ((struct AIStep *)((u8 *)entity + entity->scriptIndex * 2))->stepFlag++;
        opcodePtr = script + entity->scriptIndex * 2;
        opcode = *opcodePtr;
        handler = *(u32 *)((u8 *)entity->handlerTable + opcode * 4);
        sub_080C31E0(entity, handler);
    }
}
