/* Enemy AI tick: scale X/Y velocity by the current action byte and the state
 * angle, then test whether the enemy's heading and the direction to the
 * player line up. On a match, or when the action byte is 0x5A, clear the
 * action and invoke the action-change callback. */
extern s32 sub_08005910(s32, s32);
extern s32 sub_0801476C(s32, s32, s32);
extern void sub_080A845C(void *a, void *b);
extern void sub_080A8940(void *a, void *b);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *a, void *b, s32 c);

/* Shared player/camera position */
struct GlobalPos {
    u8 _0[0x174C];
    u32 y; /* +0x174C */
    u32 x; /* +0x1750 */
};
extern struct GlobalPos D_02025FF0;

/* State block reached from self+0x3C */
struct EnemyState {
    u8 _0[0xC4];
    s32 targetY;    /* +0xC4, also body+0x7C */
    s32 curX;       /* +0xC8 */
    u8 _CC[0xD8 - 0xCC];
    s32 curY;       /* +0xD8 */
    s32 targetX;    /* +0xDC */
    u8 _E0[0xEF - 0xE0];
    u8 effectFlag;  /* +0xEF */
    u8 _F0[0xFC - 0xF0];
    s32 velX;       /* +0xFC */
    s32 velY;       /* +0x100 */
    u8 _104[0x108 - 0x104];
    s32 angle;      /* +0x108 */
    u8 _10C[0x144 - 0x10C];
    s32 stateFlags; /* +0x144 */
};

/* Action byte for the current animation index (the s16 at self+0x22 picks a
 * 2-byte slot starting at self+0x19) */
#define ACTION(e) (*(u8 *)((s16)*(s16 *)(e + 0x22) * 2 + (u32)e + 0x19))

void sub_080A70F8(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    struct EnemyState *state = *(struct EnemyState **)(self + 0x3C);
    u8 *body = (u8 *)state + 0x48;
    s32 angle = state->angle;
    s32 otherAngle = angle - 0x4800;
    s32 tolerance;
    s32 *lookup;
    s32 *callback;
    s32 heading;
    s32 dx, dy;
    u8 zero;
    u8 *flagPtr;

    lookup = (s32 *)0x08671BFC;
    state->velX = (sub_080C31E0(angle - 0x800, *lookup) * (s32)ACTION(self)) >> 8;
    state->velY = (sub_080C31E0(otherAngle, *lookup) * (s32)ACTION(self)) >> 8;

    sub_080A8940(sprite, body);
    sub_080A845C(self, body);

    heading = sub_08005910(state->targetX - state->curX,
                           state->curY - *(s32 *)(body + 0x7C));
    tolerance = 0x400;

    dx = (s32)D_02025FF0.x - (state->targetX + *(s32 *)(self + 0x6C));
    dy = (s32)D_02025FF0.y - (state->curY + *(s32 *)(self + 0x5C));

    if (sub_0801476C(heading, tolerance, sub_08005910(dx, dy)) != 0) {
        state->stateFlags = (s32)ACTION(self) << 16;
        ACTION(self) = 0;
        callback = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }

    if (ACTION(self) == 0x5A) {
        state->stateFlags = 0x5A0000;
        flagPtr = (u8 *)state + 0xEF;
        zero = 0;
        *flagPtr = 1;
        ACTION(self) = zero;
        callback = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
}
