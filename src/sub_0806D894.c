extern u8 gMainWorkspace[];

/* End the current actor's control sequence: take its control block from the
 * workspace (+0x1724), clear the state timer and two flags (+0x9C, +0xA4,
 * +0xA8), then clear the global effect-state word at workspace+0x1810. */
void sub_0806D894(void) {
    u8 *workspace = gMainWorkspace;
    u8 *actor = *(u8 **)(workspace + 0x1724);
    *(u32 *)(actor + 0x9C) = 0;
    *(u32 *)(actor + 0xA4) = 0;
    *(u32 *)(actor + 0xA8) = 0;
    *(u32 *)(workspace + 0x1810) = 0;
}
