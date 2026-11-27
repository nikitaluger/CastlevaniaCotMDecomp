extern void copyBytes(void *, void *, u32);

struct S_02021E90_125C { u8 _0x000[0x125C]; u32 ready; };
extern struct S_02021E90_125C gCameraState;

/* Mark the graphics set as loaded and copy its 0x40-byte configuration table
 * from ROM into the workspace at +0x12E0. */
void sub_080B74C4(void) {
    gCameraState.ready = 1;
    copyBytes((u8*)&gCameraState + (0x97 << 5), (void*)0x08102D64, 0x40);
}
