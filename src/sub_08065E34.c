/* Context for one scripted-entity update: current animation step, a work
 * pointer, and the entity's embedded state block. */
struct UpdateCtx {
    u8 _0[0x22];
    s16 stepIndex;   /* 0x22 */
    u8 _24[0x14];
    u8 *work;        /* 0x38 */
    u8 _3C[0x30];
    u8 *state;       /* 0x6C: entity starts at state+4 */
};

/* Header of the state block; the entity itself follows it at +4. */
struct StateBlock {
    u8 _0[4];
    u32 spawnParam;  /* 0x04 */
    u8 _08[0x24];
    u32 actionTimer; /* 0x2C */
};

/* Scripted entity at state+4. */
struct ScriptEntity {
    u8 _0[4];
    u32 spawnParam;  /* 0x04 */
    u32 field08;     /* 0x08 */
    u32 countdown;   /* 0x0C */
    u32 field10;     /* 0x10 */
    u8 _14[0x2C];
    u32 spawnFlag;   /* 0x40 */
    u32 timingIndex; /* 0x44 */
    u8 _48[4];
    u32 field4C;
    u32 field50;
    u32 field54;
};

/* One entry of the countdown adjustment table (stride 0x58). */
struct CountdownEntry {
    u32 delta;  /* added to the entity's countdown */
    u32 limit;  /* upper clamp for the countdown */
    u8 _8[0x50];
};
extern struct CountdownEntry D_080E03A0[];
extern u32 gMainObjTimerCallbacks;
extern u8 D_0846FEA8[];
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void startEffectTimer(s32, s32, void *);
extern void sub_0806A884(void *, void *);
extern void stepDelayTimer(s32, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/*
 * Runs one frame of this scripted-entity variant: clamps its countdown,
 * spawns/queues an event on the spawn frame, then runs the position and
 * world updates.
 */
void sub_08065E34(struct UpdateCtx *arg0) {
    struct StateBlock *state = (struct StateBlock *)arg0->state;
    struct ScriptEntity *entity = (struct ScriptEntity *)((u8 *)state + 4);
    u8 *work = arg0->work;
    s32 posMode = syncViewPosition(entity, entity);
    if (posMode == 0) {
        u8 *stepPtr;
        s32 value, limit;
        u8 *timerPtr;
        s32 spawnFlag;
        resetActionResultState(arg0, work, entity, entity);
        value = entity->countdown + D_080E03A0[entity->timingIndex].delta;
        entity->countdown = value;
        limit = D_080E03A0[entity->timingIndex].limit;
        if (value > limit) entity->countdown = limit;
        sub_0806AB04(arg0, work, entity, entity);
        spawnFlag = entity->spawnFlag;
        timerPtr = (u8 *)state + 0x2C;
        if (spawnFlag == 1) {
            entity->countdown = posMode;
            startEffectTimer((s32)timerPtr, 0, (void *)D_0846FEA8);
            entity->field10 = 0x20;
            stepPtr = (u8 *)((u32)(arg0->stepIndex * 2) + (u32)arg0);
            stepPtr[0x19] = posMode;
            {
                u32 *eventPtr = &gMainObjTimerCallbacks;
                sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *eventPtr);
            }
        }
        sub_0806A884(work, entity);
        stepDelayTimer((s32)timerPtr, work);
        sub_0806C6B0(arg0, work, entity, entity);
    }
}
