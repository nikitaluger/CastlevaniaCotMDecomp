extern vu32 D_0200A260; /* global pseudo-random number generator state */

/* Advances the global PRNG and returns the new 32-bit value; callers usually
 * use only its low bits (e.g. & 3). */
u32 sub_080057F8(void) {
    u32 state = D_0200A260;
    u32 mix = (state >> 16) ^ state;
    u32 next = state * 0x499602D2u;
    next ^= mix << 8;
    next -= mix;
    D_0200A260 = state + next;
    return state + next;
}
