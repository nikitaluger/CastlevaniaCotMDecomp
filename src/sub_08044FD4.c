void sub_0808E408(s32, s32, s32);
extern u8 D_02025368[];

/* Vertical hit test for projectile arg2 against entity arg1: once the
 * projectile's y crosses the target's y from the side selected by arg0, spawn
 * hit effect 0x209 at the target's x and mark the hit state (arg3+5) as used.
 * The effect variant comes from a global flag byte. */
void sub_08044FD4(s32 arg0, void *arg1, void *arg2, void *arg3) {
    s32 effect;
    u8 *work;
    u8 *p;
    u8 v;
    work = D_02025368;
    if (*(u8 *)((u8 *)arg3 + 5) == 0) {
        p = work + 0x3CF;
        v = *p;
        effect = 0xD;
        if (v == 0) {
            effect = 0x100D;
        }
        if (arg0 != 0) {
            if (*(s32 *)((u8 *)arg2 + 0xC) > *(s32 *)((u8 *)arg1 + 0x6C)) {
                *(u8 *)((u8 *)arg3 + 5) = 1;
                sub_0808E408(*(s32 *)((u8 *)arg2 + 8), *(s32 *)((u8 *)arg1 + 0x6C), effect);
            }
        } else if (*(s32 *)((u8 *)arg2 + 0xC) < *(s32 *)((u8 *)arg1 + 0x6C)) {
            *(u8 *)((u8 *)arg3 + 5) = 1;
            sub_0808E408(*(s32 *)((u8 *)arg2 + 8), *(s32 *)((u8 *)arg1 + 0x6C), effect);
        }
    }
}
