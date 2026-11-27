/*
 * Actor script step: keep the sprite's draw priority in sync with the actor's
 * depth, and while the game's action state is 6, spawn the actor's effect
 * object with the work object's motion vector, reset the step counter and
 * advance the script through the step table.
 */
struct GameState {
    u8 _pad[0x40];
    u32 actionState;  /* script/effect code, the effect fires at 6 */
};
extern struct GameState gMainWorkspace;
extern void setSpriteFacingToTarget(s32, s32);
extern void sub_0808E9EC(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_080B8484(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *scriptEntry;

    setSpriteFacingToTarget(sprite, *(s32 *)(work + 0x08));
    if (gMainWorkspace.actionState == 6) {
        sub_0808E9EC(arg0, work + 0x0C);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *stepCallback = (s32 *)0x08671BB0;
            scriptEntry = self + 0x18;
            sub_080C31E4(scriptEntry, self + 0x22, *stepCallback);
        }
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        scriptEntry = scriptEntry + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)(*(u8 *)(scriptEntry) * 4 + *(u32 *)(self + 0x14)));
    }
}
