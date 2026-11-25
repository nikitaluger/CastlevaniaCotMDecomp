void sub_080113A8(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* When the animation finishes, flag the linked object and restart the script. */
void sub_080ADFE8(void *arg0) {
    u8 *actor = (u8 *)arg0;
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *anim = work + 0x34;
    sub_080113A8(sprite, (s32)anim);
    if (*anim & 2) {
        u8 *linked = *(u8 **)(work + 0x28);
        u8 zero = 0;
        linked[1] = 5;
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
        {
            s32 *advanceCb = (s32 *)0x08671BB0;
            sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}
