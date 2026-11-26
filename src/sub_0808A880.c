extern void sub_08003740(void *, void *);
extern void sub_08005E80(s32);
extern void sub_08007E24(s32);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
struct SFF0 { u8 _0[0x1C]; u32 f1C; u8 _20[0x14B8]; u16 f14D8; u16 f14DA; u8 _14DC[0x278]; s32 f1754; };
extern struct SFF0 gMainWorkspace;

/* Runs a temporary entity: counts down its lifetime, and on expiry plays the
 * effects, bumps the global field to at least 5, writes the global state words
 * and destroys itself. While alive it rotates, integrates motion, steps its
 * timer and snaps to the grid. */
void sub_0808A880(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *component = *(u8 **)(entity + 0x6C);
    u8 *motion = component + 4;
    u8 *state = *(u8 **)(entity + 0x38);
    s16 *stateWords = (s16 *)state;
    struct SFF0 *base;
    u16 angle;
    s16 signedAngle;
    s32 remaining = *(s32 *)(motion + 0x10) - 1;
    *(s32 *)(motion + 0x10) = remaining;
    if (remaining == 0) {
        sub_08007E24(0x31);
        base = &gMainWorkspace;
        if (base->f1754 <= 4) base->f1754 = 5;
        base->f1C = 0x20;
        base->f14D8 = 0xFFF4;
        base->f14DA = 0x12;
        sub_08005E80(0x19F);
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        return;
    }
    angle = *(u16 *)(state + 4);
    signedAngle = stateWords[2];
    if (signedAngle > 0x100) {
        *(u16 *)(state + 4) = angle - 0x80;
        *(u16 *)(state + 6) = *(u16 *)(state + 6) - 0x80;
    }
    *(s32 *)(component + 4) = *(s32 *)(component + 4) + *(s32 *)(motion + 8);
    *(s32 *)(motion + 4) = *(s32 *)(motion + 4) + *(s32 *)(motion + 0xC);
    sub_08003740(component + 0x20, state);
    sub_0806D588(state, motion);
}
