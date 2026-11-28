extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *, s32, s32);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
extern void releaseActorEffectParts(void);
extern u8 gGameStatus[];

/* One child record reserved from the shared 0x34-byte spawn-slot pool. */
struct ChildSpawnRec {
    u8 unused0, active, kind, variant;
    u16 param4, param6, param8, paramA, paramC, paramE;
    u32 sprite;
    u8 pad14[2];
    u16 param16, param18;
};

/* Per-entity spawn state, held at entity->group + 4. */
struct EntitySpawnState {
    u8 pad0[4];
    u32 field04;
    u8 pad08[0x10];
    u32 cleanupHandler;
    u8 pad1C[0x10];
    struct ChildSpawnRec *spawn;
    u32 slot0, slot1, slot2, slot3;
};

/* Variant of spawnEntityChildObject: reserves a child spawn record, fills it
 * from the gGameStatus parameter table and the entity's configured values,
 * installs releaseActorEffectParts as the cleanup handler plus the effect
 * animation/timer data, then advances the entity to its next script step. On
 * allocation failure it runs cleanupFailedEffectSpawn and returns. */
void spawnEntityChildEffect(u8 *entity) {
    u8 *groupBase = *(u8 **)(entity + 0x6C);
    struct EntitySpawnState *state = (struct EntitySpawnState *)(groupBase + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *params = gGameStatus;
    void *child;
    u32 zero;
    u8 *ctrlBase;
    s32 *callbackSlot;
    s32 i;

    child = allocEffectPart();
    state->spawn = child;
    if (child == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    zero = 0;
    state->slot0 = zero;
    state->slot1 = zero;
    state->slot2 = zero;
    state->slot3 = zero;
    *(u8 *)((u8 *)child + 1) = zero;
    state->spawn->kind = 2;
    state->spawn->variant = 8;
    state->spawn->param4 = *(u8 *)(params + (0xC1 << 2));
    state->spawn->param6 = 5;
    state->spawn->param8 = 0x5A;
    state->spawn->paramA = zero;
    state->spawn->paramC = zero;
    state->spawn->paramE = scalePercentSaturate16(*(u16 *)(params + 0x2E2), 0x64);
    state->spawn->param16 = 0x3C;
    state->spawn->param18 = 0x57;
    state->spawn->sprite = (u32)sprite;
    state->cleanupHandler = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&releaseActorEffectParts;
    *(u32 *)(sprite + 0x24) = 0x084D9E58;
    startEffectTimer(groupBase + 0x20, 0, 0x084D9E80);
    *(u32 *)(groupBase + 4) = *(u32 *)(entity + 0x7C);
    *(u32 *)((u8 *)state + 4) = *(u32 *)(entity + 0x8C);
    *(u32 *)((u8 *)state + 0x10) = *(u32 *)(entity + 0x9C);
    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = zero;
    callbackSlot = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    ctrlBase = entity + 0x18;
    _call_via_r2(ctrlBase, entity + 0x22, *callbackSlot);
    {
        i = *(s16 *)(entity + 0x22);
        i *= 2;
        {
            u8 *p = (u8 *)((u32)i + (u32)entity);
            *(u8 *)(p + 0x19) = (u8)(*(u8 *)(p + 0x19) + 1);
        }
    }
    {
        u8 *p = ctrlBase + (s16)*(s16 *)(entity + 0x22) * 2;
        _call_via_r1(entity, *(u32 *)((u32)(*p) * 4 + *(u32 *)(entity + 0x14)));
    }
}
