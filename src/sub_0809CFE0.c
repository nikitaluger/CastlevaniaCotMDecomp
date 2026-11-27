/* Advance an entity's scripted motion: tick the periodic sound counter, rotate
 * the angle and count the timer down, recompute and apply its velocity, set the
 * view's facing flag, then run the per-frame motion callback. */
struct Motion { u8 _[0x2E]; u16 angle; s32 countdown; };
extern void advanceMotion(void *, s32);
extern void setPolarOffset(void *, u16, s32);
extern void sub_080148D8(s32, s32);
extern void sub_0809856C(s32, void *, s32);
extern void sub_0809E278(s32, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_0809CFE0(u8 *entity) {
    s32 view;
    u8 *body;
    u8 *bodyData;
    struct Motion *motion;
    s32 remaining;
    u8 *animState;
    s32 *animScript;

    view = *(s32 *)(entity + 0x38);
    body = *(u8 **)(entity + 0x3C);
    bodyData = body + 0x34;
    motion = (struct Motion *)(body + 0x48);
    sub_0809856C(0x16B, body + 0x8C, 0xF);
    motion->angle += 0x100;
    remaining = motion->countdown + (s32)0xFFFFF800;
    motion->countdown = remaining;
    if (remaining <= 0) {
        motion->countdown = 0;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        animScript = (s32 *)0x08671BB0;
        animState = entity + 0x18;
        sub_080C31E4(animState, entity + 0x22, *animScript);
    }
    setPolarOffset(body, motion->angle, motion->countdown);
    advanceMotion(body, 0);
    sub_080148D8(view, *(s32 *)(body + 8));
    sub_0809E278(view, bodyData, body, motion);
}
