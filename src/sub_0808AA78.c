extern void sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);

struct S_D {
    u8 _0[0x14];
    s32 state14;
};
extern struct S_D D_02025FF0;
extern s32 D_08671BB0;
extern u8 D_0850D638;

/* Actor tick: when the global state (+0x14) is 6, play the animation at
 * 0x0850D638, tick it once, play sound 0x199 and restart the script. */
void sub_0808AA78(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *sprite = *(u8 **)(self + 0x38);

    if (D_02025FF0.state14 == 6) {
        mover += 0x20;
        sub_08003A6C(mover, 0, &D_0850D638);
        sub_08003740(mover, sprite);
        sub_08005E80(0x199);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceTable = &D_08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *advanceTable);
        }
    }
}
