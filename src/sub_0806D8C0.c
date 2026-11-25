extern u8 D_02025FF0[];

/* Clear the current actor's state timer (actor+0x9C) and reset the global
 * effect-state word at workspace+0x180C. */
void sub_0806D8C0(void) {
    u8 *workspace = D_02025FF0;
    *(u32 *)(*(u32 *)(workspace + 0x1724) + 0x9C) = 0;
    *(u32 *)(workspace + 0x180C) = 0;
}
