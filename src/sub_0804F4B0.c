extern s32 sub_080146D0(void *, u16, s32);
extern s32 sub_08014964(s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* Enemy AI script step: while the target's y is not greater than work's y,
 * advance the heading at moveState+8 by half a turn (0x8000, wrapped to 16
 * bits), steer work at speed 0x20000 along it, then clear the script action
 * byte and advance the script. */
void sub_0804F4B0(void *self) {
    u8 *actor = (u8 *)self;
    void *work = *(void **)(actor + 0x3C);
    void *moveState = (u8 *)work + 0x48;
    s32 *scriptTable;
    if (sub_08014964(*(s32 *)((u8 *)work + 0x0C)) <= 0) {
        u32 angle = *(u32 *)((u8 *)moveState + 0x08) + 0x8000;
        angle = angle & 0x0000FFFF;
        *(u32 *)((u8 *)moveState + 0x08) = angle;
        sub_080146D0(work, (u16)angle, 0x20000);
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(actor + 0x18, actor + 0x22, *scriptTable);
    }
}
