s32 sub_0800583C(s32 range);

/* Write two random fixed-point offsets: *x in [-0x400000, 0x400000) and *y
 * in [-0x580000, -0x280000) (a +/-0x180000 jitter biased down by 0x400000). */
void randomizeLaunchOffsets(s32 *outX, s32 *outY)
{
    *outX = sub_0800583C(0x400000);
    *outY = sub_0800583C(0x180000) + 0xFFC00000;
}
