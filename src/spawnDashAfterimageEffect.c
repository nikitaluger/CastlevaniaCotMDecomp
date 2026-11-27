/* Spawns the dash afterimage effect: allocates an effect part, sets its colour,
 * size and scaled stat parameters, places it at the camera with a horizontal
 * velocity opposite the owner's facing, installs the release handler, plays the
 * effect sound, then advances the parent's state machine. */
extern void *allocEffectPart(void);              /* allocate an effect part */
extern void cleanupFailedEffectSpawn(void *);    /* bail out / release entity */
extern u16 scalePercentSaturate16(u16, s32);     /* scale a value by a percentage */
extern void playSound(u16);                      /* play a sound effect */
extern void _call_via_r2(void *, void *, s32);   /* indirect call through r2 */
extern void _call_via_r1(void *, void *);        /* indirect call through r1 */
extern void releaseEffectGroup(void);            /* effect release handler */
extern u8 gGameStatus[];    /* game/player data: +0x8C character, +0x2DE stat */
extern u8 gMainWorkspace[];    /* scene state: +0x1510 colour, +0x1728/0x172C camera, +0x18C2 sprite bits */
extern u32 gDashAfterimageYOffsets[];   /* per-weapon Y offsets */
extern u32 gScriptStepCallbackTable;

/* 0x34-byte effect part object allocated by allocEffectPart. */
struct DashAfterimagePart {
    u8 mode;     /* 0x00 */
    u8 color;    /* 0x01: palette/colour index */
    u8 layer;    /* 0x02 */
    u8 priority; /* 0x03 */
    u16 gfxA;    /* 0x04 */
    u16 affine0; /* 0x06 */
    u16 affine1; /* 0x08 */
    u16 affine2; /* 0x0A */
    u16 affine3; /* 0x0C */
    u16 scaled;  /* 0x0E: stat scaled by the character's percentage */
    u32 sprite;  /* 0x10: owner sprite */
    u8 _14[2];
    u16 tail;    /* 0x16 */
    u16 timer;   /* 0x18 */
};

/* Work state reached through the entity's +0x6C pointer (extra + 4). */
struct DashAfterimageWork {
    u32 x;        /* 0x00: world X, set from the camera */
    u32 y;        /* 0x04: world Y, camera + weapon offset */
    u32 vx;       /* 0x08: horizontal velocity */
    u8 _C[0xC];
    u32 updateFn; /* 0x18: previous update handler */
    u8 _1C[0x20];
    struct DashAfterimagePart *part; /* 0x3C */
};

void spawnDashAfterimageEffect(u8 *entity)
{
    u8 *workSlot;
    u8 *sprite;
    struct DashAfterimageWork *work;
    u8 *gameStatus;
    u8 *workspace;
    u16 baseStat;
    s16 characterId;
    u16 scalePercent;
    u32 velocity;
    u8 *stepBase;
    s32 *handlerTable;

    workSlot = *(u8 **)(entity + 0x6C);
    sprite = *(u8 **)(entity + 0x38);
    work = (struct DashAfterimageWork *)(workSlot + 4);
    gameStatus = gGameStatus;

    {
        struct DashAfterimagePart *part = allocEffectPart();
        work->part = part;
        if (part == 0) {
            cleanupFailedEffectSpawn(entity);
            return;
        }
    }

    workspace = gMainWorkspace;
    work->part->color = workspace[0x1510] & 5;
    work->part->layer = 2;
    work->part->priority = 8;
    work->part->gfxA = 0;
    work->part->affine0 = 10;
    work->part->affine1 = 2;
    work->part->affine2 = 0;
    work->part->affine3 = 0;

    baseStat = *(u16 *)(gameStatus + 0x2DE);
    characterId = *(s16 *)(gameStatus + 0x8C);
    scalePercent = (characterId == 1) ? 0x2D : 0x20;
    work->part->scaled = scalePercentSaturate16(baseStat, scalePercent);

    work->part->sprite = (u32)sprite;
    work->part->tail = 5;
    work->part->timer = 0x7B;

    work->updateFn = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)releaseEffectGroup;
    *(u32 *)(sprite + 0x24) = 0x084733C4;

    *(u32 *)(workSlot + 4) = *(u32 *)(workspace + 0x1728);
    work->y = *(u32 *)(workspace + 0x172C) + gDashAfterimageYOffsets[*(u32 *)(entity + 0x7C) & 3];

    *(u32 *)(sprite + 0x1C) = 0x80000006;
    *(u16 *)(sprite + 0x00) = *(u16 *)(workspace + 0x18C2);

    if (*(u16 *)(*(u8 **)(*(u8 **)(entity + 0x28) + 0x38) + 2) & 0x10)
        *(u16 *)(sprite + 2) |= 0x10;
    else
        *(u16 *)(sprite + 2) &= 0xFFEF;

    if (*(u16 *)(sprite + 2) & 0x10)
        velocity = 0xFFF80000;
    else
        velocity = 0x00080000;
    work->vx = velocity;

    playSound(0x8F);

    *(u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity + 0x19) = 0;
    handlerTable = (s32 *)0x08671BB0;
    stepBase = entity + 0x18;
    _call_via_r2(stepBase, entity + 0x22, *handlerTable);
    {
        u8 *step = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        step[0x19]++;
    }
    {
        u8 *step = stepBase + (s16)*(s16 *)(entity + 0x22) * 2;
        _call_via_r1(entity, *(void **)(*(u32 *)(entity + 0x14) + (*step) * 4));
    }
}
