extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *a);
extern s16 sub_0806D62C(u16, s32);
extern void sub_08003A6C(void *a, s32 b, s32 c);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_0808449C(void);
struct S_02025FF0 { u8 _0[0x1510]; u8 b1510; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern u32 D_080E5CE0[];

/* one child spawn record, reserved from the shared pool */
struct Spawn {
    u8 unused0, active, kind, variant;
    u16 param4, param6, param8, paramA, paramC, paramE;
    u32 sprite;
    u8 pad14[2];
    u16 param16, param18;
};
/* group header held at groupBase+4; up to five child spawn slots follow */
struct SpawnGroup {
    u8 pad0[4];
    u32 field04;
    u8 pad08[0x10];
    u32 cleanupHandler;
    u8 pad1C[0x10];
    struct Spawn *spawn;
    u32 slot0, slot1, slot2, slot3;
};

/*
 * Spawns an entity's child object: allocate a spawn slot, fill its parameters
 * from a shared table, install the cleanup handler and sprite graphics, place
 * it at an initial screen X chosen by a 16-entry table, then run its first
 * animation step.
 */
void sub_08082288(u8 *entity) {
    u8 *groupBase = *(u8 **)(entity + 0x6C);
    struct SpawnGroup *group = (struct SpawnGroup *)(groupBase + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *params = gGameStatus;
    struct Spawn *spawn = allocEffectPart();
    s32 slotRaw;
    s32 slotBase;
    s32 slot;
    s32 *scriptFn;
    u8 *stepTable;
    u32 *spawnXTable;

    group->spawn = spawn;
    if (spawn == NULL) {
        sub_0806D2D0(entity);
        return;
    }
    group->slot0 = 0;
    group->slot1 = 0;
    group->slot2 = 0;
    group->slot3 = 0;

    spawn->active = gMainWorkspace.b1510 & 1;
    group->spawn->kind = 2;
    group->spawn->variant = 8;
    group->spawn->param4 = params[0xC1 << 2];
    group->spawn->param6 = 0x1E;
    group->spawn->param8 = 0x1E;
    group->spawn->paramA = 0;
    group->spawn->paramC = 0;
    group->spawn->paramE = sub_0806D62C(*(u16 *)(params + 0x2E2), 0x47);
    group->spawn->param16 = 0x1E;
    group->spawn->param18 = 0x77;
    group->spawn->sprite = (u32)sprite;

    group->cleanupHandler = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)sub_0808449C;
    *(u32 *)(sprite + 0x24) = 0x084F52C8;

    sub_08003A6C(groupBase + 0x20, 0, 0x084F52E8);

    spawnXTable = D_080E5CE0;
    slotRaw = *(s32 *)(entity + 0x9C);
    slotBase = slotRaw;
    if (slotBase < 0) slotBase += 0x0F;
    slotBase >>= 4;
    slotBase <<= 4;
    slot = slotRaw - slotBase;
    slot <<= 2;
    *(u32 *)(sprite + 0x14) = spawnXTable[slot >> 2];

    *(u32 *)(sprite + 0x18) = 0xFFE00000;

    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = 0;
    scriptFn = (s32 *)0x08671BB0;
    stepTable = entity + 0x18;
    sub_080C31E4(stepTable, entity + 0x22, *scriptFn);
    {
        u8 *stepData = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        *(u8 *)(stepData + 0x19) = (u8)(*(u8 *)(stepData + 0x19) + 1);
    }
    {
        u8 *stepData = stepTable + (s16)*(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)((u32)(*stepData) * 4 + *(u32 *)(entity + 0x14)));
    }
}
