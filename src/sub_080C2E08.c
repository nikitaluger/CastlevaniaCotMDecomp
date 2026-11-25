/* Unpacked floating-point parts: class code (0/1 = NaN or infinity with a
 * mantissa, 2 = zero mantissa, 4 = infinity), sign bit, unbiased exponent and
 * extended mantissa. */
struct FloatParts {
    u32 classCode;
    u32 sign;
    s32 exponent;
    u32 mantissa;
};

s32 sub_080C2500(struct FloatParts *parts);

/* Pack the unpacked float parts into an IEEE-754 binary32 bit pattern. */
s32 sub_080C2E08(u32 classCode, u32 sign, s32 exponent, u32 mantissa) {
    struct FloatParts parts;
    parts.classCode = classCode;
    parts.sign = sign;
    parts.exponent = exponent;
    parts.mantissa = mantissa;
    return sub_080C2500(&parts);
}
