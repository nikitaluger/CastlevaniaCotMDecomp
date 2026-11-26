extern void sub_080C2E68(void *, void *, u32);

struct S_02021E90_125C { u8 _0x000[0x125C]; u32 ready; };
extern struct S_02021E90_125C gCameraState;

/* Mark this graphics set as loaded, then copy its 0x40-byte configuration
 * table from ROM into the graphics workspace at +0x12E0. */
void sub_080A04B4(void) {
    gCameraState.ready = 1;
    sub_080C2E68((u8*)&gCameraState + (0x97 << 5), (void*)0x08101A10, 0x40);
}
