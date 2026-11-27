extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *, s32, void *);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, void *);
extern void releaseActorEffectParts(void);

/* Per-frame counters and effect-kind words in the main workspace. */
struct ActorChildWorkspace {
    u8 _0[0x14EF];
    u8 frameFlag;   /* 0x14EF */
    u8 _1[0x1510 - 0x14F0];
    u8 parity;      /* 0x1510 */
    u8 _2[0x1728 - 0x1511];
    u32 kindA;      /* 0x1728 */
    u32 kindB;      /* 0x172C */
};
extern struct ActorChildWorkspace gMainWorkspace;
extern u8 gGameStatus[];

/* Small effect part allocated by allocEffectPart and stored in the actor's
 * work state at +0x2C. */
struct ActorChildPart {
    u8 _0;
    u8 variant;           /* 0x01 */
    u8 kind;              /* 0x02 */
    u8 layer;             /* 0x03 */
    u16 gfxIndex;         /* 0x04: tile id from gGameStatus */
    u16 affine0, affine1, affine2, affine3, affine4; /* 0x06..0x0E */
    u32 sprite;           /* 0x10: owner sprite */
    u8 _14[2];
    u16 frame;            /* 0x16 */
    u16 animStep;         /* 0x18 */
};

/* Work state reached through the actor's +0x6C pointer (plus four bytes). */
struct ActorChildState {
    u8 _0[4];
    u32 kindB;            /* 0x04 */
    u8 _1[0x18 - 0x08];
    u32 savedHandler;     /* 0x18: previous update handler */
    u8 _2[0x2C - 0x1C];
    struct ActorChildPart *part; /* 0x2C */
    u32 handleA, handleB, handleC, handleD; /* 0x30..0x3C */
};

/* Spawn the small child effect for an actor: allocate and fill an effect part
 * from the global game tables, install the release callback as the actor's
 * update handler, start its script timer, then advance to and run the next
 * script command. */
void spawnActorChildEffectSmall(u8 *entity) {
    u8 *parent = *(u8 **)(entity + 0x6C);
    struct ActorChildState *state = (struct ActorChildState *)(parent + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *dataTable = gGameStatus;
    struct ActorChildPart *child = allocEffectPart();
    u16 flag;
    u32 v;
    s32 *callbackSlot;
    u8 *ctrlBase;
    u8 b;

    state->part = child;
    if (child == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    state->handleA = 0;
    state->handleB = 0;
    state->handleC = 0;
    state->handleD = 0;

    child->variant = gMainWorkspace.parity & 1;
    state->part->kind = 2;
    state->part->layer = 8;
    state->part->gfxIndex = dataTable[0xC1 << 2];
    state->part->affine0 = 6;
    state->part->affine1 = 6;
    state->part->affine2 = 0;
    state->part->affine3 = 0;
    state->part->affine4 = scalePercentSaturate16(*(u16 *)(dataTable + 0x2E2), 0x47);
    state->part->frame = 0x1E;
    state->part->animStep = 0x53;
    state->part->sprite = (u32)sprite;

    state->savedHandler = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)releaseActorEffectParts;
    b = gMainWorkspace.frameFlag;
    *(u8 *)(parent + 0x55) = b;
    *(u32 *)(sprite + 0x24) = 0x084D962C;

    startEffectTimer(parent + 0x20, 0, (void *)0x084D969C);

    *(u32 *)(parent + 4) = gMainWorkspace.kindA;
    state->kindB = gMainWorkspace.kindB + 0xFFEC0000;

    flag = *(u16 *)(sprite + 2) & 0x10;
    v = 0x18000;
    if (flag != 0) {
        v = 0xFFFE8000;
    }
    *(u32 *)((u8 *)state + 8) = v;
    *(u32 *)((u8 *)state + 0xC) = 0xFFFB0000;

    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = 0;
    callbackSlot = (s32 *)0x08671BB0;
    ctrlBase = entity + 0x18;
    _call_via_r2(ctrlBase, entity + 0x22, *callbackSlot);
    {
        u8 *desc = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        *(u8 *)(desc + 0x19) = (u8)(*(u8 *)(desc + 0x19) + 1);
    }
    {
        u8 *p = ctrlBase + (s16)*(s16 *)(entity + 0x22) * 2;
        _call_via_r1(entity, *(u32 *)((u32)(*p) * 4 + *(u32 *)(entity + 0x14)));
    }
}
