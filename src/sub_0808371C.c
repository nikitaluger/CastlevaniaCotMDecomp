extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s16 scalePercentSaturate16(u16, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(u8 *, void *, s32);

struct GlobalState { u8 _0[0x1510]; u8 flags; };
extern struct GlobalState gMainWorkspace;
extern u8 gGameStatus[];
extern s32 gScriptStepCallbackTable;

struct SpawnParams {
    u8 _0;
    u8 f01;
    u8 f02;
    u8 f03;
    u16 f04;
    u16 f06;
    u16 f08;
    u16 f0A;
    u16 f0C;
    u16 f0E;
    void *f10;
    u8 _2[2];
    u16 f16;
    u16 f18;
};

struct WorkerState {
    u8 _0[4];
    void *f4;
    u8 _1[0x10 - 8];
    s32 f10;
    u8 _2[0x18 - 0x14];
    void *f18;
    u8 _3[0x2C - 0x1C];
    struct SpawnParams *f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

struct Entity {
    u8 _0[0x14];
    void *handlerTable;
    u8 _1[0x22 - 0x18];
    s16 scriptIndex;
    void *updateCallback;
    u8 _2[0x38 - 0x28];
    void *linkedObj;
    u8 _3[0x6C - 0x3C];
    void *workerState;
};

static inline u32 bitOne(u16 v)
{
    u32 m = 1;
    m &= v;
    return m;
}

/* Allocate and fill a worker record for the entity from global state, install
 * a new update callback, then run the entity's script step. */
void sub_0808371C(struct Entity *entity)
{
    struct WorkerState *worker;
    void *linkedObj;
    u8 *globals;
    struct SpawnParams *params;
    s32 zero;
    s32 zero2;

    worker = (struct WorkerState *)((u8 *)entity->workerState + 4);
    linkedObj = entity->linkedObj;
    globals = gGameStatus;
    params = allocEffectPart();
    worker->f2C = params;
    if (params == 0) {
        sub_0806D2D0(entity);
        return;
    }
    zero = 0;
    worker->f30 = zero;
    worker->f34 = zero;
    worker->f38 = zero;
    worker->f3C = zero;
    params->f01 = (u8)bitOne(gMainWorkspace.flags);
    worker->f2C->f02 = 2;
    worker->f2C->f03 = 8;
    worker->f2C->f04 = globals[0x304];
    zero2 = 0;
    worker->f2C->f06 = 0x20;
    worker->f2C->f08 = 0x28;
    worker->f2C->f0A = zero;
    worker->f2C->f0C = zero;
    worker->f2C->f0E = scalePercentSaturate16(*(u16 *)(globals + 0x2E2), 0x16);
    worker->f2C->f16 = 0x3C;
    worker->f2C->f18 = 0x7A;
    worker->f2C->f10 = linkedObj;
    worker->f18 = entity->updateCallback;
    entity->updateCallback = (void *)0x0808449D;
    worker->f10 = zero;
    *(u8 *)((u8 *)entity + entity->scriptIndex * 2 + 0x19) = zero2;
    {
        s32 *fn = &gScriptStepCallbackTable;
        u8 *scriptPtr = (u8 *)entity + 0x18;
        sub_080C31E4(scriptPtr, &entity->scriptIndex, *fn);
        (*(u8 *)((u8 *)entity + entity->scriptIndex * 2 + 0x19))++;
        scriptPtr += entity->scriptIndex * 2;
        sub_080C31E0(entity, *(s32 *)((u8 *)entity->handlerTable + *scriptPtr * 4));
    }
}
