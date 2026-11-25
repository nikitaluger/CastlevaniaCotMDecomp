void sub_08011368(void *, void *, s32, s32);
s32 sub_080C2F20(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Settle step: derive the sprite's countdown speed from the script step
 * (0xC00 / (step * 4)); once the speed drops to 0x20, clamp it, drop the actor
 * 16 pixels, start animation 0x2A and advance the script. */
void sub_080A4A48(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    s32 speed;
    s32 *scriptCb;

    speed = sub_080C2F20(0xC00, *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) * 4);
    *(u16 *)(sprite + 0x06) = speed;
    if ((s16)speed <= 0x20) {
        *(u16 *)(sprite + 0x06) = 0x20;
        *(u32 *)(work + 0x0C) += 0x100000;
        sub_08011368(sprite, anim, 0x2A, 0);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptCb = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
