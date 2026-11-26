/* Spawns the dash afterimage effect: allocates an effect part, sets its colour,
 * size and scaled stat parameters, places it at the camera with a horizontal
 * velocity opposite the owner's facing, installs the release handler, plays the
 * effect sound, then advances the parent's state machine. */
extern void *allocEffectPart(void);              /* alloc effect part */
extern void sub_0806D2D0(void *);             /* bail out / release entity */
extern u16 sub_0806D62C(u16, s32);            /* scale value by percent */
extern void sub_08005E80(u32);                /* play sound */
extern void sub_080C31E4(void *, void *, s32); /* indirect call */
extern void sub_080C31E0(void *, void *);     /* indirect call */
extern void sub_080718F4(void);               /* release handler */
extern u8 gGameStatus[];    /* game/player data: +0x8C character, +0x2DE stat */
extern u8 gMainWorkspace[];    /* scene state: +0x1510 colour, +0x1728/0x172C camera, +0x18C2 sprite bits */
extern u32 D_080E0098[];   /* per-weapon Y offsets */
extern u32 gMainObjTimerCallback;

/* 0x34-byte effect part object allocated by allocEffectPart. */
struct EffectPart {
    u8 mode;     /* 0x00 */
    u8 color;    /* 0x01: palette/colour index */
    u8 param2;   /* 0x02: 2 */
    u8 param3;   /* 0x03: 8 */
    u16 p0;      /* 0x04: 0 */
    u16 p1;      /* 0x06: 10 */
    u16 p2;      /* 0x08: 2 */
    u16 p3;      /* 0x0A: 0 */
    u16 p4;      /* 0x0C: 0 */
    u16 scaled;  /* 0x0E: stat scaled by the character's percentage */
    u32 sprite;  /* 0x10: owner sprite */
    u8 _14[2];
    u16 p5;      /* 0x16: 5 */
    u16 timer;   /* 0x18: 0x7B */
};

/* Work/group state attached to the parent entity (+0x6C). */
struct GroupState {
    u32 x;        /* 0x00 (parent+0x04): world X, set from the camera */
    u32 y;        /* 0x04 (parent+0x08): world Y, camera + weapon offset */
    u32 vx;       /* 0x08 (parent+0x0C): horizontal velocity */
    u8 _C[0xC];
    u32 updateFn; /* 0x18 (parent+0x1C): previous update handler */
    u8 _1C[0x20];
    struct EffectPart *part; /* 0x3C (parent+0x40) */
};

void sub_08070748(u8 *entity)
{
    u8 *group;
    u8 *sprite;
    struct GroupState *groupState;
    u8 *playerData;
    u8 *scene;
    u16 stat;
    s16 character;
    u16 percent;
    u32 velocity;
    u8 *stateData;
    s32 *stateTable;

    group = *(u8 **)(entity + 0x6C);
    sprite = *(u8 **)(entity + 0x38);
    groupState = (struct GroupState *)(group + 4);
    playerData = gGameStatus;

    {
        struct EffectPart *part = allocEffectPart();
        groupState->part = part;
        if (part == 0) {
            sub_0806D2D0(entity);
            return;
        }
    }

    scene = gMainWorkspace;
    groupState->part->color = scene[0x1510] & 5;
    groupState->part->param2 = 2;
    groupState->part->param3 = 8;
    groupState->part->p0 = 0;
    groupState->part->p1 = 10;
    groupState->part->p2 = 2;
    groupState->part->p3 = 0;
    groupState->part->p4 = 0;

    stat = *(u16 *)(playerData + 0x2DE);
    character = *(s16 *)(playerData + 0x8C);
    percent = (character == 1) ? 0x2D : 0x20;
    groupState->part->scaled = sub_0806D62C(stat, percent);

    groupState->part->sprite = (u32)sprite;
    groupState->part->p5 = 5;
    groupState->part->timer = 0x7B;

    groupState->updateFn = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)sub_080718F4;
    *(u32 *)(sprite + 0x24) = 0x084733C4;

    *(u32 *)(group + 4) = *(u32 *)(scene + 0x1728);
    groupState->y = *(u32 *)(scene + 0x172C) + D_080E0098[*(u32 *)(entity + 0x7C) & 3];

    *(u32 *)(sprite + 0x1C) = 0x80000006;
    *(u16 *)(sprite + 0x00) = *(u16 *)(scene + 0x18C2);

    if (*(u16 *)(*(u8 **)(*(u8 **)(entity + 0x28) + 0x38) + 2) & 0x10)
        *(u16 *)(sprite + 2) |= 0x10;
    else
        *(u16 *)(sprite + 2) &= 0xFFEF;

    if (*(u16 *)(sprite + 2) & 0x10)
        velocity = 0xFFF80000;
    else
        velocity = 0x00080000;
    groupState->vx = velocity;

    sub_08005E80(0x8F);

    *(u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity + 0x19) = 0;
    stateTable = (s32 *)0x08671BB0;
    stateData = entity + 0x18;
    sub_080C31E4(stateData, entity + 0x22, *stateTable);
    {
        u8 *p = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        p[0x19]++;
    }
    {
        u8 *p = stateData + (s16)*(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(entity, *(void **)(*(u32 *)(entity + 0x14) + (*p) * 4));
    }
}
