extern void *D_02021E80;        /* pointer to the loaded record block */
extern u8 D_02025358[];         /* 0x10-byte header template */
void sub_080C2F88(void *dst, void *src, s32 size);

/* Copy the 0x10-byte header template into the block pointed to by
 * D_02021E80. */
void sub_08010250(void) {
    sub_080C2F88(D_02021E80, D_02025358, 0x10);
}
