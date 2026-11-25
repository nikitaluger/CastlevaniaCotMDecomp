extern void sub_08005E80(s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* If the work flag at +0x18 has bit 1 set, reset the timer at +0x14, play
 * sound 0x1B8, clear this script step and jump the command script to step 1. */
void sub_08096D64(void *arg0)
{
    u8 zero = 0;
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    if ((*(u8 *)(work + 0x18)) & 2) {
        *(u16 *)(work + 0x14) = zero;
        sub_08005E80(0x1B8);
        *(u8 *)((self + ((*(s16 *)(self + 0x22)) * 2)) + 0x19) = zero;
        {
            s32 *stepTable = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *stepTable);
        }
    }
}
