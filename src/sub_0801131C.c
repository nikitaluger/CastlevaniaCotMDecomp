/* Graphics/animation state used by object constructors. Field 0x08 holds a ROM
 * data pointer, 0x10 a VRAM address. */
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

/* Two separately-materialized zeros: agbcc keeps the byte zero and the
 * half/word zero in different registers, which this function's code needs. */
struct Zero { u32 word; u8 byte; };

/* Points a freshly created sprite at the given animation descriptor, clears its
 * graphics state, and installs the descriptor's update callback at sprite+0x24. */
void sub_0801131C(void *sprite, struct GfxInit *init, u8 *desc) {
    struct Zero zero = {0, 0};
    register u8 byteZero;
    register u32 wordZero;
    init->dataPtr = (u32)desc;
    byteZero = zero.byte;
    wordZero = zero.word;
    init->counter = wordZero;
    init->index = 0xFFFF;
    init->vramAddr = wordZero;
    init->unused0 = byteZero;
    init->unused1 = byteZero;
    init->unused2 = wordZero;
    init->unused4 = wordZero;
    *(u32 *)((u8 *)sprite + 0x24) = *(u32 *)(desc + 4);
}
