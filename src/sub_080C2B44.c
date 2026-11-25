extern void sub_080C25B8(s32 *src, void *dst);
extern s32 sub_080C2A60(void *a, void *b);

/* Compare two floats given as IEEE-754 bit patterns: decode each into a
 * comparison key, then hand both keys to the decoded-float comparator. */
s32 sub_080C2B44(s32 aBits, s32 bBits) {
    s32 aBitsMem;
    s32 bBitsMem;
    u32 decodedA[4];
    u32 decodedB[4];

    aBitsMem = aBits;
    bBitsMem = bBits;
    sub_080C25B8(&aBitsMem, decodedA);
    sub_080C25B8(&bBitsMem, decodedB);
    return sub_080C2A60(decodedA, decodedB);
}
