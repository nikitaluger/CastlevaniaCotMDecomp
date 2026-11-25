extern void sub_080C31E8(void *, void *, s32, s32);

/* Reset the current script step and dispatch result 3 or 6, chosen by the work
 * state byte at +0x89, through the script interpreter. */
void sub_0809DD64(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    switch (*(u8 *)(work + 0x89)) {
    case 0:
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *resultTable = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 3, *resultTable);
        }
        break;
    case 1:
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *resultTable = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 6, *resultTable);
        }
        break;
    }
}
