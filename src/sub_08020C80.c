extern void sub_08011368(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD8[];

/* Advance the actor's model animation by 8 frames (sub_08011368). If the
 * animation-restart flag (bit 1 of the anim state) is set, reload the 0x78
 * timer, clear this step's action byte at +0x17 and run the handler stored in
 * D_08671BD8[0] with mode 3. */
void sub_08020C80(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 model = *(s32 *)(self + 0x38);
    u8 *anim = *(u8 **)(self + 0x3C);
    u8 *animFlags = anim + 0x34;
    u8 *timers = anim + 0x48;
    s32 *handlerTable;

    sub_08011368(model, animFlags, 8, 0);
    if (*(u8 *)animFlags & 2) {
        s16 level;
        u8 zero = 0;
        *(u16 *)(timers + 6) = 0x78;
        level = *(s16 *)(self + 0x22);
        *(u8 *)(self + level * 2 + 0x17) = zero;
        handlerTable = D_08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *handlerTable);
    }
}
