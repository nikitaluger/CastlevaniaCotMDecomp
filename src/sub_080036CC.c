/* Initialize the display/effect engine: point the two sprite-cursor words at
 * their IWRAM buffers and clear their first entries, reset the list counters
 * and the word/halfword state block, install the two 0x80-byte sprite buffers,
 * set the shared display byte to 7 and re-initialise the graphics state. */
void sub_080036CC(void) {
    *(s32 *)0x03000C84 = 0x03002704;   /* sprite cursor A -> its buffer */
    *(s32 *)0x030026A4 = 0x03002920;   /* sprite cursor B -> its buffer */
    sub_08003638(0, 0);                /* clear the first entry of both */
    *(s32 *)0x03002918 = 0;            /* list state word */
    *(s32 *)0x03002E30 = 0;            /* list state word */
    sub_08003650(0, 0, 0, 0, 0, 0);    /* 3 words + 3 halfwords of state */
    sub_0800368C(0x03000C90, 0x80, 0x03002710, 0x03002290, 0x80);
    sub_080036C0(7);                   /* shared display byte */
    sub_08003534();                    /* re-init graphics state */
}
