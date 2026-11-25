extern s32 sub_08005820(s32);
extern void sub_080C31E8(void *, void *, s32, s32);

struct Countdown { u8 pad[2]; u16 state; u16 timer; };

/* Decrements the sub-object countdown; on expiry clears its state, restarts the
 * timer at 30 plus a random delay, clears the element's timer byte and fires the
 * callback selected from the 0x08671BD8 table. */
void sub_0803DD54(void *actor) {
    u8 *self = (u8 *)actor;
    struct Countdown *cd = (struct Countdown *)(*(u8 **)(self + 0x3C) + 0x48);
    s32 remaining;
    s32 *callbackTable;
    u8 *elementTimer;

    remaining = cd->timer;
    remaining = remaining - 1;
    cd->timer = remaining;
    if ((s32)((u16)remaining << 16) <= 0) {
        cd->state = 0;
        cd->timer = sub_08005820(0x97) + 0x1E;
        elementTimer = (u8 *)((*(s16 *)(self + 0x22) << 1) + (s32)self) + 0x17;
        *elementTimer = 0;
        callbackTable = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *callbackTable);
    }
}
