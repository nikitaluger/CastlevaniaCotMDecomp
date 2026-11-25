struct S_02021E90_609 {
    u8 pad0[0x143C];
    u8 f143C;
    u8 pad1[5];
    u8 side;
    u8 pad2[2];
    u8 f1445;
    u8 pad3[0xE];
    u8 *f1454;
};
extern struct S_02021E90_609 D_02021E90;
void sub_08060A50(u16 gfxId);
void sub_08060AD8(u16 gfxId);

/* Dispatch graphic/tile loading for the selected map-script side: side 0 uses
 * the combined 4bpp/2bpp loader, side 1 the plain 2bpp loader. */
void sub_08060A1C(u16 gfxId) {
    switch (D_02021E90.side) {
        case 0: sub_08060AD8(gfxId); break;
        case 1: sub_08060A50(gfxId); break;
    }
}
