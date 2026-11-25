/* Returns 1 when 16-bit angle `angle` is within `range` of `center`, allowing
 * for wrap-around at the 0xFFFF/0 boundary. */
s32 sub_0801476C(u32 center, u32 range, u32 angle) {
    u32 mask = 0xFFFF;
    u32 low, high;
    angle &= mask;
    low = (center - range) & mask;
    high = (center + range) & mask;
    if (low > high) {
        if (angle >= low && angle <= mask) return 1;
        if (angle <= high) return 1;
        return 0;
    }
    if (angle >= low && angle <= high) return 1;
    return 0;
}
