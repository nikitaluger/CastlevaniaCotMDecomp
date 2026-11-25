/* Effect pool at 0x020279D0: +4 registry list head, +8 active-effect list head.
 * D_02020BC0 / D_02020BC8 are the registry cursor and its saved copy. */
struct EffectPool { u8 _pad[4]; s32 registryHead; s32 activeHead; };
extern struct EffectPool D_020279D0;
extern u32 D_02020BC0;
extern u32 D_02020BC8;

/* Rewind the registry cursor to the start of its list. */
void sub_080168A8(void) {
    u32 *cursor = &D_02020BC0;
    s32 head = D_020279D0.registryHead;
    *cursor = (u32)head;
    D_02020BC8 = (u32)head;
}
