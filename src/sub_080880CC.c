/* Global game state: only the mode word at +0x14 matters to this handler. */
struct GameState {
    u8 _0[0x10];
    u32 field10;
    u32 mode;      /* +0x14: current game mode */
    u8 _1[0x1824];
};
extern struct GameState gMainWorkspace;

extern void sub_080C31E4(void *, void *, s32);
extern void startEffectTimer(void *, s32, s32);
extern void stepDelayTimer(void *, void *);
extern void sub_0806D588(void *, void *);

/* Enemy per-frame update while the game is in mode 0x17: restart the mover's
 * animation with script 0x08506414, stop it (zero x/y velocity), clear the
 * script action byte and advance the outer script through the IWRAM callback
 * table; then step the animation and copy the mover's world position into the
 * sprite's camera-relative screen position. */
void sub_080880CC(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    s32 *scriptTable;
    if (gMainWorkspace.mode == 0x17) {
        startEffectTimer(mover + 0x20, 0, 0x08506414);
        *(s32 *)(pos + 8) = 0;
        *(s32 *)(pos + 0xC) = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
    stepDelayTimer(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}
