void sub_08062394(u8, u8);

/* Uploads the object's pending sprite graphic (index at +0x1C) when bits 0-1
 * of its graphics word are set or its owner's flag bit 0 is set; bit 0x20 of
 * the word records that the load has been done. */
void sub_080142C0(u8 *self, u8 *owner) {
    u16 *gfx = *(u16 **)(self + 0x3C);
    if (gfx == 0 || owner == 0) return;
    if ((*gfx & 0x20) != 0) return;
    if ((*gfx & 3) == 0 && (*(u16 *)(owner + 0x14) & 1) == 0) return;
    *gfx = *gfx | 0x20;
    sub_08062394(0, *(u8 *)((u8 *)gfx + 0x1C));
}
