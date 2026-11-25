/*
 * Actor script step: once the animation reports "busy", knock the actor back
 * (horizontal speed 0x70000 away from its facing, upward speed 0x10000), flag
 * its facing from that speed, switch to the knocked-back animation, clear the
 * step counter and advance the script.
 */
extern void sub_080113A8(s32, void *);
extern s32 sub_080148AC(s32, s32);   /* -speed when the sprite faces left */
extern void sub_08014668(s32, s32);  /* set the sprite's facing flag from a direction */
extern void sub_080415D4(u8, s32, void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_080411D0(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    s32 speedX;
    sub_080113A8(sprite, animator);
    if (*animator & 2) {
        speedX = sub_080148AC(sprite, 0xFFF90000);
        *(s32 *)(work + 0x10) = speedX;
        *(s32 *)(work + 0x14) = 0xFFFF0000;
        sub_08014668(sprite, speedX);
        sub_080415D4(3, sprite, work, animator);
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        {
            s32 *stepCallback = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *stepCallback);
        }
    }
}
