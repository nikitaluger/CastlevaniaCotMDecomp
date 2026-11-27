/* Spawns the kind-0x68 multi-part scripted object: allocates one sprite and three
 * render-part definitions, initialises their graphics/affine parameters, sets the
 * sprite attributes and start position, installs the object's own per-frame update
 * handler, then advances the parent's state index. */
extern void *allocSpriteObject(void);                            /* alloc sprite object */
extern s32 allocWorkSlot(u8 *, s32, s32, s32);               /* alloc + clear slot */
extern s32 findKindIndex(s32);                               /* kind -> active slot */
extern void installUpdateHandler(u8 *, u8 *, void *);               /* install update handler */
extern void *allocEffectPart(void);                            /* alloc effect part */
extern void initSpriteGfx(u8 *, u8 *, s32, s32);             /* init sprite graphics */
extern void destroyMultiPartObject(void);                             /* per-frame update */
extern s32 _call_via_r1(u8 *, s32);                         /* indirect call */
extern s32 _call_via_r2(u8 *, u8 *, s32);                   /* indirect call */

/* Render part definition (0x34 bytes) allocated by allocEffectPart. */
struct Effect {
    u8 mode;      /* 0x00: playback mode */
    u8 active;    /* 0x01: 0 while spawning */
    u8 param2;    /* 0x02: 8 */
    u8 param3;    /* 0x03: 1 */
    u16 tile;     /* 0x04: base tile id from gEffectGfxTable */
    u16 p0;       /* 0x06: per-part parameters from gEffectPartParams */
    u16 p1;       /* 0x08 */
    u16 p2;       /* 0x0A */
    u16 p3;       /* 0x0C */
    u16 tile2;    /* 0x0E: secondary tile id from gEffectGfxTable */
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
extern struct S_02025FF0 gMainWorkspace;

/* 0x28-byte per-kind graphics descriptor. */
struct EffectDesc {
    u8 _0[0xC];
    u16 baseTile; /* 0x0C: tile id for this kind */
    u16 extra;    /* 0x0E: second tile id for this kind */
    u8 _10[0x28 - 0x10];
};
extern struct EffectDesc gEffectGfxTable[];
extern u16 gEffectPartParams[];  /* per-part affine/offset parameters, 4 per part */
extern u32 gScriptStepCallbackTable;

/* Build and register the three render parts, then hand control to the object's
 * destruction handler and step the script forward. */
void scriptCmdSpawnMultiPartObject(struct Entity *entity) {
    u8 *sprite;
    struct State *state;
    u8 *gfxSlot;
    u8 *partSlots;
    u8 *paramBytes;
    s32 kindSlot;
    u32 zeroByte;
    struct Effect *mainPart;
    struct Effect *part1;
    struct Effect *part2;
    u16 *params;
    u32 *callbackTable;

    sprite = allocSpriteObject();
    if (sprite == NULL)
        goto fail;
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x50, 0);
    if (entity->state == NULL)
        goto fail;
    *(u32 *)(sprite + 0x1C) = 0x80000009;
    sprite[0x2A] &= 0xBF;
    state = entity->state;
    gfxSlot = (u8 *)state + 0x34;
    partSlots = (u8 *)state + 0x48;
    installUpdateHandler((u8 *)entity, (u8 *)state, (void *)destroyMultiPartObject);
    state->kind = SPRITE_KIND_MULTI_PART;
    kindSlot = findKindIndex(SPRITE_KIND_MULTI_PART);
    state->slot = kindSlot;
    if ((s32)(kindSlot << 16) < 0)
        goto fail;
    *(u16 *)sprite |= gMainWorkspace.f18C2;
    state->y = 0xF0 << 0x11;   /* start below the screen */
    initSpriteGfx(sprite, gfxSlot, 0, 4);

    params = gEffectPartParams;

    mainPart = allocEffectPart();
    state->mainPart = mainPart;
    if (mainPart == NULL)
        goto fail;
    state->mainPart->active = 0;
    state->mainPart->param2 = 8;
    state->mainPart->param3 = 1;
    state->mainPart->tile = gEffectGfxTable[state->kind].baseTile;
    state->mainPart->p0 = params[0];
    state->mainPart->p1 = params[1];
    state->mainPart->p2 = params[2];
    state->mainPart->p3 = params[3];
    state->mainPart->tile2 = gEffectGfxTable[state->kind].extra;
    state->mainPart->sprite = (u32)sprite;

    paramBytes = (u8 *)params + 8;
    part1 = allocEffectPart();
    *(struct Effect **)(partSlots) = part1;
    if (part1 == NULL)
        goto fail;
    (*(struct Effect **)partSlots)->active = 0;
    (*(struct Effect **)partSlots)->param2 = 8;
    (*(struct Effect **)partSlots)->param3 = 1;
    (*(struct Effect **)partSlots)->tile = gEffectGfxTable[state->kind].baseTile;
    (*(struct Effect **)partSlots)->p0 = params[4];
    (*(struct Effect **)partSlots)->p1 = *(u16 *)(paramBytes + 2);
    (*(struct Effect **)partSlots)->p2 = *(u16 *)(paramBytes + 4);
    (*(struct Effect **)partSlots)->p3 = *(u16 *)(paramBytes + 6);
    (*(struct Effect **)partSlots)->tile2 = gEffectGfxTable[state->kind].extra;
    (*(struct Effect **)partSlots)->sprite = (u32)sprite;

    paramBytes = (u8 *)params + 0x10;
    part2 = allocEffectPart();
    *(struct Effect **)(partSlots + 4) = part2;
    if (part2 == NULL)
        goto fail;
    goto success;
fail:
    _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
    return;
success:
    (*(struct Effect **)(partSlots + 4))->active = 0;
    (*(struct Effect **)(partSlots + 4))->param2 = 8;
    (*(struct Effect **)(partSlots + 4))->param3 = 1;
    (*(struct Effect **)(partSlots + 4))->tile = gEffectGfxTable[state->kind].baseTile;
    (*(struct Effect **)(partSlots + 4))->p0 = params[8];
    (*(struct Effect **)(partSlots + 4))->p1 = *(u16 *)(paramBytes + 2);
    (*(struct Effect **)(partSlots + 4))->p2 = *(u16 *)(paramBytes + 4);
    (*(struct Effect **)(partSlots + 4))->p3 = *(u16 *)(paramBytes + 6);
    (*(struct Effect **)(partSlots + 4))->tile2 = gEffectGfxTable[state->kind].extra;
    (*(struct Effect **)(partSlots + 4))->sprite = (u32)sprite;

    *(u16 *)(sprite + 2) |= 0x400;
    *(u32 *)((u8 *)entity + 0x4C) = 0;
    entity->flags |= THREAD_FLAG_WAIT_SPRITE;
    zeroByte = 0;
    *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = zeroByte;
    callbackTable = &gScriptStepCallbackTable;
    {
        u8 *scriptByte = (u8 *)entity + 0x18;
        _call_via_r2(scriptByte, (u8 *)entity + 0x22, *callbackTable);
        *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) + 1;
        scriptByte = scriptByte + 2 * entity->stateIndex;
        _call_via_r1((u8 *)entity, *(s32 *)((u32)(*(u32 **)((u8 *)entity + 0x14)) + 4 * (*scriptByte)));
    }
}
