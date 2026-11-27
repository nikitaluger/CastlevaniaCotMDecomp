extern void copyBytes(void *, const void *, s32);
extern s32 divideInt(u8, s32);
extern s32 moduloInt(u8, s32);
extern void setLayerTilemap(s32, u16);
extern void sub_0805FEC8(u16);

/* Copies the 16-entry lookup table into a local buffer, sets background layer
 * 0's tilemap address at two offsets, and feeds two indices derived from `kind`
 * to the graphics-state initializer. */
void drawHudValue(u8 kind, u16 tileOffset) {
    u16 lookup[16];
    u8 kindCopy = kind;
    u16 offset = tileOffset;
    copyBytes(lookup, (const void*)0x080CAF88, 0x20);
    setLayerTilemap(0, offset);
    sub_0805FEC8(lookup[divideInt(kindCopy, 0x10)]);
    offset += 4;
    setLayerTilemap(0, offset);
    sub_0805FEC8(lookup[moduloInt(kindCopy, 0x10)]);
}
