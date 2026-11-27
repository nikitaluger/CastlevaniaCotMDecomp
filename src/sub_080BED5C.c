extern void *spawnBudgetedEffect(void *, s32);

/* EWRAM scene/transition state: the current transition step and the saved
 * color/frame/display values used by the fade-in family. */
struct SceneState {
    u8 _0x000[0x125C];
    u32 v;
    u8 _pad0[0x1361 - 0x1260];
    u8 transitionStep;      /* 0x1361 */
    u8 _pad1[2];
    u16 savedColor;         /* 0x1364, from gCrossfadeGfxState+4 */
    u16 savedFrame;         /* 0x1366, from gCrossfadeGfxState+8 */
    u8 savedValue;          /* 0x1368, latched from 0x1458 */
    u8 savedArg;            /* 0x1369 */
    u8 _pad2[0x1458 - 0x136A];
    u8 displayValue;        /* 0x1458 */
};
extern struct SceneState gCameraState;

/* Gfx/effect state block: +4 highlight color, +8 frame counter. */
struct GfxState { u8 _0x000[4]; u16 color; u8 _pad[2]; u16 frame; };
extern struct GfxState gCrossfadeGfxState;

struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

void markType1DAObjects(void) {
    void *r5 = (void *)gMainWorkspace.v;
    void *r2 = *(void **)((u8 *)r5 + 0x30);
    while (r2 != 0) {
        if (*(s16 *)r2 == 0x1DA) {
            u16 *p = *(u16 **)((u8 *)r2 + 0x3C);
            *p |= 1;
        }
        r2 = *(void **)((u8 *)r2 + 0x2C);
    }
}

/* Start transition step 3: snapshot the effect color and frame counter, latch
 * the saved display value at 0x1458 into the transition block, clear its second
 * argument and restore the DISPCNT high byte (0xE3 = BG1-BG3, win/OBJ bits). */
void sub_080BED5C(void) {
    gCameraState.transitionStep = 3;
    gCameraState.savedColor = gCrossfadeGfxState.color;
    gCameraState.savedFrame = gCrossfadeGfxState.frame;
    gCameraState.savedValue = gCameraState.displayValue;
    gCameraState.savedArg = 0;
    *(vu8 *)0x04000005 = 0xE3;
}
