void sub_08098598(s32, void *, void *, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Ramp the entity's 16.16 scale (self+0x5C) up by 0x1000 per frame; once it
 * passes 0xFFFF, clamp it to 1.0 (0x10000), clear the current step timer and
 * advance the command script. */
void sub_0809F1D8(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s32 scale = *(s32 *)(self + 0x5C) + 0x1000;
    *(s32 *)(self + 0x5C) = scale;
    if (scale > 0xFFFF) {
        *(s32 *)(self + 0x5C) = 0x10000;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
        }
    }
}
