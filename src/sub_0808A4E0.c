extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);

struct S_D {
    u8 _0[0x1C];
    s32 state1C;
    u8 _1[0x20];
    s32 effect40;
    u8 _2[0x1494];
    u16 offset14D8;
    u16 timer14DA;
};
extern struct S_D D_02025FF0;

/* When the global mode (+0x1C) is 1, request the hit effect (effect word +0x40
 * = 2, mode = 0x10, offset/timer pair at +0x14D8) and tail-call the entity's
 * current update callback; otherwise tick the animation timer and refresh the
 * sprite screen offset from the mover position. */
void sub_0808A4E0(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *moverPos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);

    if (D_02025FF0.state1C == 1) {
        D_02025FF0.effect40 = 2;
        D_02025FF0.state1C = 0x10;
        D_02025FF0.offset14D8 = 0xFFF4;
        D_02025FF0.timer14DA = 0x0D;
        sub_080C31E0(self, *(void **)(self + 0x24));
    } else {
        sub_08003740(mover + 0x20, sprite);
        sub_0806D588(sprite, moverPos);
    }
}
