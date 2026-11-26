/* identical to sub_080C2BFC (matched), with its names changed by decompdecomp */
extern void sub_080C25B8(s32 *src, u32 *dst);
extern s32 sub_080C2A60(u32 *a, u32 *b);

/* Decode two float bit patterns and compare them; a NaN or zero operand
 * (decoded type <= 1) makes this return -1 without comparing. */
s32 sub_080C2C44(s32 aBits, s32 bBits) {
    u32 aParts[4];
    u32 bParts[4];
    s32 aRaw;
    s32 bRaw;
    s32 aInvalid;
    s32 bInvalid;

    aRaw = aBits;
    bRaw = bBits;
    sub_080C25B8(&aRaw, aParts);
    sub_080C25B8(&bRaw, bParts);

    aInvalid = 0;
    if (aParts[0] <= 1)
        aInvalid = 1;
    if (aInvalid != 0)
        return -1;

    bInvalid = 0;
    if (bParts[0] <= 1)
        bInvalid = 1;
    if (bInvalid == 0)
        return sub_080C2A60(aParts, bParts);
    return -1;
}
