u32 sub_080C3824(s32, s32);

/* Scale `value` by `percent` (value * percent / 100), saturating at 0xFFFF. */
u16 scalePercentSaturate16(u16 value, u16 percent) {
    u32 scaled;

    scaled = sub_080C3824(value * percent, 0x64);
    if (scaled > 0xFFFFU) {
        scaled = 0xFFFF;
    }
    return (u16)scaled;
}
