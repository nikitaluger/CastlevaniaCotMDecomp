void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_0809C510(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_1848 {
    u8 _0x000[0x1848];
    u32 flags1848;
    u8 _pad[0x18C5 - 0x184C];
    u8 state18C5;
    u8 state18C6;
};
extern struct S_02025FF0_1848 D_02025FF0;

/* Ends this effect: clears its bits in the global effect-flag word, zeroes the
 * two global state bytes and the step's script byte, then runs the next step. */
void sub_08096E58(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 zero = *(s32 *)(self + 0x30);
    if (zero == 0) {
        D_02025FF0.flags1848 &= 0xB281FFFF;
        D_02025FF0.state18C6 = zero;
        D_02025FF0.state18C5 = zero;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = zero;
        {
            s32 *stepTable = (s32 *)0x08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *stepTable);
        }
    }
}
