/* Decompose an IEEE-754 single precision float into sign, exponent, mantissa
 * and a class: 0/1 = NaN (signaling/quiet), 2 = zero, 3 = finite, 4 = infinity. */
struct DecodedFloat {
    u32 type;
    u32 sign;
    u32 exponent;
    u32 mantissa;
};

void _080C25B8(u32 *pBits, struct DecodedFloat *out)
{
    u32 bits;
    u32 mantissa;
    u32 exponent;
    u32 sign;
    u32 denormExp;
    u32 normExp;

    bits = *pBits;
    mantissa = (bits << 9) >> 9;
    exponent = (bits << 1) >> 24;
    sign = bits >> 31;

    out->sign = sign;

    if (exponent == 0) {
        if (mantissa == 0) {
            out->type = 2;
            goto end;
        }
        denormExp = exponent - 0x7e;
        out->exponent = denormExp;
        mantissa <<= 7;
        out->type = 3;
        if (mantissa > 0x3FFFFFFF)
            goto shared;
        normExp = denormExp;
        do {
            mantissa <<= 1;
            normExp = normExp - 1;
        } while (mantissa <= 0x3FFFFFFF);
        out->exponent = normExp;
        goto shared;
    }
    if (exponent == 0xFF) {
        if (mantissa == 0) {
            out->type = 4;
            goto end;
        }
        if ((mantissa & 0x100000) != 0)
            out->type = 1;
        else
            out->type = 0;
        goto shared;
    }
    goto normal;
shared:
    out->mantissa = mantissa;
    goto end;
normal:
    out->exponent = exponent - 0x7f;
    out->type = 3;
    out->mantissa = (mantissa << 7) | 0x40000000;
end:
}
