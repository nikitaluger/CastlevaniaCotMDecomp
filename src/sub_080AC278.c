extern void sub_080AC9B4(u8, void *);
extern void _call_via_r2(void *, void *, s32);

/* Tick the actor's animation, and every 60 frames (0x3C) of the current script
 * step reset that step's timer and advance the actor's command script. */
void sub_080AC278(void *arg0) {
    u8 *actor = (u8 *)arg0;
    u8 *work = *(u8 **)(actor + 0x3C);
    sub_080AC9B4(work[0x244], work + 0x68);
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 0x3C) {
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb = (s32 *)0x08671BB0;
            _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}
