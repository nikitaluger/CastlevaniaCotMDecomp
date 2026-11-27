s32 randomSignedOffset(s32 range);

/* Write two random fixed-point offsets: *x in [-0x480000, 0x480000) and *y
 * in [-0x580000, -0x420000) (a +/-0x80000 jitter biased down by 0x500000). */
void sub_08026954(s32 *outX, s32 *outY)
{
    *outX = randomSignedOffset(0x480000);
    *outY = randomSignedOffset(0x80000) + 0xFFB00000;
}
