void sub_080C31E0(void *, void *);

/* Decrements the sub-object's countdown at +0x48; on wrap-around fires the
 * callback held at +0x24, and while the count is small and a global flag is
 * set, clears bit 0x40 of a byte in the secondary object. */
void sub_0805EA44(void *actor)
{
    u8 *self = (u8 *)actor;
    u8 *other = *(u8 **)(self + 0x38);
    u8 *timer = *(u8 **)(self + 0x3C) + 0x48;
    s16 remaining;

    remaining = --*(s16 *)timer;
    if (remaining < 0) {
        sub_080C31E0(actor, *(void **)(self + 0x24));
        return;
    }
    if (remaining <= 0x77) {
        extern u8 D_02025FF0[];
        u8 *flags = D_02025FF0;
        flags += 0x189C;
        if (*(u32 *)flags & 1) {
            *(u8 *)(other + 0x2A) &= 0xBF;
        }
    }
}
