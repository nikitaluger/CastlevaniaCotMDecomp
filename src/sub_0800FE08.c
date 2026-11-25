/*
 * Decimal number to text: fill digitCount u16 slots backwards with the digits
 * of `number`, adding `digitBase` (e.g. '0') to each digit. Leading zeros are
 * blanked by writing a plain 0 instead of the based digit.
 */
s32 sub_080C2F20(s32, s32);
s32 sub_080C2F24(s32, s32);

void sub_0800FE08(s32 number, s32 digitCount, u32 digitBase, u16 *dst)
{
    u16 *cursor;
    s32 count;
    s32 remaining;
    u16 base;
    s32 isFirst;

    remaining = number;
    count = digitCount;
    cursor = dst;
    base = digitBase;
    isFirst = 0;
    while (count != 0)
    {
        s32 digit;
        digit = sub_080C2F24(remaining, 10);
        remaining = sub_080C2F20(remaining, 10);
        if (isFirst == 0 || remaining != 0 || digit != 0)
            *cursor = base + digit;
        else
            *cursor = digit;
        cursor--;
        count--;
        isFirst = 1;
    }
}
