void sub_080148D8(s32, s32);
void sub_080114DC(s32, s32, s32, s32);
void sub_0809E278(s32, s32, void *, s32);
void sub_080C31E4(void *, void *, s32);

/*
 * Script step: face the sprite toward the player, start its animation and
 * advance the wave script; on step 0x1E clear the step and restart the script.
 */
void sub_0809D078(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    u8 *body = work + 0x48;
    sub_080148D8(sprite, *(s32 *)(work + 0x08));
    sub_080114DC(sprite, (s32)animator, 0, 1);
    sub_0809E278(sprite, (s32)animator, work, (s32)body);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
