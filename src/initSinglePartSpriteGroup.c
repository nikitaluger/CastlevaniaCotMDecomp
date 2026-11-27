extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *entity);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *timer, s32 handler, s32 data);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void releaseActorEffectParts(void);

#define SINGLE_PART_ANIM_DATA  0x084D24D8
#define SINGLE_PART_TIMER_DATA 0x084D271C

/* One render part handed out by allocEffectPart. */
struct GroupPart {
    u8 _0;
    u8 variant;       /* 0x01 */
    u8 layer;         /* 0x02 */
    u8 priority;      /* 0x03 */
    u16 gfxIndex;     /* 0x04 */
    u16 width;        /* 0x06 */
    u16 height;       /* 0x08 */
    u16 anim0;        /* 0x0A */
    u16 anim1;        /* 0x0C */
    u16 anim;         /* 0x0E */
    u32 owner;        /* 0x10 */
    u8 _14[2];
    u16 attr16;       /* 0x16 */
    u16 attr18;       /* 0x18 */
};

/* State block reached through the entity's +0x6C pointer (work starts at +4). */
struct GroupState {
    s32 x;                     /* 0x00: world X, 16.16 */
    s32 y;                     /* 0x04: world Y, 16.16 */
    s32 velX;                  /* 0x08 */
    s32 velY;                  /* 0x0C */
    u8 _10[0x18 - 0x10];
    u32 savedHandler;          /* 0x18: entity's previous update handler */
    u8 _1C[0x2C - 0x1C];
    struct GroupPart *part;    /* 0x2C */
    u32 unused30, unused34, unused38, unused3C;
};

/* Global fields used by the group setup. */
struct GroupWorkspace {
    u8 _0[0x14EF];
    u8 entityFlag;   /* 0x14EF */
    u8 _1[0x1510 - 0x14F0];
    u8 variantFlag;  /* 0x1510 */
    u8 _2[0x174C - 0x1511];
    u32 worldX;       /* 0x174C */
    u32 worldY;       /* 0x1750 */
};
extern struct GroupWorkspace gMainWorkspace;
extern u8 gGameStatus[];

/* Script command: allocate one render part for the entity's sprite group,
 * launch it with a flip-dependent offset and upward velocity, arm a one-frame
 * timer, then advance the entity's script. */
void initSinglePartSpriteGroup(u8 *entity) {
    u8 *group = *(u8 **)(entity + 0x6C);
    u8 *sprite = *(u8 **)(entity + 0x38);
    struct GroupState *state = (struct GroupState *)(group + 4);
    u8 *status = gGameStatus;
    struct GroupPart *part = allocEffectPart();
    u16 flip;
    u8 *script;
    u8 flags;

    state->part = part;
    if (part == NULL) {
        cleanupFailedEffectSpawn(entity);
        return;
    }
    state->unused30 = 0;
    state->unused34 = 0;
    state->unused38 = 0;
    state->unused3C = 0;

    part->variant = gMainWorkspace.variantFlag & 1;
    state->part->layer = 2;
    state->part->priority = 8;
    state->part->gfxIndex = status[0xC1 << 2];
    state->part->width = 6;
    state->part->height = 6;
    state->part->anim0 = 0;
    state->part->anim1 = 0;
    state->part->anim = scalePercentSaturate16(*(u16 *)(status + 0x2E2), 0x3F);
    state->part->attr16 = 5;
    state->part->attr18 = 0x4D;
    state->part->owner = (u32)sprite;

    state->savedHandler = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)releaseActorEffectParts;
    flags = gMainWorkspace.entityFlag;
    *(u8 *)(group + 0x55) = flags;
    *(u32 *)(sprite + 0x24) = SINGLE_PART_ANIM_DATA;

    startEffectTimer(group + 0x20, 0, SINGLE_PART_TIMER_DATA);

    {
        s32 baseX = gMainWorkspace.worldX;
        flip = *(u16 *)(sprite + 2) & 0x10;
        if (flip) {
            baseX += 0xFFF40000;
        } else {
            baseX += 0xC0000;
        }
        state->x = baseX;
    }
    state->y = gMainWorkspace.worldY + 0xFFF00000;

    {
        s32 mask;
        flip = *(u16 *)(sprite + 2) & 0x10;
        mask = 0x20000;
        if (flip) {
            mask = 0xFFFE0000;
        }
        state->velX = mask;
    }
    state->velY = 0xFFFC0000;

    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = 0;
    {
        s32 *cmdTable = (s32 *)0x08671BB0;
        script = entity + 0x18;
        sub_080C31E4(script, entity + 0x22, *cmdTable);
    }
    {
        u8 *entryPtr = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        *(u8 *)(entryPtr + 0x19) = (u8)(*(u8 *)(entryPtr + 0x19) + 1);
    }
    {
        u8 *entryPtr = script + (s16)*(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)((u32)(*entryPtr) * 4 + *(u32 *)(entity + 0x14)));
    }
}
