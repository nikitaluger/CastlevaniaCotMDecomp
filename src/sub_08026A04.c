/* Return 1 when every occupied slot (0..4) in the owner's graphics-manager
 * table has bit 0x20 set in its flags at +0x64, or 0 on the first occupied
 * slot without that bit. */
s32 sub_08026A04(void *owner) {
    u32 *work = *(u32 **)((u8 *)owner + 0x3C);
    s32 slotIndex = 0;
    u32 flagMask = 0x20;
    u32 *slotPtr = work + 0x1A;
    do {
        u32 *entry = (u32 *)*slotPtr;
        if (entry != 0) {
            if ((*(u16 *)((u8 *)entry + 0x64) & (u16)flagMask) == 0)
                return 0;
        }
        slotPtr++;
        slotIndex++;
    } while (slotIndex <= 4);
    return 1;
}
