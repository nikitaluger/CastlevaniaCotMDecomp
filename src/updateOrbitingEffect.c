extern s32 applyAreaEffectBehavior(void *, s32, void *);
extern void setSpriteScreenPosition(void *, void *);
extern s32 stepDelayTimer(void *, s32);
extern void spawnKind2CEntity(s32, s32, s32, s32);
extern void setDirectionVector(void *, u8);

#define ORBIT_PHASE_MASK      0x1FF
#define ORBIT_HALF_CYCLE      0x100
#define ORBIT_PHASE_BYTE_MASK 0xFF
#define ORBIT_STEP_SHIFT      4
#define ORBIT_RADIUS_BIAS     0x18
#define ORBIT_ROUND_BIAS      7
#define ORBIT_MOVE_SHIFT      3
#define ORBIT_PROJECTILE_KIND 0x0F
#define ORBIT_SPAWN_INTERVAL  0x10
#define ORBIT_STATE_IDLE      0x31

/* Partial view of the main workspace used by the orbiting effect. */
struct OrbitingEffectWorkspace {
    u8 _pad0[0x14ED];
    u8 actionState;                 /* 0x14ED */
    u8 _pad1[0x174C - 0x14EE];
    s32 scrollX;                    /* 0x174C: camera scroll rows, X */
    s32 scrollY;                    /* 0x1750: camera scroll rows, Y */
    u8 _pad2[0x18C2 - 0x1754];
    u16 gfxFlags;                   /* 0x18C2: sprite priority/blend flags */
};
extern struct OrbitingEffectWorkspace gMainWorkspace;

/* Advance an orbiting effect: bump its phase, compute a direction vector and a
 * target point from the camera scroll, glide its world position toward that
 * target, project it to screen space, tick its delay timer and periodically
 * fire a kind-0x0F projectile. */
void updateOrbitingEffect(void *actor) {
    u8 *work;
    s32 obj;
    u8 *state;
    struct OrbitingEffectWorkspace *ws;
    s32 phase, step, targetX, targetY, delta, x, y, timer;

    work = (u8 *)*(void **)((u8 *)actor + 0x6C) + 4;
    obj = *(s32 *)((u8 *)actor + 0x38);
    state = work;
    if (applyAreaEffectBehavior(actor, obj, state) != 0)
        return;
    timer = (*(s32 *)(state + 0x54) + 1) & 0xFF;
    *(s32 *)(state + 0x54) = timer;
    phase = (*(s32 *)(state + 0x58) + 1) & ORBIT_PHASE_MASK;
    *(s32 *)(state + 0x58) = phase;
    if (phase & ORBIT_HALF_CYCLE)
        step = (ORBIT_HALF_CYCLE - (phase & ORBIT_PHASE_BYTE_MASK)) >> ORBIT_STEP_SHIFT;
    else
        step = (phase & ORBIT_PHASE_BYTE_MASK) >> ORBIT_STEP_SHIFT;
    setDirectionVector(state, (u8)*(s32 *)(work + 0x54));

    ws = &gMainWorkspace;
    targetX = ws->scrollX + *(s32 *)(state + 8) * (step + ORBIT_RADIUS_BIAS);
    targetY = ws->scrollY + *(s32 *)(state + 0x0C) * (step + ORBIT_RADIUS_BIAS);

    x = *(s32 *)(state + 0);
    delta = targetX - x;
    if (delta < 0)
        delta += ORBIT_ROUND_BIAS;
    *(s32 *)(state + 0) = x + (delta >> ORBIT_MOVE_SHIFT);

    y = *(s32 *)(state + 4);
    delta = targetY - y;
    if (delta < 0)
        delta += ORBIT_ROUND_BIAS;
    *(s32 *)(state + 4) = y + (delta >> ORBIT_MOVE_SHIFT);

    setSpriteScreenPosition(obj, state);
    *(u16 *)obj = ws->gfxFlags;
    if (stepDelayTimer(work + 0x1C, obj) == 0) {
        ((void (*)(void *))(*(void **)((u8 *)actor + 0x24)))(actor);
        return;
    }
    timer = *(s32 *)(state + 0x10) - 1;
    *(s32 *)(state + 0x10) = timer;
    if (timer == 0) {
        spawnKind2CEntity(*(s32 *)((u8 *)actor + 0x28), ORBIT_PROJECTILE_KIND, *(s32 *)state, *(s32 *)(state + 0x04));
        *(s32 *)(state + 0x10) = ORBIT_SPAWN_INTERVAL;
    }
    if (ws->actionState != ORBIT_STATE_IDLE) {
        ((void (*)(void *))(*(void **)((u8 *)actor + 0x24)))(actor);
    }
}
