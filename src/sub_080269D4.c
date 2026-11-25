/* Clear `clearMask` bits in the flag word (at +0x64) of the five auxiliary
 * objects owned by the actor's sub-object; empty slots are skipped. */
void sub_080269D4(void *actor, u16 clearMask) {
    u16 m = clearMask;
    u32 *base = *(u32 **)((u8 *)actor + 0x3C);
    u32 mask = ~m;
    u32 *p = base + 0x1A;
    s32 i = 4;
    do {
        u32 *q = (u32 *)*p;
        if (q != 0) {
            *(u16 *)((u8 *)q + 0x64) &= (u16)mask;
        }
        p++;
        i--;
    } while (i >= 0);
}
