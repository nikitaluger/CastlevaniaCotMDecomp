extern void sub_080C18AC(void *src, void *dst);
extern s32 sub_080C1764(void *work);

/* Pass the two-word (64-bit) value through the SDK's soft-float work buffer,
 * normalizing its flag word to 0/1, and return the packed low word. */
s32 sub_080C246C(s32 lo, s32 hi)
{
    u32 work[7];
    s32 zeroFlag;

    work[5] = lo;
    work[6] = hi;
    sub_080C18AC(&work[5], work);
    zeroFlag = 0;
    if (work[1] == 0) zeroFlag = 1;
    work[1] = zeroFlag;
    return sub_080C1764(work);
}
