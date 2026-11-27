/* World-space component at +0x3C: 16.16 coordinate and its velocity. */
struct PatrolActor {
    u8 _0[0x0C];
    s32 pos;
    u8 _10[4];
    s32 vel;
    u8 _18[0x34 - 0x18];
};

/* A scripted entity: sprite/world links, step pointer, patrol state. */
struct ScriptEntity {
    u8 _0[0x14];
    void *callbacks;
    u8 _18[0x22 - 0x18];
    s16 stepIndex;
    u8 _24[0x38 - 0x24];
    void *sprite;
    struct PatrolActor *actor;
    u8 _40[0x4C - 0x40];
    u8 patrolIndex;
    u8 _4D[0x54 - 0x4D];
    u8 mode;
    s8 direction;
};

/* A script-step slot: per-step execution counter lives at +0x19. */
struct ScriptStep { u8 _0[0x19]; u8 counter; };

extern u8 D_08101AD4[];
extern void *gScriptStepCallbackTable;

extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* One tick of a scripted entity: advance its animation, then either dispatch
 * the current script step or patrol between bounds from D_08101AD4, flipping
 * direction at the ends and integrating the actor's motion. */
void sub_080A28AC(struct ScriptEntity *entity) {
    void *sprite = entity->sprite;
    struct PatrolActor *actor = entity->actor;
    u8 *patrolTable;
    s8 direction;
    s32 dirWide;
    u8 opcode;
    void *callback;
    u8 *p;
    s8 *dirPtr;
    u8 *idxPtr;
    s32 *speedPtr;
    s32 *boundPtr;
    s8 newDirection;
    u32 idx;
    u8 *base;

    stepAnimationTrack(sprite, (u8 *)actor + 0x34);

    if (entity->mode != 0) {
        ((struct ScriptStep *)((u8 *)entity + entity->stepIndex * 2))->counter = 0;
        {
            void **fnaddr = &gScriptStepCallbackTable;
            u8 *q;
            p = (u8 *)entity + 0x18;
            q = (u8 *)entity + 0x22;
            sub_080C31E4(p, q, *fnaddr);
        }
        ((struct ScriptStep *)((u8 *)entity + entity->stepIndex * 2))->counter++;
        p += entity->stepIndex * 2;
        opcode = *p;
        callback = *(void **)((u8 *)entity->callbacks + opcode * 4);
        sub_080C31E0(entity, callback);
        return;
    }

    dirPtr = (s8 *)entity + 0x58;
    dirWide = *dirPtr;
    patrolTable = D_08101AD4;
    idxPtr = (u8 *)entity + 0x4C;
    idx = *idxPtr * 3;
    idx <<= 2;
    base = (u8 *)(patrolTable + 8);
    speedPtr = (s32 *)base;
    actor->vel = dirWide * *(s32 *)((u8 *)speedPtr + idx);
    advanceMotion(actor, 0);
    direction = *dirPtr;
    if (direction == -1) goto neg;
    if (direction != 1) goto end;
    idx = *idxPtr * 3;
    idx <<= 2;
    base = (u8 *)(patrolTable + 4);
    boundPtr = (s32 *)base;
    if (actor->pos > *(s32 *)((u8 *)boundPtr + idx)) {
        newDirection = -1;
        goto store;
    }
    goto end;
neg:
    if (actor->pos < *(s32 *)(patrolTable + *idxPtr * 12)) {
        newDirection = 1;
        goto store;
    }
    goto end;
store:
    *dirPtr = newDirection;
end:
    return;
}
