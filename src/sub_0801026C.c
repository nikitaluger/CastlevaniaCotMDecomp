s32 sub_080C3060(void *, void *, s32);
s32 sub_080C3100(void *, void *, s32);

extern u32 D_02021E80;
extern vu32 D_040000D4[];

#define DMA_COPY_CTRL 0x84000004
#define DMA_FILL_CTRL 0x85000004

/* Copy 16 bytes from the WRAM table at 0x02025358 to the SRAM destination in
 * D_02021E80, retrying with a RAM-resident verify routine up to 10 times; if
 * every attempt fails, zero the buffer and the destination instead. */
void sub_0801026C(void)
{
    u8 buffer[0x14];
    u32 result = 0;
    u32 dest = D_02021E80;
    u32 attempt;
    u32 sourceAddr = 0x02025358;
    vu32 *dmaRegs = D_040000D4;

    dmaRegs[0] = sourceAddr;
    dmaRegs[1] = (u32)buffer;
    dmaRegs[2] = DMA_COPY_CTRL;
    (void)dmaRegs[2];

    for (attempt = 0; attempt <= 9; attempt++) {
        sub_080C3060(buffer, (void *)dest, 0x10);
        result = sub_080C3100(buffer, (void *)dest, 0x10);
        if (result == 0) break;
    }

    if (result != 0) {
        *(u32 *)(buffer + 0x10) = 0;
        D_040000D4[0] = (u32)(buffer + 0x10);
        D_040000D4[1] = (u32)buffer;
        D_040000D4[2] = DMA_FILL_CTRL;
        (void)D_040000D4[2];
        sub_080C3060(buffer, (void *)dest, 0x10);
    }
}
