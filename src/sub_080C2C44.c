/* Compare two floats given as raw IEEE-754 bit patterns.  _080C25B8 decodes
 * each pattern into {type, sign, exponent, mantissa}; if either value is a NaN
 * (type 0 or 1) the comparison fails with -1, otherwise sub_080C2A60 orders
 * the two decoded values. */
extern void _080C25B8(s32 *pBits, u32 *decoded);
extern s32 sub_080C2A60(u32 *a, u32 *b);

s32 sub_080C2C44(u32 bitsA, u32 bitsB) {
    u32 decodedA[4]; /* type, sign, exponent, mantissa */
    u32 decodedB[4]; /* type, sign, exponent, mantissa */
    u32 bitsA2;
    u32 bitsB2;
    s32 isNanA;
    s32 isNanB;

    bitsA2 = bitsA;
    bitsB2 = bitsB;
    _080C25B8(&bitsA2, decodedA);
    _080C25B8(&bitsB2, decodedB);

    isNanA = 0;
    if (decodedA[0] <= 1)
        isNanA = 1;
    if (isNanA != 0)
        return -1;

    isNanB = 0;
    if (decodedB[0] <= 1)
        isNanB = 1;
    if (isNanB == 0)
        return sub_080C2A60(decodedA, decodedB);
    return -1;
}
