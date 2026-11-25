extern void sub_080C2E68(void *, void *, u32);

struct S_02021E90_125C { u8 _0x000[0x125C]; u32 ready; };
extern struct S_02021E90_125C D_02021E90;

/* Clear the graphics-set loaded flag and copy its 0x40-byte configuration
 * table from ROM into the graphics workspace at +0x1320. */
void sub_080B31C8(void) {
    D_02021E90.ready = 0;
    sub_080C2E68((u8 *)&D_02021E90 + (0x99 << 5), (void *)0x0810294C, 0x40);
}
