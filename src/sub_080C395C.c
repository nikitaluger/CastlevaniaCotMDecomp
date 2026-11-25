/* Logical right shift of a 64-bit value by up to 63 bits (32-bit halves in r1:r0). */
typedef union { u64 q; struct { u32 lo; u32 hi; } s; } U64;
u64 sub_080C395C(u64 val, u32 sh)
{
    U64 in, out;
    u32 bits, carry;
    in.q = val;
    if (sh == 0) return val;
    bits = 0x20 - sh;
    if ((s32)bits <= 0) {
        out.s.hi = 0;
        out.s.lo = in.s.hi >> (u32)(-bits);
    } else {
        carry = in.s.hi << bits;
        out.s.hi = in.s.hi >> sh;
        out.s.lo = (in.s.lo >> sh) | carry;
    }
    return out.q;
}
