/*
 * Conditional script dispatch: clear this step's flag, then run the next
 * script step with argument 7 when the global state flag equals 2, else 8.
 */
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_08010954(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *state = (u8 *)0x02025FF0;
    if (*(s32 *)(state + 0x0C) == 2) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        {
            s32 *stepCallback = (s32 *)0x08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 7, *stepCallback);
        }
    } else {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        {
            s32 *stepCallback = (s32 *)0x08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 8, *stepCallback);
        }
    }
}
