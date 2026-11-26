extern void sub_08003740(void *timer, void *gfx);
extern void sub_08005E80(s32 resourceId);
extern void sub_08007E24(s32 flag);
extern void sub_0806D588(void *gfx, void *state);
extern void sub_080C31E4(void *scriptData, void *scriptIndex, s32 handler);
extern s32 sub_080C364C(s32 dividend, u8 divisor);

struct S_02025FF0 { u8 _0[0x1C]; s32 globalEffect; };
extern struct S_02025FF0 gMainWorkspace;

/* Steps an effect actor: advances its timer and animation phase, fires a script
 * command when the phase wraps, then updates the sprite scale, flag and screen position. */
void sub_0808AE3C(u8 *actor) {
    u8 *work;
    u8 *gfx;
    u8 *state;
    u8 *phase;
    s32 nextPhase;
    s32 scale;

    work = *(u8 **)(actor + 0x6C);
    gfx = *(u8 **)(actor + 0x38);
    state = work + 4;
    *(s32 *)(state + 0x2C) = *(s32 *)(state + 0x2C) + 1;
    sub_08003740(work + 0x20, gfx);

    phase = work + 0x34;
    nextPhase = *phase + 1;
    *phase = nextPhase;
    if ((u8)nextPhase > 0x0F) {
        *phase = 0x10;
        sub_08005E80(0x1C0);
        gMainWorkspace.globalEffect = 0x80;
        sub_08007E24(0x34);
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *handler = (s32 *)0x08671BB0;
            sub_080C31E4(actor + 0x18, actor + 0x22, *handler);
        }
    }

    scale = sub_080C364C(0x10, *phase);
    *(u16 *)(gfx + 4) = scale << 8;

    if (*(s32 *)(state + 0x2C) & 2) {
        *(u8 *)(gfx + 0x2A) = *(u8 *)(gfx + 0x2A) | 0x40;
    } else {
        *(u8 *)(gfx + 0x2A) = *(u8 *)(gfx + 0x2A) & 0xBF;
    }
    sub_0806D588(gfx, state);
}
