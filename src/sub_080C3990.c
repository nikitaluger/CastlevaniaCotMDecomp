/* libgcc __negdi2: two's-complement negate a 64-bit value held in s32 halves. */
typedef union {
    s64 all;
    struct { s32 lo, hi; } half;
} S64Parts;

s64 sub_080C3990(s64 value) {
    S64Parts x, r;
    s32 hi;

    x.all = value;
    r.half.lo = -x.half.lo;
    hi = -x.half.hi;
    if (r.half.lo != 0) hi -= 1;
    r.half.hi = hi;
    return r.all;
}
