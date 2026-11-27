extern u32 nextRandomWord(void);
extern u64 sub_080C37B4(u64, u64);

/* Scale `factor` by the next pseudo-random 32-bit value: return the high 32
 * bits of the 64-bit product (a fixed-point multiply by a random fraction). */
u32 scaleByRandom(u32 factor)
{
    return sub_080C37B4((u64)nextRandomWord(), (u64)factor) >> 32;
}
