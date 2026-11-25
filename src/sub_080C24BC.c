struct DoubleParts {
    u32 classCode;
    u32 sign;
    s32 exponent;
    u64 mantissa;
};

extern void sub_080C18AC(void *a, void *b);
extern s32 sub_080C2E08(u32 classCode, u32 sign, s32 exponent, u32 mantissa);

/* Decompose a double, round its 64-bit mantissa to 32 bits with a sticky bit
 * for the discarded low bits, then hand the parts to the float packer. */
void sub_080C24BC(u64 value)
{
    struct DoubleParts parts;
    u32 packedMantissa;

    sub_080C18AC(&value, &parts);
    packedMantissa = (u32)(parts.mantissa >> 30);
    if (parts.mantissa & 0x3FFFFFFF)
        packedMantissa |= 1;
    sub_080C2E08(parts.classCode, parts.sign, parts.exponent, packedMantissa);
}
