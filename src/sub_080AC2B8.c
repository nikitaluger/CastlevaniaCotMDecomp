extern void sub_080AC9B4(u8, void *);
extern void sub_08005E80(s32);
extern void sub_080B0908(s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BB0[];

struct S_02025FF0_1754 {
    u8 _0x000[0x1754];
    s32 nextIndex;
};
extern struct S_02025FF0_1754 D_02025FF0;

/* Projectile update: runs its effect, moves it and, once it passes its travel
 * limit, raises the global object index to at least 0x11, plays sound 0x171,
 * flags its aim state and advances the script. */
void sub_080AC2B8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *aim = work + 0x48;
    s32 newY;

    sub_080AC9B4(*(u8 *)(work + 0x244), work + 0x68);

    newY = *(s32 *)(work + 0xC) + 0x20000;
    *(s32 *)(work + 0xC) = newY;
    if (newY > 0x740000) {
        if (D_02025FF0.nextIndex <= 0x10) {
            D_02025FF0.nextIndex = 0x11;
        }
        sub_08005E80(0x171);
        sub_080B0908(*(s32 *)(aim + 0x30));
        *(s32 *)(work + 0xC) = 0x740000;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptHandlers = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
        }
    }
}
