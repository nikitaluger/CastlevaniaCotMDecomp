/* On a successful interaction check, reverse the companion sprite's direction,
 * destroy the target, play the hit sounds and restart the script step. */
extern s32 checkAngularMotionHit(void *, u32);
extern void decelerateTargetX(void *, u32);
extern void sub_080AACCC(void *);
extern void sub_080C050C(s32);
extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallbacks;

struct S_02025FF0 {
    u8 _0[0x1754];
    s32 f1754;
};
extern struct S_02025FF0 gMainWorkspace;

struct Entity {
    u8 _0[0x18];
    u8 _1[0x22 - 0x18];
    s16 f22;
    u8 _2[0x38 - 0x24];
    u32 f38;
    u32 f3C;
};
struct SpriteState {
    u16 f0;
    u16 f2;
    u8 _0[0x2A - 4];
    u8 f2A;
};
struct ScriptState {
    u8 _0[0xEE];
    u8 fEE;
    u8 _1[0x184 - 0xEF];
    u32 f184;
};
struct ScriptStep {
    u8 _0[0x19];
    u8 f19;
};
struct Target { u8 _0[0x24]; u32 f24; };

void sub_080A7EA4(struct Entity *arg) {
    struct SpriteState *sprite;
    struct ScriptState *scriptState;
    struct Target *target;
    u32 stateArg, hit, newFlags;

    sprite = (struct SpriteState *)arg->f38;
    scriptState = (struct ScriptState *)arg->f3C;
    stateArg = (u32)scriptState + 0x48;
    if (!(((struct ScriptStep *)((u8 *)arg + arg->f22 * 2))->f19 & 2)) {
        newFlags = (0xFFF & sprite->f0) | 0xE000;
        sprite->f0 = newFlags;
    }
    hit = checkAngularMotionHit(arg, stateArg);
    decelerateTargetX(sprite, stateArg);
    if (hit == 0) return;
    sprite->f2A |= 0x10;
    sprite->f2 = sprite->f2 & 0xFCFF;
    scriptState->fEE = 3;
    sub_080AACCC(arg);
    target = *(struct Target **)((u8 *)scriptState + 0xC2 * 2);
    sub_080C31E0(target, target->f24);
    if (gMainWorkspace.f1754 <= 0x10) gMainWorkspace.f1754 = 0x11;
    sub_080C050C(0xC3 << 1);
    sub_08005E80(0xBC << 1);
    ((struct ScriptStep *)((u8 *)arg + arg->f22 * 2))->f19 = 0;
    {
        u32 *pb = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)arg + 0x18, (u8 *)arg + 0x22, *pb);
    }
}
