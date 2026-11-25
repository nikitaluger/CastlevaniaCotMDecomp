extern s32 sub_0806D518(void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025FF0b {
    u8 _0[0x10];
    s32 f10;
    u8 _1[0x14ED - 0x14];
    u8 f14ED;
    u8 _2[0x173A - 0x14EE];
    u8 f173A;
};
extern struct S_02025FF0b D_02025FF0;

/* Per-frame update: unless a special scroll mode owns the position, adds the
 * scroll delta to the view, runs a countdown that fires an effect when it
 * expires, snaps the view back to the grid and finally calls the callback. */
void sub_080800A0(u8 *self) {
    u8 *base = *(u8 **)(self + 0x6C);
    u8 *vec = base + 0x04;
    u8 *view = *(u8 **)(self + 0x38);

    if (sub_0806D518(self, view, vec) == 0) {
        *(s32 *)vec = *(s32 *)vec + *(s32 *)(vec + 8);
        {
            s32 countdown = *(s32 *)(vec + 0x10) - 1;
            *(s32 *)(vec + 0x10) = countdown;
            if (countdown == 0) {
                *(s32 *)(vec + 0x10) = 0x64;
                *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
                {
                    s32 *effectData = (s32 *)0x08671BB0;
                    sub_080C31E4(self + 0x18, self + 0x22, *effectData);
                }
            }
        }
        sub_08003740(base + 0x20, view);
        sub_0806D588(view, vec);
        {
            struct S_02025FF0b *caps = &D_02025FF0;
            if (caps->f173A == 0x1C || (caps->f14ED == 0 && caps->f10 != 0)) {
                sub_080C31E0((s32)self, *(s32 *)(self + 0x24));
            }
        }
    }
}
