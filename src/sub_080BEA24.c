extern void sub_080C2E68(void *, void *, u32);

struct S_02021E90_125C { u8 _0x000[0x125C]; u32 ready; };
extern struct S_02021E90_125C D_02021E90;

/* Mark the graphics set as loaded and copy its 0x40-byte configuration table
 * from ROM into the workspace at +0x12A0. */
void sub_080BEA24(void) {
    D_02021E90.ready = 1;
    sub_080C2E68((u8*)&D_02021E90 + (0x95 << 5), (void*)0x081032D8, 0x40);
}
