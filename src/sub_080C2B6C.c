extern void sub_080C25B8(void *src, void *dst);
extern s32 sub_080C2A60(void *a, void *b);

struct DecodedFloat { u32 type; u32 sign; u32 exponent; u32 mantissa; };

/* Compare two floats given as bit patterns: decode both, report 1 if either is
 * NaN, and otherwise defer to the decoded-float comparator. */
s32 sub_080C2B6C(s32 aBits, s32 bBits)
{
    struct DecodedFloat decodedA;
    struct DecodedFloat decodedB;
    volatile s32 aBitsMem = aBits, bBitsMem = bBits;
    s32 aIsNaN, bIsNaN;

    sub_080C25B8(&aBitsMem, &decodedA);
    sub_080C25B8(&bBitsMem, &decodedB);

    aIsNaN = 0;
    if (decodedA.type <= 1) aIsNaN = 1;
    if (aIsNaN != 0) return 1;
    bIsNaN = 0;
    if (decodedB.type <= 1) bIsNaN = 1;
    if (bIsNaN == 0) return sub_080C2A60(&decodedA, &decodedB);
    return 1;
}
