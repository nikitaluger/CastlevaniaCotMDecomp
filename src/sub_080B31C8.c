extern void copyBytes(void *, void *, u32);

struct S_02021E90_125C { u8 _0x000[0x125C]; u32 ready; };
extern struct S_02021E90_125C gCameraState;

/* Clear the graphics-set loaded flag and copy its 0x40-byte configuration
 * table from ROM into the graphics workspace at +0x1320. */
void sub_080B31C8(void) {
    gCameraState.ready = 0;
    copyBytes((u8 *)&gCameraState + (0x99 << 5), (void *)0x0810294C, 0x40);
}
