/* Spawns the kind-0x68 multi-part scripted object: allocates one sprite and three
 * render-part definitions, initialises their graphics/affine parameters, sets the
 * sprite attributes and start position, installs the object's own per-frame update
 * handler, then advances the parent's state index. */
extern void *sub_0800355C(void);                            /* alloc sprite object */
extern s32 sub_0800168C(u8 *, s32, s32, s32);               /* alloc + clear slot */
extern s32 sub_08013C2C(s32);                               /* kind -> active slot */
extern void sub_08014288(u8 *, u8 *, void *);               /* install update handler */
extern void *sub_08016190(void);                            /* alloc effect part */
extern void sub_080BE528(u8 *, u8 *, s32, s32);             /* init sprite graphics */
extern void sub_080BD4E0(void);                             /* per-frame update */
extern s32 _call_via_r1(u8 *, s32);                         /* indirect call */
extern s32 _call_via_r2(u8 *, u8 *, s32);                   /* indirect call */

/* Render part definition (0x34 bytes) allocated by sub_08016190. */
struct Effect {
    u8 mode;      /* 0x00: playback mode */
    u8 active;    /* 0x01: 0 while spawning */
    u8 param2;    /* 0x02: 8 */
    u8 param3;    /* 0x03: 1 */
    u16 tile;     /* 0x04: base tile id from D_080CBDD0 */
    u16 p0;       /* 0x06: per-part parameters from D_08102F40 */
    u16 p1;       /* 0x08 */
    u16 p2;       /* 0x0A */
    u16 p3;       /* 0x0C */
    u16 tile2;    /* 0x0E: secondary tile id from D_080CBDD0 */
    u32 sprite;   /* 0x10: owner sprite */
    u16 timer;    /* 0x14 */
};

/* Script state of the spawned object (the entity's +0x3C field). */
struct State {
    u8 _0[8];
    s32 x;        /* 0x08: world X, 16.16 */
    s32 y;        /* 0x0C: world Y, 16.16 */
    u32 f10;      /* 0x10 */
    u32 f14;      /* 0x14 */
    u32 lifetime; /* 0x18 */
    s16 kind;     /* 0x1C: object kind (0x68 here) */
    u8 _1E[4];
    s16 slot;     /* 0x22: active slot index */
    u32 updateFn; /* 0x24: previous update handler, saved here */
    struct Effect *mainPart; /* 0x28: first render part; parts 2/3 at +0x48/+0x4C */
};

struct Entity {
    u8 _0[2];
    u16 flags;    /* 0x02: control flags */
    u8 _4[0x22 - 4];
    s16 stateIndex;
    u8 _24[0x38 - 0x24];
    u8 *sprite;   /* 0x38 */
    struct State *state; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s32 x;        /* 0x4C */
};

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 f18A8;
    u8 _18A9[0x19];
    u16 f18C2;    /* 0x18C2: sprite priority/blend bits */
};
extern struct S_02025FF0 D_02025FF0;

/* 0x28-byte per-kind graphics descriptor. */
struct EffectDesc {
    u8 _0[0xC];
    u16 baseTile; /* 0x0C: tile id for this kind */
    u16 extra;    /* 0x0E: second tile id for this kind */
    u8 _10[0x28 - 0x10];
};
extern struct EffectDesc D_080CBDD0[];
extern u16 D_08102F40[];  /* per-part affine/offset parameters, 4 per part */
extern u32 D_08671BB0;

