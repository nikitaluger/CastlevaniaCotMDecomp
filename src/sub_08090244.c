extern void sub_080C050C(s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback[];

struct S_02025FF0_1848 {
    u8 _0x000[0x1848];
    u32 flags;
};
extern struct S_02025FF0_1848 gMainWorkspace;

/* Counts down the effect's animation timer; on expiry clears its state, sets
 * up the four halfword animation parameters, plays sound 0x1BE, resets the
 * step byte and runs the next script command. */
void sub_08090244(void *arg0) {
    u8 *self = arg0;
    u8 *anim = *(u8 **)(self + 0x3C);
    s32 timer;
    u16 zero = 0;
    u16 minusSix = 0xFFFA;
    if (anim) {
        timer = *(u16 *)(anim + 0x18) - 1;
        *(u16 *)(anim + 0x18) = timer;
    } else {
        timer = *(u16 *)(anim + 0x18) - 1;
        *(u16 *)(anim + 0x18) = timer;
    }
    if ((timer << 0x10) < 0) {
        *(u16 *)(anim + 0x16) = zero;
        gMainWorkspace.flags &= 0xB281FFFF;
        *(u16 *)(*(vu32 *)(anim + 4) + 6) = 10;
        *(u16 *)(*(vu32 *)(anim + 4) + 8) = 6;
        *(u16 *)(*(vu32 *)(anim + 4) + 0xA) = 4;
        *(u16 *)(*(vu32 *)(anim + 4) + 0xC) = minusSix;
        sub_080C050C(0x1BE);
        *(u8 *)((*(s16 *)(self + 0x22)) * 2 + self + 0x19) = 0;
        {
            s32 *scriptHandlers = gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
        }
    }
}
