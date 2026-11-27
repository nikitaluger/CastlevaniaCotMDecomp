/* Per-frame behavior for a scripted object: start a queued effect, attack when
 * the player is close and already faced, and tick the idle timer that flips
 * the sprite and updates the work-facing direction. */
extern s32 scaleByRandom(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080149A4(void *, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);

struct Behavior {
    s16 spawnIndex;
    s16 pad2;
    s16 timer;
    s16 cooldown;
    s16 state;
    s16 pada;
    s32 paramC;
};

struct Mover {
    u16 f0;
    u16 flags2;
    u32 pad4;
    s32 x;
    s32 y;
    s32 facing;
};

struct ScriptArg { u8 pad[0x22]; s16 index; };

extern s16 gIdleTimerRanges[];
extern u32 gScriptStepCallbacks[];

void updateScriptedObjectBehavior(void *entity)
{
    void *sprite = *(void **)((u8 *)entity + 0x38);
    struct Mover *work = *(struct Mover **)((u8 *)entity + 0x3C);
    void *animTrack = (u8 *)work + 0x34;
    struct Behavior *behaviorState = (struct Behavior *)((u8 *)work + 0x48);

    if (behaviorState->state == 1) {
        void *timerPtr = (u8 *)work + 0x4A;
        s16 rangeIndex = behaviorState->spawnIndex;
        s16 *range = gIdleTimerRanges;
        s32 minDelay = range[rangeIndex * 2];
        range += 1;
        {
            s32 maxDelay = range[rangeIndex * 2];
            sub_080149A4(sprite, work, timerPtr, minDelay, maxDelay);
        }
    }

    setAnimationFrame(sprite, animTrack, 0, 1);

    behaviorState->cooldown--;
    if ((s16)behaviorState->cooldown <= 0) {
        if (absXFromFocus(work->x) <= 0x180000 && absYFromFocus(work->y) <= 0x100000) {
            s32 playerDir = signOf(work->x);
            if (playerDir == getSpriteFacingSign(sprite)) {
                s16 stepIndex;
                u8 *stepPtr;
                u32 *callback;
                behaviorState->cooldown = 0x3C;
                stepIndex = ((struct ScriptArg *)entity)->index;
                stepPtr = (u8 *)((s16 *)entity + stepIndex);
                stepPtr[0x19] = 0;
                callback = gScriptStepCallbacks;
                sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 1, *callback);
                return;
            }
            behaviorState->timer = 0;
            behaviorState->state = 1;
        }
        behaviorState->cooldown = 0;
    }

    if (work->flags2 & 3) {
        s32 idleState;
        u16 flags;
        flags = *(u16 *)((u8 *)sprite + 2);
        flags ^= 0x10;
        idleState = 0;
        *(u16 *)((u8 *)sprite + 2) = flags;
        behaviorState->timer = scaleByRandom(0x3D) + 0x78;
        behaviorState->state = idleState;
    }

    behaviorState->timer--;
    if ((s16)behaviorState->timer <= 0) {
        behaviorState->timer = scaleByRandom(0x3D) + 0x78;
        if (absXFromFocus(work->x) <= 0x600000 && absYFromFocus(work->y) <= 0x400000) {
            behaviorState->state = 1;
        } else {
            behaviorState->state = 0;
            if (work->x < behaviorState->paramC)
                *(u16 *)((u8 *)sprite + 2) |= 0x10;
            else
                *(u16 *)((u8 *)sprite + 2) &= 0xFFEF;
        }
    }

    if (getSpriteFacingSign(sprite) > 0)
        work->facing = 0x6000;
    else
        work->facing = 0xFFFFA000;
}
