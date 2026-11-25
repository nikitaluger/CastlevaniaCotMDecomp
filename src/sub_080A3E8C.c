extern u16 sub_08005910(s32, s32);
extern void sub_080114DC(s32, s32, s16, s32);
struct S_02025FF0 { u8 _0[0x10]; u32 field10; u8 _14[0x14ED - 0x14]; u8 field14ED; u8 _14EE[0x173A - 0x14EE]; u8 field173A; u8 _173B[0x174C - 0x173B]; s32 f174C; s32 f1750; };
extern struct S_02025FF0 D_02025FF0;
struct S_A3E8C_2 { u8 _0[8]; s32 f8; s32 fC; };
struct S_A3E8C_3 { u32 f0; u32 f4; u32 f8; };
struct S_08101C60 { s16 v; u8 _pad[2]; };
extern struct S_08101C60 D_08101C60[];

static inline u32 addshift(u16 a, u16 b) { return (u32)((a + b) << 16); }

/* Drive an entity's animation toward a target frame, choosing a new direction
 * from its facing angle once the timer expires, or stepping one frame at a
 * time toward the goal. */
void sub_080A3E8C(s32 scene, s32 obj, struct S_A3E8C_2 *target, struct S_A3E8C_3 *state) {
    u16 angle;
    s16 signedAngle;
    u32 timer, frame, goalFrame;
    timer = state->f8 + 1; state->f8 = timer; frame = state->f0; goalFrame = state->f4;
    if (frame == goalFrame) {
        if (timer > 0x4A) {
            state->f8 = 0;
            angle = sub_08005910(D_02025FF0.f1750 - target->fC, D_02025FF0.f174C - target->f8);
            signedAngle = (s16)angle;
            if ((u32)((angle + 0xFFFFAFFF) << 16) <= 0x3FFE0000) state->f4 = 0;
            else if ((u32)((angle + 0xFFFFCFFF) << 16) <= 0x1FFF0000 ||
                     addshift((u16)signedAngle, 0x7000) <= 0x3FFF0000) state->f4 = 2;
            else state->f4 = 4;
        }
    } else if (timer > 0x27) {
        s16 animId;
        state->f8 = 0;
        if (goalFrame > frame) state->f0 = frame + 1; else state->f0 = frame - 1;
        animId = D_08101C60[state->f0].v;
        sub_080114DC(scene, obj, animId, 0);
    }
}
