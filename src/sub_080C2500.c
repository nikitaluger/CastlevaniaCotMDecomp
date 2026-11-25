/* Unpacked floating-point parts: class code (0/1 = NaN or infinity with a
 * mantissa, 2 = zero mantissa, 4 = infinity), sign bit, unbiased exponent and
 * extended mantissa. */
struct FloatParts {
    u32 classCode;
    u32 sign;
    s32 exponent;
    u32 mantissa;
};

/* Packs the unpacked float in parts into an IEEE-754 binary32 bit pattern,
 * handling NaN/infinity/denormal classes, rounding and exponent bias.
 */
s32 sub_080C2500(struct FloatParts *parts)
{
    u32 mantissa;
    u32 sign;
    s32 exp;
    s32 isSpecial, isInfinity, isZeroClass;
    u32 classCode;
    u32 result;
    s32 unbiasedExp;
    u32 expBits, signBits;

    mantissa = parts->mantissa;
    sign = parts->sign;
    exp = 0;
    isSpecial = 0;
    classCode = parts->classCode;
    if (classCode <= 1)
        isSpecial = 1;
    if (isSpecial != 0)
    {
        exp = 0xFF;
        mantissa |= 0x100000;
        goto pack;
    }
    isInfinity = 0;
    if (classCode == 4)
        isInfinity = 1;
    if (isInfinity != 0)
        goto ff_zero;
    isZeroClass = 0;
    if (classCode == 2)
        isZeroClass = 1;
    if (isZeroClass != 0)
    {
        mantissa = 0;
        goto pack;
    }
    if (mantissa == 0)
        goto pack;
    unbiasedExp = parts->exponent;
    if (unbiasedExp < -0x7E)
    {
        s32 shift = -0x7E - unbiasedExp;
        if (shift > 0x19)
            mantissa = 0;
        else
            mantissa >>= shift;
        goto shift_end;
    }
    if (unbiasedExp <= 0x7F)
        goto normal;
ff_zero:
    exp = 0xFF;
    mantissa = 0;
    goto pack;
normal:
    exp = unbiasedExp + 0x7F;
    if ((mantissa & 0x7F) == 0x40)
    {
        if (mantissa & 0x80)
            mantissa += 0x40;
    }
    else
    {
        mantissa += 0x3F;
    }
    if ((s32)mantissa < 0)
    {
        mantissa >>= 1;
        exp++;
    }
shift_end:
    mantissa >>= 7;
pack:
    mantissa = mantissa & 0x007FFFFF;
    result = result & 0xFF800000;
    result = result | mantissa;
    exp = exp & 0xFF;
    expBits = exp << 23;
    result = result & 0x807FFFFF;
    result = result | expBits;
    signBits = sign << 31;
    result = result & 0x7FFFFFFF;
    result = result | signBits;
    return result;
}
