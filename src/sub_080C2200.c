/* Decode two packed 8-byte values into 5-word records; if either record's
 * leading word is <= 1 treat it as invalid, otherwise compare the records. */
extern void sub_080C18AC(void *src, void *dst);
extern s32 sub_080C2088(void *a, void *b);

s32 sub_080C2200(s32 left0, s32 left1, s32 right0, s32 right1)
{
    u32 recordLeft[5];
    u32 recordRight[5];
    volatile s32 rawLeft0 = left0;
    volatile s32 rawLeft1 = left1;
    volatile s32 rawRight0 = right0;
    volatile s32 rawRight1 = right1;
    s32 invalidLeft, invalidRight;

    sub_080C18AC(&rawLeft0, recordLeft);
    sub_080C18AC(&rawRight0, recordRight);

    invalidLeft = 0;
    if (recordLeft[0] <= 1) invalidLeft = 1;
    if (invalidLeft != 0) return 1;
    invalidRight = 0;
    if (recordRight[0] <= 1) invalidRight = 1;
    if (invalidRight == 0) return sub_080C2088(recordLeft, recordRight);
    return 1;
}
