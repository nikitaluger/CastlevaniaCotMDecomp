void sub_08097F70(s32 src, s32 block);

/* Decompress the LZ77 graphics set at 0x08440AA8 into VRAM screen block 0. */
void sub_080BE578(void) {
    sub_08097F70(0x08440AA8, 0);
}
