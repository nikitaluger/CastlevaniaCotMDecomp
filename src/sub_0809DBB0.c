/* Drive an entity's animation from a target object's state: tick the sound
 * counter, then on states 2 or 0 reset its pose and frame data and run the
 * matching animation command. */
struct Motion { u8 _0[8]; s32 offset; u8 _C[1]; u8 flag; u8 _E[0x28 - 0x0E]; s32 target; };
struct Body { u8 _0[0x0C]; s32 position; u8 _10[0x28 - 0x10]; u8 *target; };

extern void copyPoseAttrs(void *, s32);
extern void sub_0808BB54(void);
extern void sub_0809856C(s32, void *, s32);
extern void sub_0809E300(s32, s32, void *);
extern s32 sub_080A041C(s32);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_0809DBB0(u8 *entity) {
    s32 view;
    struct Body *body;
    u8 *bodyData;
    struct Motion *motion;
    s32 state;
    u8 *animState;
    s32 *animScript;

    view = *(s32 *)(entity + 0x38);
    body = (struct Body *)*(u8 **)(entity + 0x3C);
    bodyData = (u8 *)body + 0x34;
    motion = (struct Motion *)((u8 *)body + 0x48);
    sub_0809856C(0xB7 << 1, (u8 *)body + 0x8C, 0xC);
    if (sub_080A041C(motion->target) == 2) {
        motion->flag = 0;
        body->position = motion->offset + 0x220000;
        *(u8 *)((u8 *)body->target + 1) = 0;
        sub_0809E300(view, (s32)bodyData, motion);
    }
    state = sub_080A041C(motion->target);
    if (state == 0) {
        *((u8 *)body->target + 1) = 5;
        copyPoseAttrs((u8 *)body->target, 0x081019A4);
        sub_0808BB54();
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = state;
        animScript = (s32 *)0x08671BD0;
        animState = entity + 0x18;
        sub_080C31E8(animState, entity + 0x22, 2, *animScript);
    }
}
