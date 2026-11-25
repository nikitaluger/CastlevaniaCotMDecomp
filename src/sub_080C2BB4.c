/* Compare two IEEE-754 single-precision floats given as raw bit patterns.
 * Each pattern is decoded by sub_080C25B8 into {type, sign, exponent, mantissa};
 * if either operand is a NaN (decoded type <= 1) the comparison reports
 * unordered (1), otherwise sub_080C2A60 orders the two decoded values. */
extern void sub_080C25B8(void *src, void *dst);
extern s32 sub_080C2A60(void *a, void *b);

s32 sub_080C2BB4(s32 bitsA, s32 bitsB)
{
    u32 decodedA[4]; /* type, sign, exponent, mantissa */
    u32 decodedB[4]; /* type, sign, exponent, mantissa */
    volatile s32 rawA = bitsA, rawB = bitsB;
    s32 isNanA, isNanB;

    sub_080C25B8(&rawA, decodedA);
    sub_080C25B8(&rawB, decodedB);

    isNanA = 0;
    if (decodedA[0] <= 1) isNanA = 1;
    if (isNanA != 0) return 1;
    isNanB = 0;
    if (decodedB[0] <= 1) isNanB = 1;
    if (isNanB == 0) return sub_080C2A60(decodedA, decodedB);
    return 1;
}
