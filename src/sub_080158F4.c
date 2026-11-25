extern void sub_080008A0(void *dst, s32 size);
extern u8 D_0201E3A0[];
extern s32 D_0201E8A0;

/* Resets the 0x500-byte scratch buffer at D_0201E3A0 to zero and clears the
 * word that sits right after it, at D_0201E8A0. */
void sub_080158F4(void) {
    D_0201E8A0 = 0;
    sub_080008A0(D_0201E3A0, 0x500);
}
