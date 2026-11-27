void sub_080BB984(void *, void *);
void sub_080C31E4(void *, void *, s32);

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

void sub_080BAF88(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r0 = *(void **)(self + 0x3C);
    sub_080BB984(r0, (u8 *)r0 + 0x48);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xF0) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *nv;
            nv = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}

void sub_080BEDBC(void) {
    gCameraState.transitionStep = 3;
    gCameraState.savedColor = gCrossfadeGfxState.color;
    gCameraState.savedFrame = gCrossfadeGfxState.frame;
    gCameraState.savedValue = gCameraState.displayValue;
    gCameraState.savedArg = 0x50;
    *(vu8 *)0x04000005 = 0xE3;
}

/* Start transition step 3 with argument 0x48: snapshot the effect color and
 * frame counter, latch the display value, and restore the control byte. */
void sub_080BEE14(void) {
    gCameraState.transitionStep = 3;
    gCameraState.savedColor = gCrossfadeGfxState.color;
    gCameraState.savedFrame = gCrossfadeGfxState.frame;
    gCameraState.savedValue = gCameraState.displayValue;
    gCameraState.savedArg = 0x48;
    *(vu8 *)0x04000005 = 0xE3;
}

void sub_080BEF60(void) {
    u8 *base = (u8 *)&gCameraState;
    u32 r2;
    base[0x1361] = 7;
    r2 = base[0x1364];
    base[0x1366] = r2;
    base[0x1367] = base[0x1365];
    if ((r2 << 24) == 0)
        *(vu8 *)0x04000005 = 0xE2;
    else
        *(vu8 *)0x04000005 = r2 - 1;
}
