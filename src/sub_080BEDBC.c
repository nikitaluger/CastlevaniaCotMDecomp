/* Fade/transition state block in EWRAM: current step at 0x1361 and the saved
 * color/frame/display values used by the fade family. */
struct FadeState {
    u8 _0x000[0x125C];
    u32 v;
    u8 _pad0[0x1361 - 0x1260];
    u8 transitionStep;
    u8 _pad1[2];
    u16 savedColor;
    u16 savedFrame;
    u8 savedValue;
    u8 savedArg;
    u8 _pad2[0x1458 - 0x136A];
    u8 displayValue;
};
extern struct FadeState gCameraState;

/* Gfx/effect state block: +4 highlight color, +8 frame counter. */
struct GfxTimers { u8 _0x000[4]; u16 color; u8 _pad[2]; u16 frame; };
extern struct GfxTimers D_03000830;

/* Start transition step 3 with fade argument 0x50: snapshot the effect color,
 * frame counter and saved display value, then restore the DISPCNT high byte. */
void sub_080BEDBC(void) {
    gCameraState.transitionStep = 3;
    gCameraState.savedColor = D_03000830.color;
    gCameraState.savedFrame = D_03000830.frame;
    gCameraState.savedValue = gCameraState.displayValue;
    gCameraState.savedArg = 0x50;
    *(vu8 *)0x04000005 = 0xE3;
}
