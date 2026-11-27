/* Enemy/boss per-frame update: on the first trigger state (global flag f1C
 * == 1), queue a delayed graphics load and install its callback; always
 * advance that load and align the sprite to its sub-object's position. */
extern void stepDelayTimer(s32, s32);
extern void startEffectTimer(s32, s32, s32);
extern void sub_0806D588(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gScriptStepCallbackTable[];
extern u8 gMainWorkspace[];

void sub_0808A474(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *subObj = *(u8 **)(self + 0x6C);
    u8 *position = subObj + 4;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *gameState = gMainWorkspace;
    s32 *cbTable;
    if (*(s32 *)(gameState + 0x1C) == 1) {
        startEffectTimer((s32)(subObj + 0x20), 0, (s32)0x08502D50);
        *(s32 *)(gameState + 0x1C) = 0x10;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        cbTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *cbTable);
    }
    stepDelayTimer((s32)(subObj + 0x20), sprite);
    sub_0806D588(sprite, (s32)position);
}
