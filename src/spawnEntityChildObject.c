extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *a);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *a, s32 b, s32 c);
extern void _call_via_r1(void *a, s32 b);
extern void _call_via_r2(void *a, void *b, s32 c);
extern void releaseActorEffectParts(void);
struct MainWorkspaceFrameFlag { u8 _0[0x1510]; u8 frameToggle; };
extern struct MainWorkspaceFrameFlag gMainWorkspace;
extern u8 gGameStatus[];
extern u32 gChildSpawnXOffsets[];

/* One child spawn slot reserved from the shared pool. */
struct ChildSpawnSlot {
    u8 unused0, active, kind, variant;
    u16 param4, param6, param8, paramA, paramC, paramE;
    u32 sprite;
    u8 pad14[2];
    u16 param16, param18;
};
/* Group header at workBase+4; up to five child spawn slots follow it. */
struct ChildSpawnGroup {
    u8 pad0[4];
    u32 field04;
    u8 pad08[0x10];
    u32 cleanupHandler;
    u8 pad1C[0x10];
    struct ChildSpawnSlot *spawn;
    u32 slot0, slot1, slot2, slot3;
};

/*
 * Spawns an entity's child object: reserve a spawn slot, fill its parameters
 * from the shared game status, install the cleanup handler and sprite
 * graphics, place it at a screen X chosen by a 16-entry table, then run its
 * first animation step.
 */
void spawnEntityChildObject(u8 *entity) {
    u8 *workBase = *(u8 **)(entity + 0x6C);
    struct ChildSpawnGroup *group = (struct ChildSpawnGroup *)(workBase + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *gameStatus = gGameStatus;
    struct ChildSpawnSlot *spawn = allocEffectPart();
    s32 slotValue;
    s32 slotGroupBase;
    s32 slotIndex;
    s32 *timerCallbacks;
    u8 *stepBase;
    u32 *xOffsetTable;

    group->spawn = spawn;
    if (spawn == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    group->slot0 = 0;
    group->slot1 = 0;
    group->slot2 = 0;
    group->slot3 = 0;

    spawn->active = gMainWorkspace.frameToggle & 1;
    group->spawn->kind = 2;
    group->spawn->variant = 8;
    group->spawn->param4 = gameStatus[0xC1 << 2];
    group->spawn->param6 = 0x1E;
    group->spawn->param8 = 0x1E;
    group->spawn->paramA = 0;
    group->spawn->paramC = 0;
    group->spawn->paramE = scalePercentSaturate16(*(u16 *)(gameStatus + 0x2E2), 0x47);
    group->spawn->param16 = 0x1E;
    group->spawn->param18 = 0x77;
    group->spawn->sprite = (u32)sprite;

    group->cleanupHandler = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)releaseActorEffectParts;
    *(u32 *)(sprite + 0x24) = CHILD_OBJ_ANIM_SEQ;

    startEffectTimer(workBase + 0x20, 0, CHILD_OBJ_TIMER_DATA);

    xOffsetTable = gChildSpawnXOffsets;
    slotValue = *(s32 *)(entity + 0x9C);
    slotGroupBase = slotValue;
    if (slotGroupBase < 0) slotGroupBase += 0x0F;
    slotGroupBase >>= 4;
    slotGroupBase <<= 4;
    slotIndex = slotValue - slotGroupBase;
    slotIndex <<= 2;
    *(u32 *)(sprite + 0x14) = xOffsetTable[slotIndex >> 2];

    *(u32 *)(sprite + 0x18) = 0xFFE00000;

    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = 0;
    timerCallbacks = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    stepBase = entity + 0x18;
    _call_via_r2(stepBase, entity + 0x22, *timerCallbacks);
    {
        u8 *stepData = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        *(u8 *)(stepData + 0x19) = (u8)(*(u8 *)(stepData + 0x19) + 1);
    }
    {
        u8 *stepData = stepBase + (s16)*(s16 *)(entity + 0x22) * 2;
        _call_via_r1(entity, *(u32 *)((u32)(*stepData) * 4 + *(u32 *)(entity + 0x14)));
    }
}
