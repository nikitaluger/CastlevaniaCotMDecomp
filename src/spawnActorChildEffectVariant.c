extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *, s32, void *);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, void *);
extern void releaseActorEffectParts(void);

struct S_02025FF0 {
    u8 _0[0x14EF];
    u8 b14EF;
    u8 _1[0x1510 - 0x14F0];
    u8 b1510;
    u8 _2[0x1728 - 0x1511];
    u32 f1728;
    u32 f172C;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern s32 gMainObjTimerCallbacks;

struct SubObject {
    u8 _0;
    u8 active;
    u8 type;
    u8 subtype;
    u16 dataWord;
    u16 field6;
    u16 field8;
    u16 fieldA;
    u16 fieldC;
    u16 scaledValue;
    u32 sprite;
    u8 _14[2];
    u16 lifetime;
    u16 field18;
};
struct BehaviorState {
    u8 _0[4];
    u32 oldHandler;
    u8 _1[0x18 - 0x08];
    u32 cleanupCallback;
    u8 _2[0x2C - 0x1C];
    struct SubObject *subObject;
    u32 handle0, handle1, handle2, handle3;
    u8 _40[0x14];
    u32 field54;
};
struct ScriptStep { u8 _0[0x19]; u8 counter; };

/* Allocate and initialize a sub-object for this entity's current action, install its
 * cleanup callback and timer, then dispatch the next script step. */
void spawnActorChildEffectVariant(u8 *entity) {
    u8 *params = *(u8 **)(entity + 0x6C);
    struct BehaviorState *state = (struct BehaviorState *)(params + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *dataTable = gGameStatus;
    struct SubObject *child = allocEffectPart();
    u16 spriteFlag;
    u8 one = 1;
    u16 flagMask = 0x10;
    s32 offset;
    u32 stepOffset;

    state->subObject = child;
    if (child == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    state->handle0 = 0;
    state->handle1 = 0;
    state->handle2 = 0;
    state->handle3 = 0;

    child->active = gMainWorkspace.b1510 & one;
    state->subObject->type = 2;
    state->subObject->subtype = 8;
    state->subObject->dataWord = dataTable[0xC1 << 2];
    state->subObject->field6 = 9;
    state->subObject->field8 = 9;
    state->subObject->fieldA = 0;
    state->subObject->fieldC = 0;
    state->subObject->scaledValue = scalePercentSaturate16(*(u16 *)(dataTable + 0x2E2), 0x20);
    state->subObject->lifetime = 0x1E;
    state->subObject->sprite = (u32)sprite;

    state->cleanupCallback = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)releaseActorEffectParts;
    {
        u8 modeFlag = gMainWorkspace.b14EF;
        *(u8 *)(params + 0x55) = modeFlag;
    }
    *(u32 *)(sprite + 0x24) = 0x084DCFBC;

    startEffectTimer(params + 0x20, 0, (void *)0x084DD09C);

    state->field54 = 0x1C;
    *(u32 *)(params + 4) = gMainWorkspace.f1728;
    state->oldHandler = gMainWorkspace.f172C + 0xFFEC0000;

    spriteFlag = *(u16 *)(sprite + 2) & flagMask;
    offset = 0x28000;
    if (spriteFlag != 0) {
        offset = 0xFFFD8000;
    }
    *(u32 *)((u8 *)state + 8) = offset;
    *(u32 *)((u8 *)state + 0xC) = 0xFFFB0000;

    ((struct ScriptStep *)(entity + *(s16 *)(entity + 0x22) * 2))->counter = 0;
    {
        s32 *cueTable = &gMainObjTimerCallbacks;
        u8 *scriptPtr = entity + 0x18;
        _call_via_r2(scriptPtr, entity + 0x22, *cueTable);
        ((struct ScriptStep *)(entity + *(s16 *)(entity + 0x22) * 2))->counter++;
        stepOffset = *(s16 *)(entity + 0x22) * 2;
        _call_via_r1(entity, *(u32 *)(*(u32 *)(entity + 0x14) + *(u8 *)(scriptPtr + stepOffset) * 4));
    }
}
