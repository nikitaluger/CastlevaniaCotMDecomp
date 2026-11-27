extern void stepAnimationTrack(void *, void *);
extern void sub_08014460(void *);
extern s32 sub_08005910(s32, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

/* Large runtime state block (BSS): holds the player/target position near its end. */
struct GameGlobals { u8 _0[0x174C]; u32 playerX; u32 playerY; };
extern struct GameGlobals gMainWorkspace;

/* Per-entity motion state reached through the +0x3C pointer. */
struct MotionState {
    u8 _0[8];
    u32 posX;       /* 0x08 */
    u32 posY;       /* 0x0C */
    u8 _10[0x18];
    u8 *subState;   /* 0x28 */
    u8 _2C[8];
    u8 status;      /* 0x34, tested against bit 2 */
};

/* One slot of the per-entity array indexed by the +0x22 halfword. */
struct SlotState { u8 _0[0x18]; u8 f18; u8 timer; };

/* An entity that owns a motion state and a slot index. */
struct EntityObj {
    u8 _0[0x22];
    s16 slotIndex;
    u8 _24[0x14];
    u32 animHandle;
    struct MotionState *state;
};

/* Advance a chasing entity: refresh its animation/status, relink it into the
 * active list, set sub-state bytes, aim its motion at the player, reset its
 * slot timer, then dispatch the callback from the pointer table. */
void sub_0804039C(struct EntityObj *entity) {
    struct MotionState *state;
    u8 *status;
    struct GameGlobals *globals;
    s32 angle;
    u32 animHandle;
    u8 zero;
    u8 *subState;

    animHandle = entity->animHandle;
    state = entity->state;
    status = (u8 *)state + 0x34;
    stepAnimationTrack((void *)animHandle, status);
    if ((*status & 2) == 0) return;
    sub_08014460(entity);
    subState = state->subState;
    zero = 0;
    subState[2] = 8;
    state->subState[3] = 1;
    globals = &gMainWorkspace;
    angle = sub_08005910(globals->playerY - state->posY, globals->playerX - state->posX);
    sub_080146D0(state, angle, 0x30000);
    ((struct SlotState *)((u8 *)entity + entity->slotIndex * 2))->timer = zero;
    {
        void **fn = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *fn);
    }
}
