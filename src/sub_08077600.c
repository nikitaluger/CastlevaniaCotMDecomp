s32 sub_0806D35C(void *, void *, void *);
void sub_0806D588(void *, void *);
void sub_08003740(void *, void *);
void sub_080C31E0(void *, void *);

/* Readable aliases for the game's helpers (preprocessor-only, no code effect). */
#define ApplySpecialMotion  sub_0806D35C
#define SyncSpritePos       sub_0806D588
#define RunSpriteTimer      sub_08003740
#define SwitchState         sub_080C31E0

struct S_02025FF0 {
    u8 pad0[0x173A];
    u8 roomState;
    u8 pad1[0x18C2 - 0x173A - 1];
    u16 spriteFlags;
};
extern struct S_02025FF0 gMainWorkspace;

/*
 * Script step for a moving sprite: if no special motion override applies, then
 * outside room states 0x0D/0x0E abort to the handler at self+0x24; otherwise
 * sync the sprite position from the mover, set its flags and run its timer.
 */
void sub_08077600(void *self) {
    void *mover;
    void *pos;
    void *sprite;
    struct S_02025FF0 *state;

    mover = *(void **)((u8 *)self + 0x6C);
    pos = (u8 *)mover + 4;
    sprite = *(void **)((u8 *)self + 0x38);
    if (ApplySpecialMotion(self, sprite, pos) == 0) {
        state = &gMainWorkspace;
        if ((u8)(state->roomState - 0xD) > 1) {
            SwitchState(self, *(void **)((u8 *)self + 0x24));
        } else {
            SyncSpritePos(sprite, pos);
            *(u16 *)sprite = state->spriteFlags;
            RunSpriteTimer((u8 *)mover + 0x20, sprite);
        }
    }
}
