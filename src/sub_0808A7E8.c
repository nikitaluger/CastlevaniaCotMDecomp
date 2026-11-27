/* Spawn-time setup for an effect entity: point the view at its graphics table,
 * initialise the hitbox/animation parameters and play the spawn sound, then
 * run the first animation command and dispatch the state callback. */
extern void startEffectTimer(s32, s32, s32);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern s32 gScriptStepCallbackTable[];

void sub_0808A7E8(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *params = *(u8 **)(self + 0x6C);
    u8 *params2 = params + 4;
    *(s32 *)(*(u8 **)(self + 0x38) + 0x24) = 0x08507BA0;
    startEffectTimer((s32)(params + 0x20), 0, (s32)0x08507E24);
    *(s32 *)(params + 4) = 0x00A80000;
    *(s32 *)(params2 + 4) = 0x00680000;
    *(s32 *)(params2 + 8) = (s32)0xFFFE0000;
    *(s32 *)(params2 + 0x0C) = 0x0000A000;
    *(s32 *)(params2 + 0x10) = 0x34;
    sub_08005E80(0x19D);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *animScript = gScriptStepCallbackTable;
        sub_080C31E4(self + 0x18, self + 0x22, *animScript);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *animState = self + 0x18;
        s16 idx = *(s16 *)(self + 0x22);
        animState += idx * 2;
        sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *animState * 4));
    }
}
