void sub_080C31E0(void *, void *);

struct S_02025FF0_1848 {
    u8 _0x000[0x1848];
    u32 flags1848;
    u8 _pad[0x18C5 - 0x184C];
    u8 state18C5;
    u8 state18C6;
};
extern struct S_02025FF0_1848 D_02025FF0;

/* Ends this effect when its step counter at +0x30 is zero: clear its bits in
 * the global effect-flag word, zero the two global state bytes, then run the
 * next step. */
void sub_0805F080(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 zero = *(s32 *)(self + 0x30);
    if (zero == 0) {
        D_02025FF0.flags1848 &= 0xB205FFFF;
        D_02025FF0.state18C6 = zero;
        D_02025FF0.state18C5 = zero;
        sub_080C31E0(self, *(void **)(self + 0x24));
    }
}
