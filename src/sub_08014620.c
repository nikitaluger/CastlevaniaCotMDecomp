s32 sub_0808DC88(s32, s32, s32);
struct S_02025FF0_1728 { u8 _0x000[0x1728]; s32 layerBoundary; };
extern struct S_02025FF0_1728 gMainWorkspace;

/* Spawn the effect object at (x, y) with the low nibble of `flags`; bit 4
 * selects the layer on the far side of the stored boundary. Returns 1 when
 * x is past the boundary and -1 when it is not. */
s32 sub_08014620(s32 x, s32 y, u16 flags) {
    if (gMainWorkspace.layerBoundary < x) {
        sub_0808DC88(x, y, flags & 0xF);
        return 1;
    }
    sub_0808DC88(x, y, (flags & 0xF) | 0x10);
    return -1;
}
