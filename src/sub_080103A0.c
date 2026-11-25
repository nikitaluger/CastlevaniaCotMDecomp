extern void sub_080102F0(u8 slot);
extern void sub_08010320(u8 slot);

/* Copy the save slot `srcSlot` into the working save buffer, then write that
 * buffer into slot `dstSlot` (duplicating a save file). */
void sub_080103A0(u8 srcSlot, u8 dstSlot) {
    sub_080102F0(srcSlot);
    sub_08010320(dstSlot);
}
