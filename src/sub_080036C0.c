/* Set the shared display-engine mode byte at 0x030026A0. The engine initialiser
 * writes 7 here; the sprite and effect spawners switch it to 0x0A. */
void sub_080036C0(s8 mode) {
    *(s8 *)0x030026A0 = mode;
}
