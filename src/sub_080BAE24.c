/* Follow the mover and emit an effect; once its state reaches 2, clear the
 * extra field, reset the step byte and restart the script callback. */
extern void sub_080BB940(void *, void *);
extern void sub_080988B8(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_080BAE24(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *work = *(void **)(actor + 0x3C);
    u8 *extra = (u8 *)work + 0x48;
    void *mover = *(void **)(actor + 0x4C);
    sub_080BB940(work, mover);
    sub_080988B8(mover, *(s32 *)((u8 *)work + 8));
    if (*(u8 *)((u8 *)mover + 0x25) == 2) {
        *(s32 *)(extra + 0x68) = 0;
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb = (s32 *)0x08671BB0;
            sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}
