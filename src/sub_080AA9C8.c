struct GfxInit {
    u8 unused0;
    u8 unused1;
    u16 unused2;
    u32 unused4;
    u32 dataPtr;
    u16 counter;
    u16 index;
    u32 vramAddr;
};

extern void sub_0801147C(void *obj, struct GfxInit *init, u32 dataPtr,
                         u32 vramAddr, s32 allocUnits);

/* Initialise graphics slot `init` from the sprite-template table at
 * 0x081021A8: upload template `index` (0x20-byte entries) to the VRAM block
 * at 0x06014000 and allocate `allocUnits` units of work buffer. */
void sub_080AA9C8(void *obj, struct GfxInit *init, s32 index, s32 allocUnits) {
    sub_0801147C(obj, init, 0x081021A8, (index << 5) + 0x06014000, allocUnits);
}
