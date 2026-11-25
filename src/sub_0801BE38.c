/* identical to sub_08018694 (matched), with its names changed by decompdecomp */
void sub_080186C0(u16 *a, s16 b)
{
    *a += b;
    if ((s16)*a > 0x2328)
        *a = 0x2328;
}

void sub_080186DC(u16 *a, s16 b)
{
    *a -= b;
    if ((s32)((u16)*a << 16) <= 0x03E70000)
        *a = 0x03E8;
}

/* Set flag bits `bits` in the +0x64 halfword of each of the 10 slot objects,
 * skipping empty slots. */
void sub_0801BE38(void *arg0, u16 bits)
{
    u32 *slots;
    u32 *p;
    s32 i;

    slots = *(u32 **)((u8 *)arg0 + 0x3C);
    p = slots + 0x20;
    i = 9;
    do {
        u32 member = *p;
        if (member != 0) {
            *(u16 *)(member + 0x64) |= bits;
        }
        p++;
        i--;
    } while (i >= 0);
}

void sub_08018410(void *a)
{
    u32 *base;
    u32 *p;
    s32 i;
    u32 zero;

    zero = 0;
    base = *(u32 **)((u8 *)a + 0x3C);
    p = base + 0x20;
    i = 9;
    do {
        u32 q = *p;
        if (q != 0) {
            *(u16 *)(q + 0x64) |= 1;
            *p = zero;
        }
        p++;
        i--;
    } while (i >= 0);
}
