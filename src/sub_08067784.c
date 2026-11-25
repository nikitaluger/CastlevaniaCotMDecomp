extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AA64(void *, void *);
extern s32 sub_08003740(void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, u16, s32);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern s32 D_08671BD8;

/* One frame of a scripted actor: skip unless a camera mode is active, reset
 * the result flags, ease its position toward a target, snap the sprite to the
 * tile grid, and on timer expiry dispatch a script callback. */
void sub_08067784(u8 *script) {
    u8 *actor = *(u8 **)(script + 0x6C);
    u8 *mover = actor + 4;
    void *sprite = *(void **)(script + 0x38);
    if (sub_0806C4B4(mover, mover) == 0) {
        s32 diff;
        sub_0806C5EC(script, sprite, mover, mover);
        diff = *(s32 *)(actor + 0x110) - *(s32 *)(mover + 4);
        if (diff < 0) diff += 7;
        *(s32 *)(mover + 4) = *(s32 *)(mover + 4) + (diff >> 3);
        sub_0806AA64(sprite, mover);
        if (sub_08003740(actor + 0x2C, sprite) == 0) {
            *(s32 *)(mover + 4) = *(s32 *)(actor + 0x108);
            *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x17) = 0;
            {
                u8 *p18 = script;
                u8 *p22 = script;
                s32 *lit = &D_08671BD8;
                u16 rv;
                p18 += 0x18;
                p22 += 0x22;
                rv = sub_08065CC8(script, sprite, mover, mover);
                sub_080C31E8(p18, p22, rv, *lit);
            }
        }
        sub_0806C6B0(script, sprite, mover, mover);
    }
}
