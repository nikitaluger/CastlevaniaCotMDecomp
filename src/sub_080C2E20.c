extern void sub_080C25B8(s32 *src, void *dst);
extern s32 sub_080C2494(s32 a, s32 b, s32 c, s32 d, s32 e);

union U { u64 q; struct { u32 lo; u32 hi; } s; };

/* Convert a float to the double-helper form: unpack it, then forward the class,
 * sign, exponent and the mantissa shifted up by 30 bits as a lo/hi word pair. */
s32 sub_080C2E20(s32 value) {
    s32 src;
    s32 parts[4];
    s32 classCode, sign, exponent;
    union U mantissa;

    src = value;
    sub_080C25B8(&src, parts);
    classCode = parts[0];
    sign = parts[1];
    exponent = parts[2];
    mantissa.q = (u64)(u32)parts[3] << 30;
    return sub_080C2494(classCode, sign, exponent, (s32)mantissa.s.lo, (s32)mantissa.s.hi);
}
