typedef union { u64 q; struct { u32 lo; u32 hi; } w; } U64Union;
u64 sub_080C37B4(volatile u32 a0, volatile u32 a1, volatile u32 b0, volatile u32 b1)
{
    u32 al, ah, bl, bh;
    u32 p00, p01, p10, p11;
    u32 mid, hi, lo;
    u32 t0 = a0, mask;
    u32 t1;
    U64Union u;
    mask = 0xFFFF;
    al = t0 & mask; ah = t0 >> 16;
    t1 = b0;
    bl = t1 & mask; bh = t1 >> 16;
    p00 = al * bl;
    p10 = ah * bl;
    p01 = al * bh;
    p11 = ah * bh;
    mid = p01 + (p00 >> 16) + p10;
    if (mid < p10) p11 += 0x10000;
    hi = p11 + (mid >> 16);
    lo = ((mid & mask) << 16) | (p00 & mask);
    u.w.lo = lo;
    {
        u32 c0 = a0 * b1;
        u32 c1 = a1 * b0;
        u.w.hi = hi + c0 + c1;
    }
    return u.q;
}
