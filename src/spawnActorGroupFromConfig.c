/*
 * Spawn an actor group: allocate a child record, fill it from the slot and
 * parameter tables, install the actor/sprite callbacks, then advance the
 * actor's script step.
 */
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *a);
extern s16 scalePercentSaturate16(u16, u16);
extern void startEffectTimer(void *a, s32 b, s32 c);
extern s32 signedRemainder(s32, s32);
extern void _call_via_r1(void *a, s32 b);
extern void _call_via_r2(void *a, void *b, s32 c);
extern void releaseActorEffectParts(void);

struct S_02025FF0 { u8 _0[0x1510]; u8 b1510; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern u8 D_080E5C80[];
extern u8 D_080E5C5C[];
extern s32 gMainObjTimerCallbacks;

/* Child render part allocated for the actor (offsets from m2c). */
struct ChildConfigPart {
    u8 f0;
    u8 active;         /* 0x01: gMainWorkspace.b1510 & 1 */
    u8 type;           /* 0x02: 2 */
    u8 subtype;        /* 0x03: 8 */
    u16 dataWord;      /* 0x04: gGameStatus+0x304 */
    u16 field6;        /* 0x06: config table +8 */
    u16 field8;        /* 0x08: config table +0xA */
    u16 fieldA;        /* 0x0A */
    u16 fieldC;        /* 0x0C */
    u16 scaledValue;   /* 0x0E: scaled by scalePercentSaturate16 */
    u32 sprite;        /* 0x10 */
    u8 _14[2];
    u16 lifetime;      /* 0x16: 5 */
    u16 field18;       /* 0x18: config table +0x14 */
    u8 _1A[0x0A];
    u32 f24;
};

/* Work state at actor+0x6C+4. */
struct ActorChildState {
    u8 _0[0x18];
    u32 oldHandler;    /* 0x18: replaced by releaseActorEffectParts */
    u8 _1C[0x10];
    struct ChildConfigPart *child; /* 0x2C */
    u32 handle0, handle1, handle2, handle3; /* 0x30..0x3C */
    u8 _40[0x14];
    u32 field54;       /* 0x54: config table +4 */
};

void spawnActorGroupFromConfig(u8 *actor) {
    u8 *groupBase = *(u8 **)(actor + 0x6C);
    struct ActorChildState *group = (struct ActorChildState *)(groupBase + 4);
    u8 *sprite = *(u8 **)(actor + 0x38);
    u8 *params = gGameStatus;
    struct ChildConfigPart *spawn;
    u32 *slotPtr;
    u32 *stepCallbacks;
    u32 idx;
    u8 *table;
    u8 *animTable;

    spawn = (struct ChildConfigPart *)allocEffectPart();
    group->child = spawn;
    if (spawn == NULL) {
        cleanupFailedEffectSpawn(actor);
        return;
    }
    group->handle0 = 0;
    group->handle1 = 0;
    group->handle2 = 0;
    group->handle3 = 0;

    slotPtr = (u32 *)(actor + 0x9C);
    idx = (*slotPtr & 3) * 0x18;
    table = D_080E5C80 + idx;

    group->child->active = gMainWorkspace.b1510 & 1;
    group->child->type = 2;
    group->child->subtype = 8;
    group->child->dataWord = params[0xC1 << 2];
    group->child->field6 = *(u16 *)(table + 8);
    group->child->field8 = *(u16 *)(table + 0xA);
    group->child->fieldA = 0;
    group->child->fieldC = 0;
    group->child->scaledValue = scalePercentSaturate16(*(u16 *)(params + 0x2E2), *(u16 *)(table + 0xC));
    group->child->lifetime = 5;
    group->child->field18 = *(u16 *)(table + 0x14);
    group->child->sprite = (u32)sprite;

    group->oldHandler = *(u32 *)(actor + 0x24);
    *(u32 *)(actor + 0x24) = (u32)releaseActorEffectParts;
    *(u32 *)(sprite + 0x24) = 0x084F3C04;

    startEffectTimer(groupBase + 0x20, 0, *(u32 *)(table + 0x10));

    *(u32 *)(sprite + 0x14) = 0x1000000;
    animTable = D_080E5C5C;
    *(u32 *)(sprite + 0x18) = *(u32 *)(animTable + (signedRemainder(*slotPtr, 9) << 2));

    group->field54 = *(u32 *)(table + 4);
    *(u32 *)((u8 *)group + 8) = *(u32 *)(table + 0);

    *((u8 *)((s16)*(s16 *)(actor + 0x22) * 2 + (u32)actor) + 0x19) = 0;

    stepCallbacks = (u32 *)&gMainObjTimerCallbacks;
    {
        u8 *scriptState = actor + 0x18;
        _call_via_r2(scriptState, actor + 0x22, *stepCallbacks);
        {
            u8 *stepSlot = (u8 *)((s16)*(s16 *)(actor + 0x22) * 2 + (u32)actor);
            *(u8 *)(stepSlot + 0x19) = (u8)(*(u8 *)(stepSlot + 0x19) + 1);
        }
        {
            u8 *stepParam = scriptState + (s16)*(s16 *)(actor + 0x22) * 2;
            _call_via_r1(actor, *(u32 *)((u32)(*stepParam) * 4 + *(u32 *)(actor + 0x14)));
        }
    }
}
