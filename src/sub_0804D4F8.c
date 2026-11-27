extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern s32 sub_080C36E4(s32, s32);

struct S_3C_b { u8 _0[8]; s32 f08; s32 f0C; };
struct S_A0_b {
    u8 _0[0x22];
    s16 f22;
    u8 _24[0x14];
    void *f38;
    struct S_3C_b *f3C;
};
struct Sub { u8 _0[0x18]; u8 f18; u8 f19; };
struct S_02025FF0_189C { u8 _0[0x189C]; u32 w; };
extern struct S_02025FF0_189C gMainWorkspace;
extern void *gScriptStepCallbacks;

// Sets frame 0 and fires a step callback when this entity's position-derived phase matches the global phase.
void sub_0804D4F8(struct S_A0_b *obj) {
    struct S_3C_b *physics;
    void *sprite;
    s32 xPhase, yPhase, phase, phaseMod;

    sprite = obj->f38;
    physics = obj->f3C;
    setAnimationFrame(sprite, (u8 *)physics + 0x34, 0, 0);
    xPhase = physics->f08 / 0x10000;
    yPhase = (physics->f0C * 3) / 0x10000;
    phase = xPhase + yPhase;
    phaseMod = sub_080C36E4(phase, 0x14A);
    if (sub_080C36E4(gMainWorkspace.w, 0x14A) == phaseMod) {
        ((struct Sub *)((u8 *)obj + obj->f22 * 2))->f19 = 0;
        {
            void **fn = &gScriptStepCallbacks;
            sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 1, *fn);
        }
    }
}
