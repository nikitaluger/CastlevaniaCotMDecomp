s32 divideInt(s32, s32); /* SWI Div: quotient */
s32 moduloInt(s32, s32); /* SWI Div: remainder */

/* Write `count` decimal digits of value into p from least significant to most
 * (p walks downward), each digit offset by the tile/character base. */
void drawPaddedDecimal(s32 value, s32 count, u32 charBase, u16 *p)
{
    s32 val = value;
    s32 left = count;
    u16 *out = p;
    u16 digitBase = (u16)charBase;

    if (left == 0)
        return;
    do
    {
        s32 digit = moduloInt(val, 10);
        val = divideInt(val, 10);
        *out = digit + digitBase;
        out--;
        left--;
    } while (left != 0);
}
