extern s32 sub_08005820(s32);   /* random in [0, arg) */
extern s32 signOf(s32);    /* sign(sharedTargetX - arg) */

/* Random idle timer: count *timer down; when it expires, flip the sprite's
 * X-facing bit (flags bit 0x10 at sprite+2) according to which side of the
 * shared target X the entity at entity+8 is on, then reload the timer with a
 * random delay in [minDelay, maxDelay] (or exactly minDelay if both are equal). */
void sub_080149A4(void *sprite, void *entity, u16 *timer, u16 minDelay, s32 maxDelay) {
    u16 minD = (u16)minDelay;
    u16 maxD = (u16)maxDelay;
    s32 remaining;
    s16 lo, hi;
    s32 reduced, span, next;
    remaining = *timer;
    remaining = remaining - 1;
    *timer = remaining;
    if ((s32)((u16)remaining << 16) <= 0) {
        s32 flags;
        if (signOf(*(s32 *)((u8 *)entity + 8)) > 0) {
            flags = 0x10 | *(u16 *)((u8 *)sprite + 2);
            *(u16 *)((u8 *)sprite + 2) = flags;
        } else {
            *(u16 *)((u8 *)sprite + 2) &= 0xFFEF;
        }
        lo = (s16)minD;
        hi = (s16)maxD;
        if (lo == hi) {
            *timer = minD;
        } else {
            reduced = lo - 1;
            span = hi - reduced;
            next = sub_08005820(span);
            next = next + minD;
            *timer = next;
        }
    }
}
