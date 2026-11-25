void sub_080113A8(s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_08011528(void *, void *);
void sub_080C31E0(void *, void *);
void sub_08013C8C(void *, void *);
void sub_08016678(void *);

/* Actor step: set the work block's +0xEE flag at sub-step 4, clear it at 8,
 * and when the sub-step reaches 60 reset it and advance the script. */
void sub_080A6670(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 stepCounter = *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19);
    if (stepCounter == 4) {
        *(u8 *)(work + 0xEE) = 1;
    } else if (stepCounter == 8) {
        *(u8 *)(work + 0xEE) = 0;
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x3C) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *advanceCb);
        }
    }
}
