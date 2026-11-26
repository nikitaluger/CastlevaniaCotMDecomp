/* Spawns the fixed-kind projectile effect from the parent entity: allocates the
 * sprite and its effect definition, copies the animation parameters, sets its world
 * position from the parent's position reference, gives it a horizontal direction,
 * speed and lifetime, then advances the parent's state index. */
extern void *allocSpriteObject(void);                            /* alloc sprite object */
extern s32 allocWorkSlot(u8 *, s32, s32, s32);               /* alloc + clear slot */
extern s32 findKindIndex(s32);                               /* kind -> active slot */
extern void initSpriteGraphics(u8 *, u8 *, s32);                  /* init sprite gfx */
extern void *allocEffectPart(void);                            /* alloc effect def */
extern void setAnimationFrame(u8 *, u8 *, s32, s32);             /* set animation frame */
extern void registerScriptObject(u8 *, s32);                        /* attach registry data */
extern s32 signOf(s32);                               /* sign(camera - x) */
extern s32 _call_via_r1(u8 *, s32);                         /* indirect call */
extern s32 _call_via_r2(u8 *, u8 *, s32);                   /* indirect call */

/* Per-effect definition (0x34 bytes) allocated by allocEffectPart. */
struct Effect {
    u8 mode;      /* 0x00: playback mode, bit 1 preserved by setAnimationFrame */
    u8 active;    /* 0x01: 0 while spawning */
    u8 param2;    /* 0x02: 8 */
    u8 param3;    /* 0x03: 1 */
    u16 gfxA;     /* 0x04: tile id from the effect table */
    u16 affine0;  /* 0x06: affine/OAM parameters from a constant table */
    u16 affine1;  /* 0x08 */
    u16 affine2;  /* 0x0A */
    u16 affine3;  /* 0x0C */
    u16 gfxB;     /* 0x0E: second tile id from the effect table */
    u32 sprite;   /* 0x10: owner sprite */
    u16 timer;    /* 0x14 */
};

/* Script state of an active entity (the entity's +0x3C field). */
struct State {
    u8 _0[8];
    s32 x;        /* 0x08: world X, 16.16 */
    s32 y;        /* 0x0C: world Y, 16.16 */
    u32 f10;      /* 0x10: propulsion values used by other spawn kinds */
    u32 f14;      /* 0x14 */
    u32 lifetime; /* 0x18: effect duration in frames */
    s16 kind;     /* 0x1C: effect kind (SPRITE_KIND_PROJECTILE here) */
    u8 _1E[4];
    s16 slot;     /* 0x22: active effect slot index */
    u32 updateFn; /* 0x24: previous per-frame update handler, saved here */
    struct Effect *effect; /* 0x28: attached effect definition */
};

struct Ref {
    s16 x;
    s16 y;
};

struct RefHolder {
    u8 _0[4];
    struct Ref *position; /* position reference used for the spawn point */
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
    s16 x;
    u8 _4E[6];
    s16 y;
    u8 _56[0xAC - 0x56];
    struct RefHolder *refHolder; /* 0xAC */
};

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 f18A8;     /* 0x18A8: video-frame counter used for the BG scroll rows */
    u8 _18A9[0x19];
    u16 f18C2;    /* 0x18C2: sprite priority/blend bits */
};
extern struct S_02025FF0 gMainWorkspace;

struct S_02021E90 {
    u8 _0[0x1278];
    u32 f1278;    /* per-frame BG scroll X buffers */
    u32 f127C;    /* per-frame BG scroll Y buffers */
};
extern struct S_02021E90 gCameraState;

/* 20-byte per-kind effect table: gfxA, lifetime, gfxB. */
struct EffectDef {
    u16 gfxA;
    s16 lifetime;
    u16 gfxB;
    u8 _6[0x14 - 6];
};
extern struct EffectDef gSpriteKindTable[];
extern u16 D_080CE7DC[];  /* affine/OAM constants copied into the effect */
extern u8 gSpriteAnimDataTable[];   /* per-kind animation descriptor table (12-byte entries) */

inline u16 *attrOf(u8 *sprite)
{
    return (u16 *) sprite;
}

