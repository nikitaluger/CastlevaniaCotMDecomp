extern void sub_08011344(void *, void *, s32, s32);
extern s64 sub_0809329C(void *);
extern void sub_080C31E4(void *, void *, u32);
extern s32 D_08671BB0[];
extern struct GameState { u8 _0[0x3C]; u16 mode; } D_02025FF0;
extern struct FrameEntry { s16 frame; s16 pad; } D_08100684[];

/* AI script step: clear the sprite highlight, then, only while the game mode is
 * not 2, the work state word is not 0x2000 and the player is out of range, set
 * an animation frame from D_08100684, mark the work state and advance the script. */
void sub_08093144(void *self) {
    u8 *sprite;
    u8 *work;
    u8 *animState;
    u32 *litp;
    u32 zero;

    sprite = *(u8 **)((u8 *)self + 0x38);
    work = *(u8 **)((u8 *)self + 0x3C);
    animState = work + 0x1C;
    *(u8 *)(sprite + 0x2A) &= 0xBF;
    if (D_02025FF0.mode == 2) return;
    if (*(u16 *)(*(u8 **)(work + 0x18)) == 0x2000) return;
    if ((s32)sub_0809329C(self) != 0) return;
    sub_08011344(sprite, animState, D_08100684[*(u32 *)work].frame, 0);
    zero = 0;
    *(u16 *)(work + 0x16) = 1;
    *(u8 *)(*(u8 **)(work + 4) + 1) = 7;
    *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) = zero;
    litp = (u32 *)0x08671BB0;
    sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *litp);
}
