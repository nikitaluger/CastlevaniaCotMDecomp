/* Grow a sprite's X/Y scale by 0x10 each frame; abort the script once its X
 * scale passes 0x3FF or the current room/mode changes. */
extern s32 checkGlobalStateChange(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void stepDelayTimer(void *, void *);
extern void sub_080C31E0(void *, s32);
extern u8 gMainWorkspace[];

void sub_08074870(u8 *self) {
    u8 *actor = *(u8 **)(self + 0x6C);
    u8 *mover = actor + 4;
    u8 *sprite = *(u8 **)(self + 0x38);

    if (checkGlobalStateChange(self, sprite, mover) == 0) {
        sub_0806D588(sprite, mover);
        *(u16 *)(sprite + 4) = *(u16 *)(sprite + 4) + 0x10;
        *(u16 *)(sprite + 6) = *(u16 *)(sprite + 6) + 0x10;
        stepDelayTimer(actor + 0x20, sprite);
        if (*(s16 *)(sprite + 4) > 0x3FF) {
            sub_080C31E0(self, *(s32 *)(self + 0x24));
        } else {
            u8 *state = gMainWorkspace;
            if ((state[0x173A] == 0x1C) ||
                ((state[0x14ED] == 0) && (*(u32 *)(state + 0x10) != 0))) {
                sub_080C31E0(self, *(s32 *)(self + 0x24));
            }
        }
    }
}
