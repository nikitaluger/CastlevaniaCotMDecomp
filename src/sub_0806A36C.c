struct S_080DEA88 { u8 _pad[0xE3 << 3]; s32 field; };
extern struct S_080DEA88 D_080DEA88;
extern s32 syncViewPosition(s32, s32);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AA64(void *, void *);
extern void startEffectTimer(void *, s32, s32);
extern void stepDelayTimer(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Entity script step: advances the active animation block and, when its countdown
   reaches zero, resets the state and starts the next script phase. */
void sub_0806A36C(void *entity) {
    u8 *obj = (u8 *)entity;
    u8 *aiData = *(u8 **)(obj + 0x6C);
    u8 *scriptBase = aiData + 4;
    void *sprite = *(void **)(obj + 0x38);
    s32 countdown;
    u8 *state;
    if (syncViewPosition((s32)scriptBase, (s32)scriptBase) == 0) {
        resetActionResultState(entity, sprite, scriptBase, scriptBase);
        sub_0806AA64(sprite, scriptBase);
        countdown = *(s32 *)(aiData + 0xBC) - 1;
        *(s32 *)(aiData + 0xBC) = countdown;
        state = aiData + 0x2C;
        if (countdown == 0) {
            startEffectTimer(state, 0, D_080DEA88.field);
            *(s32 *)(aiData + (0x88 << 1)) = *(s32 *)(aiData + (0x84 << 1));
            *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = countdown;
            {
                const u32 *scriptId = (const u32 *)0x08671BB0;
                sub_080C31E4(obj + 0x18, obj + 0x22, *scriptId);
            }
        }
        stepDelayTimer(state, sprite);
        sub_0806C6B0(entity, sprite, scriptBase, scriptBase);
    }
}
