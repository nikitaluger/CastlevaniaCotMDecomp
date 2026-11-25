/* Unpacked floating-point parts: class code, sign bit, exponent, mantissa. */
struct FloatParts {
    u32 classCode;
    u32 sign;
    s32 exponent;
    u32 mantissa;
};
extern void sub_080C25B8(s32 *src, struct FloatParts *dst);
extern s32 sub_080C2500(struct FloatParts *parts);

/* Negates a float bit pattern: unpack it into parts, flip the sign field and
 * pack the parts back into an IEEE-754 word. */
s32 sub_080C2DE4(s32 bits)
{
    s32 input;
    struct FloatParts parts;
    s32 newSign;

    input = bits;
    sub_080C25B8(&input, &parts);
    newSign = 0;
    if (parts.sign == 0)
        newSign = 1;
    parts.sign = newSign;
    return sub_080C2500(&parts);
}
