extern void sub_08097DF8(s32 song);
struct S_12B4 { u8 pad[0x12B4]; u32 v; };
extern struct S_12B4 D_02021E90;

/* Fill the backdrop palette with the solid colour 0x7C (BGR555 0xBE<<1) and
 * start song 0x0841FBA4. */
void sub_080BEA50(void) {
    u16 color;
    u16 *colorPtr = &color;
    vu32 *dma;
    *colorPtr = 0xBE << 1;
    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)colorPtr;
    dma[1] = D_02021E90.v;
    dma[2] = 0x81001000;
    (void)dma[2];
    sub_08097DF8(0x0841FBA4);
}
