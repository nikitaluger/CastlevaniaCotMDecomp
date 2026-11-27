struct S02025FF0 { u8 _0[0x14A8]; u32 f14A8; u32 f14AC; };
extern struct S02025FF0 gMainWorkspace;
struct S03000830 { u8 _0[4]; u16 f4; u16 f6; };
extern struct S03000830 gCrossfadeGfxState;
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

extern void sub_08005E80(u16);
extern void resetActionResultState(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806C6B0(u8 *, u8 *, u8 *, u8 *);
extern void sub_080C31E4(u8 *, u8 *, u32);

/* Draw an object's sprite within the graphics pass; in one particular scene
 * state also update the display setup, play a sound and advance its script. */
void sub_08069A2C(u8 *obj) {
    struct S02025FF0 *state;
    u8 *gfxData;
    u8 *sprite;
    u32 worldBase;
    u32 *table;
    u32 zero;

    gfxData = *(u8 **)(obj + 0x6C) + 4;
    sprite = *(u8 **)(obj + 0x38);
    resetActionResultState(obj, sprite, gfxData, gfxData);

    state = &gMainWorkspace;
    if (state->f14AC == 3) {
        struct S03000830 *display = &gCrossfadeGfxState;
        display->f4 = 0x1542;
        display->f6 = 0x1010;
        zero = 0;
        worldBase = (u32)gCameraState;
        *(u32 *)(worldBase + 0x12BC) = 0x80 << 17;
        *(u16 *)(worldBase + 0x12A0) &= 0xBFFF;
        state->f14A8 = 0;
        sub_08005E80(0xDD << 1);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        table = &gMainObjTimerCallbacks;
        sub_080C31E4(obj + 0x18, obj + 0x22, *table);
    }
    sub_0806C6B0(obj, sprite, gfxData, gfxData);
}
