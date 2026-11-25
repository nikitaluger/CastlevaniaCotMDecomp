/* Track the mover and emit an effect; when it finishes, clear the step byte
 * and advance the script through the alternate callback table. */
extern s32 sub_08098754(s32);
extern void sub_080988B8(s32, s32);
extern void sub_080BB940(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_080BB010(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *work = *(void **)(actor + 0x3C);
    s32 mover = *(s32 *)(actor + 0x4C);
    s32 *advanceCb;
    sub_080BB940(work, mover);
    sub_080988B8(mover, *(s32 *)((u8 *)work + 8));
    if (sub_08098754(mover) != 0) {
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x17) = 0;
        advanceCb = (s32 *)0x08671BD8;
        sub_080C31E8(actor + 0x18, actor + 0x22, 0, *advanceCb);
    }
}
