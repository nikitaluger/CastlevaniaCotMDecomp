extern s32 stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0_AAD4 { u8 _0[0x1C]; u32 v1C; u8 _1[0x14D8-0x20]; u16 v14D8; u16 v14DA; };
extern struct S_02025FF0_AAD4 gMainWorkspace;

/* Runs the entity's current script step; when it finishes, installs the next
 * script, sets up the game-state parameters for it, then advances the step
 * byte and dispatches the new step's handler. */
void sub_0808AAD4(void *arg0) {
    s32 *handlerTable;
    u8 *self = (u8 *)arg0;
    u8 *work = *((u8 **)(self + 0x6C));
    u8 *sprite = *((u8 **)(self + 0x38));
    u8 *script = work + 0x20;
    u8 zero;
    if (stepDelayTimer(script, sprite) == 0) {
        startEffectTimer(script, 0, (void *)0x0850D684);
        stepDelayTimer(script, sprite);
        gMainWorkspace.v1C = 0x40;
        zero = 0;
        gMainWorkspace.v14D8 = 0xFFFA;
        gMainWorkspace.v14DA = 0x14;
        *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19)) = zero;
        handlerTable = &(*((s32 *)0x08671BB0));
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
