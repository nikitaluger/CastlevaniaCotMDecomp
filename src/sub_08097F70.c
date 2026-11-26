extern s32 decompressToVram(s32, s32);

/* Decompress the graphics data at src into VRAM, selecting the destination
 * screen block (0x800-byte slot from 0x06014000) with the low byte of block. */
void sub_08097F70(s32 src, s32 block) {
    decompressToVram(src, ((u32) (block << 0x18) >> 0xD) + 0x06014000);
}
