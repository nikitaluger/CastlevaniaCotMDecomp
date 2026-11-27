/* Spawn the direction-scaled child effect of an actor's current script step:
 * take a render part from the pool and fill it from gGameStatus, install
 * releaseActorEffectParts as the actor's update handler, expand the angle byte
 * at entity+0x9C into a velocity vector and amplify it fivefold, start the
 * child's script timer, then advance to and dispatch the next script command.
 * On allocation failure the old child is just cleaned up. */
extern void startEffectTimer(void *, s32, void *);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s16 scalePercentSaturate16(u16, s32);
extern void setDirectionVector(void *, u8);
extern void releaseActorEffectParts(void);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
extern u8 gGameStatus[];
extern u32 gScaledDirectionChildAnimTable;
extern u32 gScaledDirectionChildTimerTable;
extern s32 gMainObjTimerCallbacks;

/* Work state reached through the actor's +0x6C pointer (plus four bytes):
 * +0x2C is the spawned render part and is reloaded on every access. */
struct EffectSpawnState { u8 _0[0x2C]; u8 * volatile part; };

/* Global flags: the low bit at +0x1510 selects the spawned part's variant. */
struct EffectSpawnWorkspace { u8 _0[0x1510]; u8 parity; };
extern struct EffectSpawnWorkspace gMainWorkspace;

void spawnActorChildEffectScaledDirection(u8 *entity) {
    s32 zero;
    s32 scaleConst;
    u8 *parent = *(u8 **)(entity + 0x6C);
    u8 *state = parent + 4;
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *dataTable = gGameStatus;
    void *part;
    struct EffectSpawnState *work = (struct EffectSpawnState *)state;

    part = allocEffectPart();
    work->part = part;
    if (part == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    zero = 0;
    *(u32 *)(state + 0x30) = zero;
    *(u32 *)(state + 0x34) = zero;
    *(u32 *)(state + 0x38) = zero;
    *(u32 *)(state + 0x3C) = zero;
    *(u8 *)(part + 1) = 1 & gMainWorkspace.parity;
    *(u8 *)(work->part + 2) = 2;
    *(u8 *)(work->part + 3) = 8;
    *(u16 *)(work->part + 4) = *(u8 *)(dataTable + 0x304);
    *(u16 *)(work->part + 6) = 4;
    *(u16 *)(work->part + 8) = 4;
    *(u16 *)(work->part + 0xA) = zero;
    *(u16 *)(work->part + 0xC) = zero;
    *(u16 *)(work->part + 0xE) = scalePercentSaturate16(*(u16 *)(dataTable + 0x2E2), 0x32);
    *(u16 *)(work->part + 0x16) = 0x1E;
    *(u16 *)(work->part + 0x18) = 0x59;
    {
        u8 *partCopy = work->part;
        *(void **)(partCopy + 0x10) = sprite;
    }
    *(u32 *)(state + 0x18) = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&releaseActorEffectParts;
    *(u32 *)(sprite + 0x24) = (u32)&gScaledDirectionChildAnimTable;
    startEffectTimer(parent + 0x20, 0, &gScaledDirectionChildTimerTable);
    *(u32 *)(parent + 4) = *(u32 *)(entity + 0x7C);
    *(u32 *)(state + 4) = *(u32 *)(entity + 0x8C);
    scaleConst = 0xA0 << 0xB;
    *(s32 *)(state + 0x40) = scaleConst;
    {
        u32 direction = *(u32 *)(entity + 0x9C);
        *(u8 *)(parent + 0x48) = direction;
    }
    setDirectionVector(state, *(u8 *)(parent + 0x48));
    {
        s32 scaleFactor = *(s32 *)(state + 0x40) >> 8;
        *(s32 *)(state + 8) = (*(s32 *)(state + 8) * scaleFactor) / 256;
        *(s32 *)(state + 0xC) = (*(s32 *)(state + 0xC) * scaleFactor) / 256;
    }
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
    {
        s32 *callbackSlot = &gMainObjTimerCallbacks;
        u8 *scriptPtr = entity + 0x18;
        _call_via_r2(scriptPtr, entity + 0x22, *callbackSlot);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) + 1;
        scriptPtr += *(s16 *)(entity + 0x22) * 2;
        {
            u8 cmdId = *scriptPtr;
            _call_via_r1(entity, *(s32 *)(cmdId * 4 + *(u32 *)(entity + 0x14)));
        }
    }
}
