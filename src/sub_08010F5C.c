/* Fill the 8-byte sprite-group descriptor desc from source entry: a nonzero
 * first halfword selects a frame group, whose frame data is copied/loaded from
 * frameTable; a zero halfword marks the group empty by setting flag bit 1. */
extern void sub_080111D0(s32 obj, s32 frameEntries, s32 gfxSrc, s32 gfxDst);
static inline u8 zero8(void) { return 0; }

void sub_08010F5C(s32 obj, u8 *desc, u8 *entry, s32 frameTable, s32 gfxSrc, s32 gfxDst, s32 groupFlags) {
    u32 baseTile;
    u8 flags;
    u8 zero;
    u32 z;

    flags = (u8)groupFlags;
    baseTile = *(u16 *)(entry + 0);
    z = 0;
    *(u16 *)(desc + 2) = (u16)baseTile;
    *(u32 *)(desc + 4) = z;
    *(u8 *)(desc + 1) = 1;
    *(u8 *)(desc + 0) = flags;
    baseTile <<= 16;
    if (baseTile == 0) {
        zero = zero8();
        *(u8 *)(desc + 1) = zero;
        *(u8 *)(desc + 0) = flags | 2;
        return;
    }
    sub_080111D0(obj, frameTable + (*(u16 *)(entry + 2) * 8), gfxSrc, gfxDst);
}
