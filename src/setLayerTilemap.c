extern u8 gCameraState[];

/* Set a background layer's VRAM tilemap address from a layer index and tile
 * offset, recording the parameters and writing the address to three slots. */
void setLayerTilemap(u8 layer, u16 tileOffset) {
    u8 *gfxState = gCameraState;
    u32 *addr0;
    u32 vramAddr;

    *(u8 *)(gfxState + 0x1438) = layer;
    *(u16 *)(gfxState + 0x143E) = tileOffset;

    addr0 = (u32 *)(gfxState + 0x1448);
    vramAddr = ((*(u16 *)(gfxState + layer * 0x40 + 0x1262) & 0x0C) << 12) + (tileOffset << 5) + 0x06000000;
    *addr0 = vramAddr;
    *(u32 *)(gfxState + 0x144C) = vramAddr;
    *(u32 *)(gfxState + 0x1450) = vramAddr;
}
