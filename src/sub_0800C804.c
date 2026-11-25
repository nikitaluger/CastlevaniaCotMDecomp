extern void sub_080C2E68(void *, const void *, s32);
extern s32 sub_080C2F20(u8, s32);
extern s32 sub_080C2F24(u8, s32);
extern void sub_0805FE28(s32, u16);
extern void sub_0805FEC8(u16);

/* Copies the 16-entry lookup table into a local buffer, sets background layer
 * 0's tilemap address at two offsets, and feeds two indices derived from `kind`
 * to the graphics-state initializer. */
void sub_0800C804(u8 kind, u16 tileOffset) {
    u16 lookup[16];
    u8 kindCopy = kind;
    u16 offset = tileOffset;
    sub_080C2E68(lookup, (const void*)0x080CAF88, 0x20);
    sub_0805FE28(0, offset);
    sub_0805FEC8(lookup[sub_080C2F20(kindCopy, 0x10)]);
    offset += 4;
    sub_0805FE28(0, offset);
    sub_0805FEC8(lookup[sub_080C2F24(kindCopy, 0x10)]);
}
