extern void setObjectAnimationFrame(void *, void *, s32, s32);
extern s64 sub_080979EC(void *);
extern void sub_080C31E4(void *, void *, u32);
extern s16 D_08100B98[][2];

/* AI script step: clear the sprite highlight, then, only while the status flags are
 * quiet, this work slot is not marked done and the player is out of range, set an
 * animation frame from the table, mark the work state and advance the script. */
void sub_08097790(void *self) {
    u8 *sprite;
    u8 *statusObj;
    u8 *work;
    u8 *animState;
    u16 statusFlags;
    u32 tmp;
    u32 zero;
    s16 *frameTable;
    s16 frame;

    sprite = *(u8 **)((u8 *)self + 0x38);
    statusObj = *(u8 **)((u8 *)self + 0xAC);
    work = *(u8 **)((u8 *)self + 0x3C);
    animState = work + 0x1C;
    *(u8 *)(sprite + 0x2A) &= 0xBF;
    statusFlags = *(u16 *)(*(u8 **)(statusObj + 4) + 6);
    tmp = 2 & statusFlags;
    if (tmp) return;
    tmp = 4;
    tmp &= statusFlags;
    if (tmp) return;
    if (*(s16 *)(work + 0x18) == 1) return;
    if ((s32)sub_080979EC(self) != 0) return;
    frameTable = (s16 *)D_08100B98;
    tmp = *(s32 *)work;
    frame = frameTable[tmp * 2];
    setObjectAnimationFrame(sprite, animState, frame, 0);
    zero = 0;
    *(u16 *)(work + 0x16) = 1;
    *(u8 *)(*(u8 **)(work + 4) + 1) = 7;
    *(u8 *)((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = zero;
    {
        u32 *litp = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *litp);
    }
}
