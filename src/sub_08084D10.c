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

extern SpawnedPart *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_08003A6C(void *, s32, s32, s32);
extern void sub_08086E28(void);

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
        spawned = sub_0806D2A0(owner, 0x35, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0;
        spawned = sub_0806D2A0(owner, 0x35, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0x80;
        sub_08086E28();
        break;
    case 1:
        spawned = sub_0806D2A0(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0;
        spawned = sub_0806D2A0(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0x40;
        spawned = sub_0806D2A0(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0x80;
        spawned = sub_0806D2A0(owner, 0x36, 0x0A, 0x12);
        if (spawned)
            spawned->facing = 0xC0;
        sub_08086E28();
        break;
    case 8:
        sub_0806D2A0(owner, 0x37, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 9:
        sub_0806D2A0(owner, 0x37, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 80:
        sub_0806D2A0(owner, 0x53, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 81:
        sub_0806D2A0(owner, 0x55, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 82:
        sub_0806D2A0(owner, 0x56, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 83:
        sub_0806D2A0(owner, 0x58, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 84:
        sub_0806D2A0(owner, 0x59, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 85:
        sub_0806D2A0(owner, 0x5B, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 86:
        sub_0806D2A0(owner, 0x5C, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 87:
        sub_0806D2A0(owner, 0x5E, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 88:
        sub_0806D2A0(owner, 0x5F, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 89:
        sub_0806D2A0(owner, 0x61, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 115:
        spawned = sub_0806D2A0(owner, 0x2D, 0x1C, 0x02);
        if (spawned)
            spawned->facing = 1;
        sub_08086E28();
        break;
    case 116:
    case 119:
        sub_0806D2A0(owner, 0x39, 0x0A, 0x12);
        sub_08086E28();
        break;
    case 118:
        spawned = sub_0806D2A0(owner, 0x2D, 0x1E, 0x02);
        if (spawned)
            spawned->facing = 4;
        spawned = sub_0806D2A0(owner, 0x2D, 0x1E, 0x02);
        if (spawned)
            spawned->facing = 5;
        sub_08086E28();
        break;
    case 120:
        gMainWorkspace.flag181C = 1;
        sub_08086E28();
        break;
    case 121:
        if (actor[0x128] != 0)
        {
            obj->data = (u32) D_084FC524;
            sub_08003A6C(actor + 0x28, 0, (s32) D_084FCA3C, (s32) obj);
            sub_08086E28();
            return 0x29;
        }
        obj->data = (u32) D_084A65BC;
        sub_08003A6C(actor + 0x28, 0, (s32) D_084A6814, (s32) obj);
        sub_08086E28();
        return 0x24;
    default:
        return 4;
    }
    return 4;
}
