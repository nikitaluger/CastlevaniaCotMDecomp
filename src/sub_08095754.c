extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080918B0(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern s32 sub_080C36E4(s32, s32);

/* Global frame counter; this system reads it at offset 0x1898 to phase effects. */
struct FrameState { u8 pad[0x1898]; s32 value; };
extern struct FrameState gMainWorkspace;

/* Spawns a visual effect around an entity's origin using fixed-point sine
 * phases and a frame-driven spread, then removes the entity once its indexed
 * state counter passes 0x20. */
void sub_08095754(u8 *entity) {
    u8 *origin;
    s32 posX;
    s32 posY;
    s32 frame, frameParity;
    s32 rounded;
    s32 frameMod4;
    s32 posYFinal;
    s32 spreadX;
    s32 spreadY;
    s32 sine, spread;

    origin = *(u8 **)(entity + 0x3C);
    posX = *(s32 *)(origin + 0) + (sub_0800583C(0x10000) << 4);
    posY = *(s32 *)(origin + 4) + sub_0800583C(0x10000) * 14;
    frame = gMainWorkspace.value;
    rounded = frame;
    if (frame < 0) rounded = frame + 3;
    frameMod4 = frame - ((rounded >> 2) << 2);
    posYFinal = posY + ((frameMod4 - 1) * 3) * 0x80000 + 0x180000;
    sine = sub_08005820(0x2000);
    spread = sub_080C36E4(gMainWorkspace.value, 5) - 2;
    spreadX = (sine + 0x4000) * spread;
    spreadY = 0x8000 - sub_08005820(0x20000);
    frameParity = gMainWorkspace.value;
    if ((frameParity & 1) == 0) {
        sub_080918B0(posX, posYFinal, spreadX, spreadY, 0x16C1,
            (s16)(((s32)(frameParity + (s32)((u32)frameParity >> 31)) >> 1) - (((((s32)(frameParity + (s32)((u32)frameParity >> 31)) >> 1) + (s32)((u32)(frameParity + (s32)((u32)frameParity >> 31)) >> 31)) >> 1) << 1) + 1));
        sub_0808DBF8(posX, posYFinal, 8);
    }
    if ((u32)*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) > 0x20) {
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
    }
}
