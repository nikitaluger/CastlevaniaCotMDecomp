extern void sub_080C18AC(void *src, void *dst);
extern s32 sub_080C2088(void *a, void *b);

/* Builds two internal comparison values from the argument pairs and
   three-way compares them with sub_080C2088. */
void sub_080C2188(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u32 value0[5];
    u32 value1[5];
    volatile s32 pair0Lo = arg0;
    volatile s32 pair0Hi = arg1;
    volatile s32 pair1Lo = arg2;
    volatile s32 pair1Hi = arg3;

    sub_080C18AC(&pair0Lo, value0);
    sub_080C18AC(&pair1Lo, value1);
    sub_080C2088(value0, value1);
}