void sub_080BD040(struct Entity *entity) {
    u8 *sprite;
    struct State *state;
    u8 *gfxInit;
    u8 *parts;
    u8 *params;
    s32 slot;
    u32 zero;
    struct Effect *mainPart;
    struct Effect *part1;
    struct Effect *part2;
    u16 *partTable;
    u32 *tablePtr;

    sprite = sub_0800355C();
    if (sprite == NULL)
        goto fail;
    entity->sprite = sprite;
    sub_0800168C((u8 *)entity, 0, 0x50, 0);
    if (entity->state == NULL)
        goto fail;
    *(u32 *)(sprite + 0x1C) = 0x80000009;
    sprite[0x2A] &= 0xBF;
    state = entity->state;
    gfxInit = (u8 *)state + 0x34;
    parts = (u8 *)state + 0x48;
    sub_08014288((u8 *)entity, (u8 *)state, (void *)sub_080BD4E0);
    state->kind = 0x68;
    slot = sub_08013C2C(0x68);
    state->slot = slot;
    if ((s32)(slot << 16) < 0)
        goto fail;
    *(u16 *)sprite |= D_02025FF0.f18C2;
    state->y = 0xF0 << 0x11;   /* start below the screen */
    sub_080BE528(sprite, gfxInit, 0, 4);

    partTable = D_08102F40;

    mainPart = sub_08016190();
    state->mainPart = mainPart;
    if (mainPart == NULL)
        goto fail;
    state->mainPart->active = 0;
    state->mainPart->param2 = 8;
    state->mainPart->param3 = 1;
    state->mainPart->tile = D_080CBDD0[state->kind].baseTile;
    state->mainPart->p0 = partTable[0];
    state->mainPart->p1 = partTable[1];
    state->mainPart->p2 = partTable[2];
    state->mainPart->p3 = partTable[3];
    state->mainPart->tile2 = D_080CBDD0[state->kind].extra;
    state->mainPart->sprite = (u32)sprite;

    params = (u8 *)partTable + 8;
    part1 = sub_08016190();
    *(struct Effect **)(parts) = part1;
    if (part1 == NULL)
        goto fail;
    (*(struct Effect **)parts)->active = 0;
    (*(struct Effect **)parts)->param2 = 8;
    (*(struct Effect **)parts)->param3 = 1;
    (*(struct Effect **)parts)->tile = D_080CBDD0[state->kind].baseTile;
    (*(struct Effect **)parts)->p0 = partTable[4];
    (*(struct Effect **)parts)->p1 = *(u16 *)(params + 2);
    (*(struct Effect **)parts)->p2 = *(u16 *)(params + 4);
    (*(struct Effect **)parts)->p3 = *(u16 *)(params + 6);
    (*(struct Effect **)parts)->tile2 = D_080CBDD0[state->kind].extra;
    (*(struct Effect **)parts)->sprite = (u32)sprite;

    params = (u8 *)partTable + 0x10;
    part2 = sub_08016190();
    *(struct Effect **)(parts + 4) = part2;
    if (part2 == NULL)
        goto fail;
    goto success;
fail:
    _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
    return;
success:
    (*(struct Effect **)(parts + 4))->active = 0;
    (*(struct Effect **)(parts + 4))->param2 = 8;
    (*(struct Effect **)(parts + 4))->param3 = 1;
    (*(struct Effect **)(parts + 4))->tile = D_080CBDD0[state->kind].baseTile;
    (*(struct Effect **)(parts + 4))->p0 = partTable[8];
    (*(struct Effect **)(parts + 4))->p1 = *(u16 *)(params + 2);
    (*(struct Effect **)(parts + 4))->p2 = *(u16 *)(params + 4);
    (*(struct Effect **)(parts + 4))->p3 = *(u16 *)(params + 6);
    (*(struct Effect **)(parts + 4))->tile2 = D_080CBDD0[state->kind].extra;
    (*(struct Effect **)(parts + 4))->sprite = (u32)sprite;

    *(u16 *)(sprite + 2) |= 0x400;
    *(u32 *)((u8 *)entity + 0x4C) = 0;
    entity->flags |= 0x1000;
    zero = 0;
    *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = zero;
    tablePtr = &D_08671BB0;
    {
        u8 *q = (u8 *)entity + 0x18;
        _call_via_r2(q, (u8 *)entity + 0x22, *tablePtr);
        *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) + 1;
        q = q + 2 * entity->stateIndex;
        _call_via_r1((u8 *)entity, *(s32 *)((u32)(*(u32 **)((u8 *)entity + 0x14)) + 4 * (*q)));
    }
}
