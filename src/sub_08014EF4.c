extern s32 sub_08005820(s32 range);

/* Returns 1 when a random roll in [0, 9999] is below `threshold` (a probability
 * expressed in 1/10000ths), 0 otherwise. */
s32 sub_08014EF4(s32 threshold)
{
    if (sub_08005820(0x2710) < threshold)
        return 1;
    return 0;
}
