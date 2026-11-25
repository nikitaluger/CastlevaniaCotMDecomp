extern void sub_080C18AC(void *src, void *dst);
extern s32 sub_080C2088(void *a, void *b);

/* Build two internal values from the arguments and three-way compare them;
   a value of type <= 1 (null/bool) always compares as greater. */
s32 sub_080C21B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u32 value0[5];
    u32 value1[5];
    volatile s32 pair0Lo = arg0;
    volatile s32 pair0Hi = arg1;
    volatile s32 pair1Lo = arg2;
    volatile s32 pair1Hi = arg3;
    s32 isSmall0, isSmall1;

    sub_080C18AC(&pair0Lo, value0);
    sub_080C18AC(&pair1Lo, value1);

    isSmall0 = 0;
    if (value0[0] <= 1) isSmall0 = 1;
    if (isSmall0 != 0) return 1;
    isSmall1 = 0;
    if (value1[0] <= 1) isSmall1 = 1;
    if (isSmall1 == 0) return sub_080C2088(value0, value1);
    return 1;
}
