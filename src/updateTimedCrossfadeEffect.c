extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern s32 divInt32(s32, s32);
extern void *spawnEntity(s32, s32, s32, s32);
extern void initCrossfadeGfxState(void);
extern void sub_080C31E0(void *, s32);
extern void stepDelayTimer(void *, void *);
extern void playSound(u16);
extern u8 gMainWorkspace[];
extern u16 gCrossfadeGfxState[];

/* Advances the crossfade timed effect by one frame: decrements its countdown
 * and rescales the sprite's two tile ids from the remaining ticks, drives the
 * hardware colour-blend register at the start and end of the count, spawns a
 * child on every fourth tick, and fires the actor's callback when the timer
 * runs out or a global cancel condition is set. Sibling of
 * updateTimedGraphicsEffect with a faster spawn cadence and different constants. */
void updateTimedCrossfadeEffect(void *effect)
{
    u8 *work = (u8 *)(*(u32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_WORK) + TIMED_EFFECT_WORK_HEADER);
    u8 *sprite = *(u8 **)((u8 *)effect + TIMED_EFFECT_ACTOR_SPRITE);
    u8 *data = work;
    s32 *words = (s32 *)data;
    s32 ticksLeft;
    s32 divisor;
    s32 fade;
    s32 off;
    s32 scaled;
    void *child;
    u8 *workspace;

    if (applyAreaSpecialBehavior(effect, sprite, data) > 0) {
        sub_080C31E0(effect, *(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_CB));
        return;
    }

    ticksLeft = words[4] - 1;
    words[4] = ticksLeft;
    divisor = TIMED_EFFECT_DIV_BASE;
    fade = TIMED_EFFECT_TIMER_MAX - ticksLeft;
    if (fade <= TIMED_EFFECT_NEAR_END) divisor = fade * 2;
    if (ticksLeft <= TIMED_EFFECT_EARLY_LIMIT) {
        off = TIMED_EFFECT_EARLY_BASE - ticksLeft;
        divisor = off * TIMED_EFFECT_EARLY_STEP + TIMED_EFFECT_DIV_BASE;
    }
    scaled = divInt32(TIMED_EFFECT_SCALE_NUM, divisor);
    *(s16 *)(sprite + TIMED_EFFECT_SPRITE_TILE0) = scaled;
    *(s16 *)(sprite + TIMED_EFFECT_SPRITE_TILE1) = scaled;
    if (words[4] > TIMED_EFFECT_FADE_HIGH) {
        u16 *fadeReg;
        divisor = (words[4] - TIMED_EFFECT_FADE_HIGH) >> 1;
        fadeReg = gCrossfadeGfxState;
        fadeReg[TIMED_EFFECT_GFX_REG_SLOT] = (u16)((divisor << 8) | (TIMED_EFFECT_FADE_HALF - divisor));
    }
    if (words[4] <= TIMED_EFFECT_FADE_LOW) {
        u16 *fadeReg;
        divisor = words[4] >> 1;
        fadeReg = gCrossfadeGfxState;
        fadeReg[TIMED_EFFECT_GFX_REG_SLOT] = (u16)(((TIMED_EFFECT_FADE_HALF - divisor) << 8) | divisor);
    }
    if ((words[4] & CROSSFADE_EFFECT_SPAWN_MASK) == 0) {
        child = spawnEntity(*(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_SPAWN),
                            CROSSFADE_EFFECT_SPAWN_KIND, CROSSFADE_EFFECT_SPAWN_A, CROSSFADE_EFFECT_SPAWN_B);
        if (child != NULL)
            *(s32 *)((u8 *)child + TIMED_EFFECT_CHILD_TIMER) = words[4] >> CROSSFADE_EFFECT_CHILD_SHIFT;
    }
    if (words[4] == 0) {
        initCrossfadeGfxState();
        sub_080C31E0(effect, *(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_CB));
        return;
    }
    workspace = gMainWorkspace;
    *(u16 *)sprite = *(u16 *)(workspace + TIMED_EFFECT_WS_GFX_FLAGS);
    stepDelayTimer(work + TIMED_EFFECT_DELAY_TIMER, sprite);
    words[5] -= 1;
    if (words[5] == 0) {
        playSound(CROSSFADE_EFFECT_TICK_SFX);
        words[5] = CROSSFADE_EFFECT_SFX_PERIOD;
    }
    if (*(u8 *)(workspace + TIMED_EFFECT_WS_CANCEL) == TIMED_EFFECT_WS_CANCEL_VAL ||
        (*(u8 *)(workspace + TIMED_EFFECT_WS_STATE) == 0 && *(s32 *)(workspace + TIMED_EFFECT_WS_ACTIVE) != 0))
        sub_080C31E0(effect, *(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_CB));
}
