s32 sub_08011368(void *, void *, s32, s32);
s32 sub_08014938(s32);
s32 sub_08014114(s32, s32, s32, s32, s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Points the entity's body at its target, runs a countdown that toggles a
 * facing flag on the target, and once it expires inside the camera window
 * starts a new animation from the stored state; otherwise it retries later. */
void sub_080244A8(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *target = *(u8 **)(entity + 0x38);
    u8 *body = *(u8 **)(entity + 0x3C);
    u8 *aimPoint = body + 0x34;
    u8 *state = body + 0x48;
    s32 zero;
    sub_08011368(target, aimPoint, 0, 1);
    {
        s32 countdown = *(u16 *)(state + 0x04) - 1;
        *(u16 *)(state + 0x04) = (u16)countdown;
        if ((s16)countdown == 0x1E) {
            if (sub_08014938(*(s32 *)(body + 0x08)) > 0) {
                *(u16 *)(target + 0x02) = *(u16 *)(target + 0x02) | 0x10;
            } else {
                *(u16 *)(target + 0x02) = *(u16 *)(target + 0x02) & 0xFFEF;
            }
        }
    }
    if ((s16)*(u16 *)(state + 0x04) < 0) {
        if (sub_08014114(*(s32 *)(body + 0x08), *(s32 *)(body + 0x0C), -0x12, 0x12, -0x28, -8) == 1) {
            u8 *animData = *(u8 **)(state + 0x08);
            u16 newCountdown = *(u16 *)(animData + 0x00);
            zero = 0;
            *(u16 *)(state + 0x04) = newCountdown;
            *(u16 *)(state + 0x00) = *(u16 *)(animData + 0x02);
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
            {
                s32 *lit = (s32 *)0x08671BD0;
                sub_080C31E8(entity + 0x18, entity + 0x22, 1, *lit);
            }
            return;
        }
        *(u16 *)(state + 0x04) = *(u16 *)(state + 0x04) + 0x14;
    }
}
