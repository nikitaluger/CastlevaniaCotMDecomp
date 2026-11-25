/* Alias of sub_080C224C. */
extern void sub_080C18AC(void *src, void *dst);
extern s32 sub_080C2088(void *a, void *b);

/* Compare two two-word values after normalising them; returns -1 when either
 * value is invalid, otherwise the signed comparison result. */
s32 sub_080C2298(s32 v0, s32 v1, s32 v2, s32 v3)
{
    u32 first[5];
    u32 second[5];
    volatile s32 a0 = v0, a1 = v1, a2 = v2, a3 = v3;
    s32 badFirst, badSecond;

    sub_080C18AC(&a0, first);
    sub_080C18AC(&a2, second);

    badFirst = 0;
    if (first[0] <= 1) badFirst = 1;
    if (badFirst != 0) return -1;
    badSecond = 0;
    if (second[0] <= 1) badSecond = 1;
    if (badSecond == 0) return sub_080C2088(first, second);
    return -1;
}
