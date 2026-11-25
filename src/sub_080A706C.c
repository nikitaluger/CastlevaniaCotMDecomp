extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

/* At sub-step 0x1E, clear the step's command byte (+0x17) and restart the
 * actor's script via the D_08671BD8 advance callback. */
void sub_080A706C(void *arg0) {
    u8 *actor = (u8*)arg0;
    if (*(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *advanceCb;
        *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x17) = 0;
        advanceCb = (s32*)0x08671BD8;
        sub_080C31E8(actor + 0x18, actor + 0x22, 0, *advanceCb);
    }
}