void scriptCmdSpawnProjectile(struct Entity *entity)
{
    u8 *sprite;
    s16 unused;
    struct State *state;
    u8 *gfxInit;
    u8 *effect;
    s32 slot;
    u32 attrs;
    u32 zero;
    u8 *coordBase;
    u8 *effectTable;
    s32 *tablePtr;
    struct RefHolder *refHolder;
    u8 *stateData;
    s32 angle;

    refHolder = entity->refHolder;
    sprite = allocSpriteObject();
    state = NULL;
    effect = NULL;
    slot = 0;
    if ((((sprite == NULL) || ((entity->sprite = sprite, allocWorkSlot((u8 *) entity, 0, 0x98, 0), state = entity->state, state == NULL))) || ((gfxInit = ((u8 *) state) + 0x34, state->updateFn = *((u32 *) (((u8 *) entity) + 0x24)), *((u32 *) (((u8 *) entity) + 0x24)) = 0x08020E45, zero = 0, state->kind = SPRITE_KIND_PROJECTILE, effectTable = (u8 *) gSpriteKindTable, state->lifetime = ((struct EffectDef *) (effectTable + (0xA0 * 4)))[0].lifetime, state->x = refHolder->position->x << 16, state->y = refHolder->position->y << 16, slot = findKindIndex(SPRITE_KIND_PROJECTILE), state->slot = slot, ((s32) (slot << 16)) < 0))) || ((initSpriteGraphics(sprite, gfxInit, ((s32) gSpriteAnimDataTable) + (state->kind * 0xC)), effect = allocEffectPart(), state->effect = (struct Effect *) effect, effect == NULL)))
    {
        sub_080C31E0((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24)));
        return;
    }
    state->effect->active = 0;
    state->effect->param2 = 8;
    state->effect->param3 = 1;
    state->effect->gfxA = ((struct EffectDef *) effectTable)[state->kind].gfxA;
    state->effect->affine0 = D_080CE7DC[0];
    state->effect->affine1 = D_080CE7DC[1];
    state->effect->affine2 = D_080CE7DC[2];
    state->effect->affine3 = D_080CE7DC[3];
    state->effect->gfxB = ((struct EffectDef *) effectTable)[state->kind].gfxB;
    state->effect->sprite = (u32) sprite;
    state->effect->timer = zero;
    attrs = ((*attrOf(sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) state) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) state) + 0x22))) + 8) << 12));
    *attrOf(sprite) = attrs;
    *((u16 *) sprite) = attrs | gMainWorkspace.f18C2;
    *((u32 *) (sprite + 0x1C)) = 0x8000000A;
    coordBase = (u8 *) (&gCameraState);
    {
        u32 k = 0x1278;
        *((u32 *) (sprite + 0x14)) = state->x - (((*((u32 *) ((coordBase + k) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 k = 0x127C;
        *((u32 *) (sprite + 0x18)) = state->y - (((*((u32 *) ((coordBase + k) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
    }
    {
        u8 *p = ((u8 *) state) + 0x48;   /* hit/impact block, cleared */
        *((u32 *) p) = zero;
        *((u16 *) (p + 4)) = zero;
        *((u16 *) (p + 6)) = zero;
        *((u16 *) (p + 8)) = zero;
        *((u16 *) (p + 0xA)) = zero;
    }
    {
        u8 *q = ((u8 *) state) + 0x6C;   /* movement block: flags, angle, speed, accel, lifetime */
        *((u32 *) q) = zero;
        angle = (signOf(state->x) >> 31) & 0x8000;
        *((u32 *) (q + 4)) = angle;
        *((u32 *) (q + 8)) = zero;
        *((u32 *) (q + 0xC)) = 0x28000;
        *((u32 *) (q + 0x10)) = 0x2000;
        *((u32 *) (q + 0x14)) = 0x180;
    }
    setSpriteFlip(sprite, angle);   /* flip/priority for the travel direction */
    setAnimationFrame(sprite, gfxInit, 0, 1);
    registerScriptObject((u8 *) entity, 0);
    entity->flags |= THREAD_FLAG_WAIT_SPRITE;
    *((u8 *) ((((u8 *) entity) + (2 * entity->stateIndex)) + 0x19)) = 0;
    tablePtr = (s32 *) 0x08671BB0;
    stateData = ((u8 *) entity) + 0x18;
    _call_via_r2(stateData, ((u8 *) entity) + 0x22, *tablePtr);
    {
        u8 *p = (u8 *) ((2 * entity->stateIndex) + ((u32) entity));
        *((u8 *) (p + 0x19)) = (*((u8 *) (p + 0x19))) + 1;
    }
    {
        u8 *p = stateData + (2 * entity->stateIndex);
        _call_via_r1((u8 *) entity, *((s32 *) ((*((u8 **) (((u8 *) entity) + 0x14))) + ((*((u8 *) p)) * 4))));
    }
}
