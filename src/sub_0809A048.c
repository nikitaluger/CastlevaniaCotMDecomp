extern void sub_080C31E8(void *, void *, s32, s32);

/* Script step handler: once the current step's sub-step counter reaches 0x0A,
 * clear the alternate sub-step byte (+0x17) and advance the script with
 * argument 3. */
void sub_0809A048(void *arg0)
{
    u8 *self = arg0;
    s16 idx = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + idx * 2 + 0x19) == 0x0A) {
        s32 *advanceCb;
        *(u8 *)(self + idx * 2 + 0x17) = 0;
        advanceCb = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *advanceCb);
    }
}
