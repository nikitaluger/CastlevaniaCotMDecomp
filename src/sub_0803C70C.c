extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);

/* Choose a random position within a fixed-point X/Y range, scale X by the
 * direction multiplier, and store the result at out+0x10 / out+0x14. */
void sub_0803C70C(u8 *out, u8 xDir, u8 xMode, u8 yMode, s32 xRange, s32 yRange)
{
    s32 xMin, xMax, yMin, yMax;
    s32 rnd;

    xMin = (xRange & 0xFFFF0000) >> 12;
    xMax = (xRange & 0xFFFF) << 4;
    yMin = (yRange & 0xFFFF0000) >> 12;
    yMax = (yRange & 0xFFFF) << 4;

    switch (xMode)
    {
    case 0:
        *(s32 *)(out + 0x10) = scaleByRandom(xMax - xMin) + xMin;
        break;
    case 1:
        rnd = randomSignedOffset(xMax - xMin);
        *(s32 *)(out + 0x10) = rnd;
        if (rnd < 0)
            *(s32 *)(out + 0x10) = rnd - xMin;
        else
            *(s32 *)(out + 0x10) = rnd + xMin;
        break;
    }

    *(s32 *)(out + 0x10) = (s8)xDir * *(s32 *)(out + 0x10);

    switch (yMode)
    {
    case 0:
        *(s32 *)(out + 0x14) = scaleByRandom(yMax - yMin) + yMin;
        break;
    case 1:
        rnd = randomSignedOffset(yMax - yMin);
        *(s32 *)(out + 0x14) = rnd;
        if (rnd < 0)
            *(s32 *)(out + 0x14) = rnd - yMin;
        else
            *(s32 *)(out + 0x14) = rnd + yMin;
        break;
    case 2:
        *(s32 *)(out + 0x14) = -(scaleByRandom(yMax - yMin) + yMin);
        break;
    }
}
