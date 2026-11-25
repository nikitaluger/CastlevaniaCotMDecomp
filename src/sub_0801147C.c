extern s32 sub_080111B0(s32);

/* Graphics/animation state used by object constructors. Field 0x08 holds a ROM
 * data pointer, 0x10 a VRAM address; an 8-byte-unit buffer is also allocated
 * from heap 0 and its pointer stored at obj+0x24. */
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

void sub_0801147C(void *obj, struct GfxInit *init, u32 dataPtr, u32 vramAddr, s32 allocUnits) {
    init->dataPtr = dataPtr;
    init->counter = 0;
    init->index = 0xFFFF;
    init->vramAddr = vramAddr;
    init->unused0 = 0;
    init->unused1 = 0;
    init->unused2 = 0;
    init->unused4 = 0;
    *(u32 *)((u8 *)obj + 0x24) = sub_080111B0(allocUnits);
}
