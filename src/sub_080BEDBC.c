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
extern struct FadeState D_02021E90;

/* Gfx/effect state block: +4 highlight color, +8 frame counter. */
struct GfxTimers { u8 _0x000[4]; u16 color; u8 _pad[2]; u16 frame; };
extern struct GfxTimers D_03000830;

/* Start transition step 3 with fade argument 0x50: snapshot the effect color,
 * frame counter and saved display value, then restore the DISPCNT high byte. */
void sub_080BEDBC(void) {
    D_02021E90.transitionStep = 3;
    D_02021E90.savedColor = D_03000830.color;
    D_02021E90.savedFrame = D_03000830.frame;
    D_02021E90.savedValue = D_02021E90.displayValue;
    D_02021E90.savedArg = 0x50;
    *(vu8 *)0x04000005 = 0xE3;
}
