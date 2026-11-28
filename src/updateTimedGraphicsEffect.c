extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern s32 divInt32(s32, s32);
extern void *spawnEntity(s32, s32, s32, s32);
extern void initCrossfadeGfxState(void);
extern void sub_080C31E0(void *, s32);
extern void stepDelayTimer(void *, void *);
extern void playSound(u16);
extern u8 gMainWorkspace[];
extern u16 gCrossfadeGfxState[];

/* Advances a timed graphics effect by one frame: decrements its countdown and
 * rescales the sprite's two tile ids from the remaining ticks, drives the
 * crossfade register at the start and end of the count, spawns a child on every
 * eighth tick, and invokes the actor's callback when the timer runs out or a
 * global cancel condition is set. */
void updateTimedGraphicsEffect(void *effect)
{
    void *work = (void *)(*(u32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_WORK) + TIMED_EFFECT_WORK_HEADER);
    void *sprite = *(void **)((u8 *)effect + TIMED_EFFECT_ACTOR_SPRITE);
    u32 *timerWords = (u32 *)work;
    s32 ticksLeft;
    s32 divisor;
    s32 scaled;
    u16 *fadeReg;
    u16 *fadeReg2;
    void *child;
    u8 *workspace;

    if (applyAreaSpecialBehavior(effect, sprite, work) > 0) {
        sub_080C31E0(effect, *(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_CB));
        return;
    }
    ticksLeft = (s32)timerWords[4] - 1;
    timerWords[4] = ticksLeft;
    divisor = TIMED_EFFECT_DIV_BASE;
    if (TIMED_EFFECT_TIMER_MAX - ticksLeft <= TIMED_EFFECT_NEAR_END)
        divisor = (TIMED_EFFECT_TIMER_MAX - ticksLeft) * 2;
    if (ticksLeft <= TIMED_EFFECT_EARLY_LIMIT)
        divisor = (TIMED_EFFECT_EARLY_BASE - ticksLeft) * TIMED_EFFECT_EARLY_STEP + TIMED_EFFECT_DIV_BASE;
    scaled = divInt32(TIMED_EFFECT_SCALE_NUM, divisor);
    *(u16 *)((u8 *)sprite + TIMED_EFFECT_SPRITE_TILE0) = scaled;
    *(u16 *)((u8 *)sprite + TIMED_EFFECT_SPRITE_TILE1) = scaled;
    if ((s32)timerWords[4] > TIMED_EFFECT_FADE_HIGH) {
        divisor = ((s32)timerWords[4] - TIMED_EFFECT_FADE_HIGH) >> 1;
        fadeReg = gCrossfadeGfxState;
        fadeReg[TIMED_EFFECT_GFX_REG_SLOT] = (divisor << 8) | (TIMED_EFFECT_FADE_HALF - divisor);
    }
    if ((s32)timerWords[4] <= TIMED_EFFECT_FADE_LOW) {
        divisor = (s32)timerWords[4] >> 1;
        fadeReg2 = gCrossfadeGfxState;
        fadeReg2[TIMED_EFFECT_GFX_REG_SLOT] = ((TIMED_EFFECT_FADE_HALF - divisor) << 8) | divisor;
    }
    if ((timerWords[4] & TIMED_EFFECT_SPAWN_MASK) == 0) {
        child = spawnEntity(*(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_SPAWN), TIMED_EFFECT_SPAWN_KIND, TIMED_EFFECT_SPAWN_A, TIMED_EFFECT_SPAWN_B);
        if (child != 0)
            *(u32 *)((u8 *)child + TIMED_EFFECT_CHILD_TIMER) = ((s32)timerWords[4]) >> TIMED_EFFECT_CHILD_SHIFT;
    }
    if (timerWords[4] == 0) {
        initCrossfadeGfxState();
        sub_080C31E0(effect, *(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_CB));
        return;
    }
    workspace = gMainWorkspace;
    *(u16 *)sprite = *(u16 *)(workspace + TIMED_EFFECT_WS_GFX_FLAGS);
    stepDelayTimer((u8 *)work + TIMED_EFFECT_DELAY_TIMER, sprite);
    if (--timerWords[5] == 0) {
        playSound(TIMED_EFFECT_TICK_SFX);
        timerWords[5] = TIMED_EFFECT_SFX_PERIOD;
    }
    if (*(u8 *)(workspace + TIMED_EFFECT_WS_CANCEL) == TIMED_EFFECT_WS_CANCEL_VAL ||
        (*(u8 *)(workspace + TIMED_EFFECT_WS_STATE) == 0 && *(u32 *)(workspace + TIMED_EFFECT_WS_ACTIVE) != 0))
        sub_080C31E0(effect, *(s32 *)((u8 *)effect + TIMED_EFFECT_ACTOR_CB));
}
