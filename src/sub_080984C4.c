extern s32 postDisplaySprite(s32, s32, s32, s32, s32);

/* Copy the 0x20-byte graphics blocks selected by the bits of blockMask into
 * two destination buffers: bits 0-3 come from one source table, bits 4-7 from
 * a second one. */
void sub_080984C4(s32 blockMask) {
    s32 src0;
    s32 src1;
    s32 dst0;
    s32 dst1;
    u32 bit0;
    u32 bit1;

    dst0 = 0x020213E0;
    src0 = 0x05000300;
    bit0 = 1;
    do {
        if (blockMask & bit0) {
            postDisplaySprite(1, dst0, src0, 0x20, 0x10);
        }
        dst0 += 0x20;
        src0 += 0x20;
        bit0 *= 2;
    } while (bit0 <= 0xFU);
    dst1 = 0x020214E0;
    src1 = 0x05000180;
    bit1 = 0x10;
    do {
        if (blockMask & bit1) {
            postDisplaySprite(1, dst1, src1, 0x20, 0x10);
        }
        dst1 += 0x20;
        src1 += 0x20;
        bit1 *= 2;
    } while (bit1 <= 0xFFU);
}
