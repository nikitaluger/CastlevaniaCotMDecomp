extern u8 gGameStatus[];

/* Add delta to the 32-bit stat at gGameStatus+0x2C4, clamping it to the
 * maximum stored at +0x2C8. */
void sub_0806D7F4(s32 delta)
{
    u8 *base = gGameStatus;
    s32 *value = (s32 *)(base + 0x2C4);
    s32 sum = *value + delta;
    *value = sum;
    {
        s32 *maxPtr = (s32 *)(base + 0x2C8);
        if (sum > *maxPtr)
        {
            *value = *maxPtr;
        }
    }
}

/* Add delta to the 32-bit stat at gGameStatus+0x2CC, clamping it to the
 * maximum stored at +0x2D0. */
void sub_0806D81C(s32 delta)
{
    u8 *base = gGameStatus;
    s32 *value = (s32 *)(base + 0x2CC);
    s32 sum = *value + delta;
    *value = sum;
    {
        s32 *maxPtr = (s32 *)(base + 0x2D0);
        if (sum > *maxPtr)
        {
            *value = *maxPtr;
        }
    }
}

/* Subtract amount from the 32-bit stat at gGameStatus+0x2CC, flooring at 0. */
void sub_0806D844(s32 amount)
{
    u8 *base = gGameStatus;
    s32 *value = (s32 *)(base + 0x2CC);
    s32 diff = *value - amount;
    *value = diff;
    if (diff < 0)
    {
        *value = 0;
    }
}

/* Add delta to the 16-bit stat at gGameStatus+0x2D4, clamping it to the
 * signed maximum stored at +0x2D6. */
void sub_0806D860(s16 delta)
{
    u8 *base = gGameStatus;
    s32 offset = 0x2D4;
    s16 *value = (s16 *)(base + offset);
    s16 sum = (s16)(*value + delta);
    *value = sum;
    {
        s16 *maxPtr = (s16 *)(base + offset + 2);
        s16 maxValue = *maxPtr;
        if (sum > maxValue)
        {
            *value = maxValue;
        }
    }
}
