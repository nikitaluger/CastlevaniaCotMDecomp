extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct S_D {
    u8 _0[0x40];
    s32 effect40;
};
extern struct S_D D_02025FF0;
extern s32 D_08671BB0;
extern u8 D_0850969C;

/* Actor tick with a countdown: when the mover's timer runs out, start the
 * animation at D_0850969C, set the global effect word (+0x40) to 7 and restart
 * the script; then refresh the sprite screen offset from the mover position. */
void sub_08088E94(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *moverPos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    s32 timer;

    timer = *(s32 *)(moverPos + 0x10) - 1;
    *(s32 *)(moverPos + 0x10) = timer;
    if (timer == 0) {
        sub_08003A6C(mover + 0x20, 0, &D_0850969C);
        D_02025FF0.effect40 = 7;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (u8)timer;
        {
            s32 *advanceTable = &D_08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *advanceTable);
        }
    }
    sub_0806D588(sprite, moverPos);
}
