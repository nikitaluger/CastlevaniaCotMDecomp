void sub_080113A8(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Keep the linked body's animation in sync with its sprite; when the body's
 * hitbox reports contact (bit 1), raise the hit flag, clear this script step's
 * sub-counter and run the script-advance callback (0x08671BB0). */
void sub_080B87BC(void *arg0) {
    u8 *actor = (u8 *)arg0;
    s32 r5 = *(s32 *)(actor + 0x38);
    void *hitbox = (u8 *)*(void **)(actor + 0x3C) + 0x34;
    sub_080113A8(r5, hitbox);
    if (*(u8 *)hitbox & 2) {
        u8 *p = *(u8 **)(actor + 0x28) + 0x4C;
        u8 zero = 0;
        *p = 1;
        *(u8 *)(actor + (*(s16 *)(actor + 0x22) * 2) + 0x19) = zero;
        {
            s32 *advanceCb = (s32 *)0x08671BB0;
            sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}
