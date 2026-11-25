extern s32 sub_08005910(s32, s32);
extern void sub_08011368(s32, void *, s32, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Large runtime state block: holds the player/target position near its end. */
struct GameGlobals { u8 _0[0x174C]; u32 playerX; u32 playerY; };
extern struct GameGlobals D_02025FF0;

/* Per-entity motion state reached through the entity's +0x3C pointer. */
struct MotionState {
    u8 _0[8];
    u32 posX;      /* 0x08 */
    u32 posY;      /* 0x0C */
    u8 _10[0x18];
    u8 *subState;  /* 0x28 */
    u8 _2C[8];
    u8 status;     /* 0x34, bit 2 = animation finished */
};

/* One slot of the per-entity array indexed by the +0x22 halfword. */
struct SlotState { u8 _0[0x18]; u8 f18; u8 timer; };

/* An entity that owns an animation handle and a motion state. */
struct EntityObj {
    u8 _0[0x22];
    s16 slotIndex;             /* 0x22 */
    u8 _24[0x14];
    u32 animHandle;            /* 0x38 */
    struct MotionState *state; /* 0x3C */
};

/* When the entity's animation 0xD finishes, aim its motion at the player at
 * speed 0x0C000, clear its slot timer and advance the script step. */
void sub_0805B1E4(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 animHandle = *(s32 *)(self + 0x38);
    struct MotionState *state = *(struct MotionState **)(self + 0x3C);
    u8 *status = (u8 *)state + 0x34;
    s32 a, b;
    s32 result;
    s32 *lit;

    sub_08011368(animHandle, status, 0xD, 0);
    if (*status & 2) {
        a = D_02025FF0.playerY - state->posY;
        b = D_02025FF0.playerX - state->posX;
        result = sub_08005910(a, b);
        sub_080146D0(state, result, 0xC000);
        ((struct SlotState *)(self + *(s16 *)(self + 0x22) * 2))->timer = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
