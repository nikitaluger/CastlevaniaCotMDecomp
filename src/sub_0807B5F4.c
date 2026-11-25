/* Spawns the large rotating effect sprite: allocates the child effect record,
 * sets its colour, size and scaled stat, places it above the camera, derives
 * its direction vector from the owner's facing, installs the effect's update
 * handler, then advances the parent's state machine. */
extern void *sub_08016190(void);              /* alloc effect record */
extern void sub_0806D2D0(void *);             /* bail out / release entity */
extern s16 sub_0806D62C(u16, s32);            /* scale value by percent */
extern void sub_08003A6C(void *, s32, void *); /* start one-frame timer record */
extern void sub_080C31E0(void *, void *);     /* indirect call */
extern void sub_080C31E4(void *, void *, s32); /* indirect call */
extern void sub_0808449C(void);               /* effect release handler */
extern void sub_080722E0(void *, u8);         /* angle -> direction vector */
extern void sub_08005E80(s32);                /* play sound */

struct S_02025FF0 {
    u8 _0[0x14EF];
    u8 b14EF;      /* 0x14EF: previous game mode */
    u8 _1[0x1510 - 0x14F0];
    u8 b1510;      /* 0x1510: colour/palette selector */
    u8 _2[0x1728 - 0x1511];
    u32 f1728;     /* 0x1728: camera X */
    u32 f172C;     /* 0x172C: camera Y */
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_00001728;   /* address constant for the camera X offset */
extern u8 D_02025368[]; /* game/player data */

/* 0x34-byte effect record allocated by sub_08016190. */
struct EffectPart {
    u8 mode;     /* 0x00 */
    u8 color;    /* 0x01: palette/colour index */
    u8 param2;   /* 0x02: 2 */
    u8 param3;   /* 0x03: 8 */
    u16 p0;      /* 0x04: base tile */
    u16 p1;      /* 0x06: 1 */
    u16 p2;      /* 0x08: 1 */
    u16 p3;      /* 0x0A: 0 */
    u16 p4;      /* 0x0C: 0 */
    u16 scaled;  /* 0x0E: stat scaled by percentage */
    u32 sprite;  /* 0x10: owner sprite */
    u8 _14[2];
    u16 p5;      /* 0x16: 0x0F */
    u16 timer;   /* 0x18: 0x5E */
};

/* Work/group state attached to the parent entity (+0x6C). */
struct GroupState {
    u8 _0[4];
    u32 y;        /* 0x04 (parent+0x08): world Y */
    u32 vx;       /* 0x08 (parent+0x0C): direction vector X */
    u32 vy;       /* 0x0C (parent+0x10): direction vector Y */
    u8 _1[0x14 - 0x10];
    u32 spinTime; /* 0x14 (parent+0x18) */
    u32 updateFn; /* 0x18 (parent+0x1C): previous update handler */
    u8 _2[0x2C - 0x1C];
    struct EffectPart *part; /* 0x2C (parent+0x30) */
    u32 part2;    /* 0x30 */
    u32 part3;    /* 0x34 */
    u32 part4;    /* 0x38 */
    u32 part5;    /* 0x3C */
    u32 spin;     /* 0x40 (parent+0x44) */
    u8 _3[0x48 - 0x44];
    u32 radius;   /* 0x48 (parent+0x4C) */
    u8 _4[0x54 - 0x4C];
    u32 angle;    /* 0x54 (parent+0x58) */
};

void sub_0807B5F4(u8 *entity) {
    u8 *parent = *(u8 **)(entity + 0x6C);
    struct GroupState *state = (struct GroupState *)(parent + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *dataTable = D_02025368;
    struct EffectPart *child = sub_08016190();
    u8 prevMode;
    u16 flipMask;
    u16 scale;
    u32 dirStep;
    s32 *stateTable;
    u8 *stateData;

    state->part = child;
    if (child == NULL) {
        sub_0806D2D0(entity);
        return;
    }
    state->part2 = 0;
    state->part3 = 0;
    state->part4 = 0;
    state->part5 = 0;

    child->color = D_02025FF0.b1510 & 1;
    state->part->param2 = 2;
    state->part->param3 = 8;
    state->part->p0 = dataTable[0xC1 << 2];
    state->part->p1 = 1;
    state->part->p2 = 1;
    state->part->p3 = 0;
    state->part->p4 = 0;
    state->part->scaled = sub_0806D62C(*(u16 *)(dataTable + 0x2E2), 0x47);
    state->part->p5 = 0x0F;
    state->part->timer = 0x5E;
    state->part->sprite = (u32)sprite;

    state->updateFn = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)sub_0808449C;
    prevMode = D_02025FF0.b14EF;
    *(u8 *)(parent + 0x55) = prevMode;

    scale = 0x400;
    *(u16 *)(sprite + 4) = scale;
    *(u16 *)(sprite + 6) = scale;
    *(u16 *)(sprite + 8) = 0;
    *(u32 *)(sprite + 0x24) = 0x084E1738;

    sub_08003A6C(parent + 0x20, 0, (void *)0x084E1758);

    *(u32 *)(parent + 4) = *(u32 *)((u8 *)&D_02025FF0 + (u32)&D_00001728);
    state->y = D_02025FF0.f172C + 0xFFEC0000;

    state->spin = 0x20000;

    flipMask = *(u16 *)(sprite + 2) & 0x10;
    dirStep = flipMask;
    dirStep = -(s32)dirStep;
    dirStep = (u32)((s32)dirStep >> 31);
    dirStep = dirStep & 0x80;
    *(u8 *)(parent + 0x48) = dirStep;

    sub_080722E0(state, *(u8 *)(parent + 0x48));

    state->radius = 0x100;
    state->angle = 0;
    sub_08005E80(0x144);

    state->spinTime = 0x0C;

    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = 0;
    stateTable = (s32 *)0x08671BB0;
    stateData = entity + 0x18;
    sub_080C31E4(stateData, entity + 0x22, *stateTable);
    {
        u8 *p = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        *(u8 *)(p + 0x19) = (u8)(*(u8 *)(p + 0x19) + 1);
    }
    {
        u8 *p = stateData + (s16)*(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(entity, *(void **)((u32)(*p) * 4 + *(u32 *)(entity + 0x14)));
    }
}
