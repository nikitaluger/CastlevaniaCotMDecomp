extern u32 sub_080057F8(void);
extern u64 sub_080C37B4(u64, u64);

/* Scale `factor` by the next pseudo-random 32-bit value: return the high 32
 * bits of the 64-bit product (a fixed-point multiply by a random fraction). */
u32 sub_08005820(u32 factor)
{
    return sub_080C37B4((u64)sub_080057F8(), (u64)factor) >> 32;
}
