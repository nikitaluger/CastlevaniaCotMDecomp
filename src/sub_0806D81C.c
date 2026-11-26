extern u8 gGameStatus[];

/* Raise the current gauge value (+0x2CC) by `amount`, clamping it to the
 * gauge's limit at +0x2D0. */
void sub_0806D81C(s32 amount)
{
    u8 *state = gGameStatus;
    s32 *value = (s32 *)(state + 0x2CC);
    s32 newValue = *value + amount;
    *value = newValue;
    {
        s32 *limit = (s32 *)(state + 0x2D0);
        if (newValue > *limit)
        {
            *value = *limit;
        }
    }
}
