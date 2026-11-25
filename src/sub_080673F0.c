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
    u8 _10[0x30];
    u32 spawnFlag;   /* 0x40 */
    u32 timingIndex; /* 0x44 */
    u8 _48[4];
    u32 field4C;     /* 0x4C */
    u32 field50;     /* 0x50 */
    u32 field54;     /* 0x54 */
};

/* One entry of the countdown adjustment table (stride 0x58). */
struct CountdownEntry {
    u32 delta;  /* added to the entity's countdown */
    u32 limit;  /* upper clamp for the countdown */
    u8 _8[0x50];
};

extern struct CountdownEntry D_080E03A0[];
extern u32 D_08671BD0;
extern u32 D_08671BD8;

extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_08005E80(s32);
extern void sub_0806E114(void *, s32, u32, u32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_0806D588(void *, void *);
extern void sub_0806A884(void *, void *);
extern u32 sub_08003740(void *, void *);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806C6B0(void *, void *, void *, void *);

/*
 * Runs one frame of a scripted entity: applies a world-position override if
 * one is active, advances the countdown, spawns the child on the spawn frame,
 * and queues a follow-up event when the action timer expires.
 */
void sub_080673F0(struct UpdateCtx *ctx) {
    struct StateBlock *blk = (struct StateBlock *)ctx->state;
    struct ScriptEntity *ent = (struct ScriptEntity *)((u8 *)blk + 4);
    u8 *work = ctx->work;
    s32 mode = sub_0806C4B4(ent, ent);
    if (mode == 0) {
        u8 *step;
        s32 timer, limit;
        sub_0806C5EC(ctx, work, ent, ent);
        timer = ent->countdown + D_080E03A0[ent->timingIndex].delta;
        ent->countdown = timer;
        limit = D_080E03A0[ent->timingIndex].limit;
        if (timer > limit) ent->countdown = limit;
        sub_0806AB04(ctx, work, ent, ent);
        if (ent->spawnFlag == 1) {
            sub_08005E80(0x67);
            ent->field4C = mode;
            ent->field50 = mode;
            ent->field54 = mode;
            ent->field08 = mode;
            sub_0806E114(ctx, 9, blk->spawnParam, ent->spawnParam);
            step = (u8 *)((u32)(ctx->stepIndex * 2) + (u32)ctx);
            step[0x19] = mode;
            {
                u32 *eventPtr = &D_08671BD0;
                sub_080C31E8((u8 *)ctx + 0x18, (u8 *)ctx + 0x22, 1, *eventPtr);
            }
        }
        sub_0806D588(work, ent);
        sub_0806A884(work, ent);
        {
            u8 *timerPtr = (u8 *)blk + 0x2C;
            u32 expired = sub_08003740(timerPtr, work);
            if (expired == 0) {
                sub_0806A7AC(work, ent, 0x10);
                sub_08003740(timerPtr, work);
                step = (u8 *)((u32)(ctx->stepIndex * 2) + (u32)ctx);
                step[0x17] = expired;
                {
                    u32 *eventPtr = &D_08671BD8;
                    sub_080C31E8((u8 *)ctx + 0x18, (u8 *)ctx + 0x22, 3, *eventPtr);
                }
            }
        }
        sub_0806C6B0(ctx, work, ent, ent);
    }
}
