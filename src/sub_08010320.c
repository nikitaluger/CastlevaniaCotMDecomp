extern s8 sub_08010490(void *a);
extern void sub_080C3060(void *a, void *b, s32 c);
extern s32 sub_080C3100(void *a, void *b, s32 c);
extern u8 *D_02021E80;
extern u8 gGameStatus[];
extern vu32 D_040000D4[];

/* Copies the 0x3D0-byte data block at gGameStatus into a stack buffer, writes
 * its checksum to byte 9, then copies/verifies it into slot arg0 of the
 * D_02021E80 table, retrying up to ten times. */
void sub_08010320(u8 slot)
{
    u8 block[0x3D0];
    u8 **slotTable = &D_02021E80;
    u32 offset = ((slot * 0xF) * 4 + slot) * 0x10;
    u8 *dst;
    vu32 *dma;
    u8 *src;
    u32 attempt;

    offset += 0x10;
    dst = *slotTable + offset;

    src = gGameStatus;
    dma = D_040000D4;
    dma[0] = (u32)src;
    dma[1] = (u32)block;
    dma[2] = 0x840000F4;
    dma[2];

    block[9] = sub_08010490(block);

    attempt = 0;
    while (attempt <= 9) {
        sub_080C3060(block, dst, 0x3D0);
        if (sub_080C3100(block, dst, 0x3D0) == 0)
            break;
        attempt++;
    }
}
