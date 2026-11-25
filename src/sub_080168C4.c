/* Effect pool at 0x020279D0: +4 registry list head, +8 active-effect list head.
 * D_02020BC4 / D_02020BCC are the active-effect cursor and its saved copy. */
struct EffectPool { u8 _pad[4]; s32 registryHead; s32 activeHead; };
extern struct EffectPool D_020279D0;
extern s32 D_02020BC4;
extern s32 D_02020BCC;

/* Rewind the active-effect cursor to the start of its list. */
void sub_080168C4(void) {
    s32 *cursor = &D_02020BC4;
    s32 head = D_020279D0.activeHead;
    *cursor = head;
    D_02020BCC = head;
}
