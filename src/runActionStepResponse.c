/* Performs the response to the action step currently selected by
 * gMainWorkspace.actionState: failed/cancelled/no-direction steps spawn and
 * reset the configured entity, while the scenario codes advance the actor's
 * counters, spawn the step's effect and play its cue. */
extern u32 sub_08061C78(void);                 /* scaled value used as a spawn threshold */
extern void *spawnEntity(s32, s32, s32, s32);
extern void spawnScaledEffect(s32, s32);
extern void recordSpawnEvent(void);                /* records the spawn in the global table */
extern void playSound(s32);
extern s32 sub_080C3824(s32, s32);             /* saturating divide */

extern struct ActionStepWorkspace gMainWorkspace;
extern struct ActionStepGameState gGameStatus;

void runActionStepResponse(s32 actor, struct ActionStepContext *state, s32 pos) {
    u32 currentValue;
u32 __repair_result_r6;
    void *spawned;
    u32 wrappedCount;
    s32 nextTick;
    
    u32 stateOffset;
    u8 command;
    struct ActionStepGameState *gs = &gGameStatus;
    u8 rawCommand;

    gMainWorkspace.spawnRequest = 0;
    stateOffset = ACTION_STEP_STATE_OFFSET;
    rawCommand = *(u8 *)((u8 *)&gMainWorkspace + stateOffset);
    command = rawCommand;
    switch (command) {
    case ACTION_STEP_FAIL:
        if (gMainWorkspace.failFlag == 0) return;
        spawned = spawnEntity(actor, SPRITE_KIND_JITTERED_SPAWN, 0xA, 0x12);
        if (spawned != NULL) ((struct ActionStepSpawn *)spawned)->animFlags = 0;
        recordSpawnEvent();
        return;
    case ACTION_STEP_NO_DIR:
    case ACTION_ALT_STEP_FAIL:
        __repair_result_r6 = sub_08061C78();
        if (__repair_result_r6 <= state->spawnCounter) return;
        spawned = spawnEntity(actor, SPRITE_KIND_JITTERED_SPAWN, 0xA, 0x12);
        if (spawned != NULL) ((struct ActionStepSpawn *)spawned)->animFlags = 0;
        recordSpawnEvent();
        state->spawnCounter = __repair_result_r6;
        return;
    case ACTION_STEP_CANCEL:
        if (gMainWorkspace.cancelFlag == 0) return;
        spawned = spawnEntity(actor, SPRITE_KIND_JITTERED_SPAWN, 0xA, 0x12);
        if (spawned != NULL) ((struct ActionStepSpawn *)spawned)->animFlags = 0;
        recordSpawnEvent();
        return;
    case 0x27:
        if ((s32)gs->phaseTimer < (s32)gs->phaseThreshold) {
            wrappedCount = (state->spawnCounter + 1) & 0x3F;
            state->spawnCounter = wrappedCount;
            if (wrappedCount == 0) {
                spawned = spawnEntity(actor, SPRITE_KIND_JITTERED_SPAWN, 0xA, 0x12);
                if (spawned != NULL) ((struct ActionStepSpawn *)spawned)->animFlags = 0;
                recordSpawnEvent();
            }
        } else {
            state->spawnCounter = 0;
        }
        return;
    case 0x33:
        if (gMainWorkspace.timerEnabled != 0) {
            nextTick = gMainWorkspace.actionTimer + 1;
            gMainWorkspace.actionTimer = nextTick;
            if (nextTick > 0x3B) {
                gMainWorkspace.actionTimer = 0;
                spawnScaledEffect(pos, 1);
                recordSpawnEvent();
            }
        }
        return;
    case 0x35:
        state->form = 3;
        gMainWorkspace.spawnRequest = 1;
        recordSpawnEvent();
        return;
    case 0x36:
        if ((s32)state->spawnCounter <= 0) {
            state->spawnCounter = 0xC;
            spawnEntity(actor, ACTION_SPAWN_KIND_ALT, 0xA, 0x12);
            recordSpawnEvent();
            playSound(0xD8);
        }
        state->spawnCounter--;
        return;
    case 0x3A:
        state->timerMode = 2;
        state->timerCount = 2;
        gMainWorkspace.spawnTimerB = 1;
        gMainWorkspace.spawnTimerA = 0;
        return;
    case 0xA1: {
        u32 timer = gMainWorkspace.actionTimer;
        if (timer != 0) {
            timer--;
            gMainWorkspace.actionTimer = timer;
            if (((s32)timer <= 0x1FF) && !(timer & 3)) {
                spawnEntity(actor, ACTION_SPAWN_KIND_TIMER, 0xA, 0x12);
            }
        }
        return;
    }
    case 0xA3: {
        u32 *current = &gs->trackedValue;
        if (*current > (u32)gMainWorkspace.trackedSnapshot) {
            currentValue = *current;
            gs->trackedValue = currentValue + sub_080C3824(currentValue - gMainWorkspace.trackedSnapshot, 5);
            spawned = spawnEntity(actor, SPRITE_KIND_JITTERED_SPAWN, 0xA, 0x12);
            if (spawned != NULL) {
                ((struct ActionStepSpawn *)spawned)->animFlags = 0;
            }
            recordSpawnEvent();
        }
        return;
    }
    }
}
