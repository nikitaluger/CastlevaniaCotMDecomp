typedef struct
{
    u8 _0[0x24];
    u32 data;
} ScriptObj;

typedef struct
{
    u8 _0[0x7C];
    u32 facing;
} SpawnedPart;

typedef struct
{
    u8 _0[0x14ED];
    u8 state;
    u8 _14EE[0x32E];
    u32 flag181C;
} GameState;

extern GameState gMainWorkspace;
extern u8 D_084FC524[];
extern u8 D_084FCA3C[];
extern u8 D_084A65BC[];
extern u8 D_084A6814[];

extern SpawnedPart *spawnEntity(void *, s32, s32, s32);
extern void startEffectTimer(void *, s32, s32, s32);
extern void recordSpawnEvent(void);

/* Dispatch on the current scripted state to spawn its actors with the right
 * facing values; the last state instead arms a timed action from one of two
 * graphic tables depending on the actor's flag byte. */
s32 sub_08084D10(void *owner, ScriptObj *obj, u8 *actor)
{
    s32 stateIndex = gMainWorkspace.state - 0x31;
    SpawnedPart *spawned;

    switch (stateIndex)
    {
    case 0:
        spawned = spawnEntity(owner, 0x35, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0;
        spawned = spawnEntity(owner, 0x35, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0x80;
        recordSpawnEvent();
        break;
    case 1:
        spawned = spawnEntity(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0;
        spawned = spawnEntity(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0x40;
        spawned = spawnEntity(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0x80;
        spawned = spawnEntity(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0xC0;
        recordSpawnEvent();
        break;
    case 8:
        spawnEntity(owner, 0x37, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 9:
        spawnEntity(owner, 0x37, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 80:
        spawnEntity(owner, 0x53, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 81:
        spawnEntity(owner, 0x55, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 82:
        spawnEntity(owner, 0x56, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 83:
        spawnEntity(owner, 0x58, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 84:
        spawnEntity(owner, 0x59, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 85:
        spawnEntity(owner, 0x5B, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 86:
        spawnEntity(owner, 0x5C, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 87:
        spawnEntity(owner, 0x5E, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 88:
        spawnEntity(owner, 0x5F, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 89:
        spawnEntity(owner, 0x61, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 115:
        spawned = spawnEntity(owner, 0x2D, 0x1C, 0x02);
        if (spawned)
            spawned->facing = 1;
        recordSpawnEvent();
        break;
    case 116:
    case 119:
        spawnEntity(owner, 0x39, 0x0A, 0x12);
        recordSpawnEvent();
        break;
    case 118:
        spawned = spawnEntity(owner, 0x2D, 0x1E, 0x02);
        if (spawned)
            spawned->facing = 4;
        spawned = spawnEntity(owner, 0x2D, 0x1E, 0x02);
        if (spawned)
            spawned->facing = 5;
        recordSpawnEvent();
        break;
    case 120:
        gMainWorkspace.flag181C = 1;
        recordSpawnEvent();
        break;
    case 121:
        if (actor[0x128] != 0)
        {
            obj->data = (u32) D_084FC524;
            startEffectTimer(actor + 0x28, 0, (s32) D_084FCA3C, (s32) obj);
            recordSpawnEvent();
            return 0x29;
        }
        obj->data = (u32) D_084A65BC;
        startEffectTimer(actor + 0x28, 0, (s32) D_084A6814, (s32) obj);
        recordSpawnEvent();
        return 0x24;
    default:
        return 4;
    }
    return 4;
}
