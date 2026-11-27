extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void dispatchSavedSpriteHandler(void);

#define SPAWN_EFFECT_WORK_SLOT_SIZE 0x34
#define SPAWN_EFFECT_GFX_ID        0x80000007
#define SPAWN_EFFECT_FRAME_MASK    0xF
#define SPAWN_EFFECT_SCROLL_X      0x1278
#define SPAWN_EFFECT_SCROLL_Y      0x127C

/* Render layer installed on the spawned sprite, with fixed attributes. */
struct SpawnEffectLayer {
    u8 mode;        /* 0x00 */
    u8 kind;        /* 0x01 */
    u8 layer;       /* 0x02 */
    u8 priority;    /* 0x03 */
    u16 gfxIndex;   /* 0x04 */
    u16 anim0;      /* 0x06 */
    u16 anim1;      /* 0x08 */
    u16 anim2;      /* 0x0A */
    u16 anim3;      /* 0x0C */
    u16 palette;    /* 0x0E */
    void *object;   /* 0x10: owner sprite */
    u16 timer;      /* 0x14 */
};

/* Work state allocated at the owner's +0x3C slot. */
struct SpawnEffectWork {
    u8 _0[8];
    s32 x;                          /* 0x08: world X, 16.16 */
    s32 y;                          /* 0x0C: world Y, 16.16 */
    u8 _10[8];
    s32 state;                      /* 0x18 */
    u8 _1C[8];
    s32 savedHandler;               /* 0x24: previous update handler */
    struct SpawnEffectLayer *layer; /* 0x28 */
};

/* Spawn definition reached through the owner's +0xAC pointer. */
struct SpawnEffectDef {
    u8 _0[4];
    s16 *coords; /* 0x04: spawn X/Y plus the frame-parameter word */
};

/* Script thread that requested the spawn. */
struct SpawnEffectOwner {
    u8 _0[2];
    u16 flags;                      /* 0x02: EFFECT_SPRITE_READY on success */
    u8 _4[0x10];
    u32 *handlerTable;              /* 0x14: script command handlers */
    u8 _18[0xA];
    s16 stepIndex;                  /* 0x22 */
    s32 handler;                    /* 0x24: current update handler */
    u8 _28[0x10];
    void *sprite;                   /* 0x38 */
    struct SpawnEffectWork *work;   /* 0x3C */
    u8 _40[0x6C];
    struct SpawnEffectDef *definition; /* 0xAC */
};

extern u8 gCameraState[];
extern struct {
    u8 _0[0x18A8];
    u8 frameCounter;
    u8 _18A9[0x19];
    u16 gfxFlags;
} gMainWorkspace;

extern u16 gSpawnEffectFrameIds[];
extern u8 gSpawnEffectAnimData[];
extern s32 gMainObjTimerCallbacks[];

/* Script command: build a parameter-driven effect sprite for the calling
 * script thread. Allocates the sprite and its work state, seeds the work
 * coordinates from the owner's definition, installs a render layer with fixed
 * attributes, places the sprite against the camera scroll, selects its
 * starting animation frame from the spawn parameter and advances the script. */
void scriptCmdSpawnAnimatedSprite(struct SpawnEffectOwner *owner)
{
    struct SpawnEffectDef *def;
    void *sprite;
    struct SpawnEffectWork *work;
    s16 *coords;
    struct SpawnEffectLayer *layer;
    u32 zero;
    s32 *cmdTable;
    u8 *stepLog;

    def = owner->definition;
    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;

    owner->sprite = sprite;
    allocWorkSlot(owner, 0, SPAWN_EFFECT_WORK_SLOT_SIZE, 0);
    work = owner->work;
    if (work == 0)
        goto fail;

    work->savedHandler = owner->handler;
    owner->handler = (s32)dispatchSavedSpriteHandler;
    work->state = 1;

    coords = def->coords;
    work->x = (s32)coords[0] << 16;
    work->y = (s32)coords[1] << 16;

    layer = allocEffectPart();
    work->layer = layer;
    if (layer != 0)
        goto cont;

fail:
    sub_080C31E0(owner, owner->handler);
    goto end;

cont:
    zero = 0;
    layer->kind = 4;
    work->layer->layer = 0x80;
    work->layer->priority = 0;
    work->layer->gfxIndex = zero;
    work->layer->anim0 = 6;
    work->layer->anim1 = 6;
    work->layer->anim2 = zero;
    work->layer->anim3 = zero;
    work->layer->palette = zero;
    work->layer->object = sprite;
    work->layer->timer = 0;

    *(u16 *)sprite |= gMainWorkspace.gfxFlags;
    *(u32 *)((u8 *)sprite + 0x1C) = SPAWN_EFFECT_GFX_ID;

    {
        u8 *scrollBase = (u8 *)&gCameraState;
        { u32 offset = SPAWN_EFFECT_SCROLL_X; *(u32 *)((u8 *)sprite + 0x14) = work->x - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 offset = SPAWN_EFFECT_SCROLL_Y; *(u32 *)((u8 *)sprite + 0x18) = work->y - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    }

    *(u32 *)((u8 *)sprite + 0x24) = (u32)gSpawnEffectAnimData;
    *(u16 *)((u8 *)sprite + 0x28) = gSpawnEffectFrameIds[def->coords[3] & SPAWN_EFFECT_FRAME_MASK];

    owner->flags |= EFFECT_SPRITE_READY;

    *(u8 *)((u8 *)owner + owner->stepIndex * 2 + 0x19) = zero;

    cmdTable = gMainObjTimerCallbacks;
    stepLog = (u8 *)owner + 0x18;
    sub_080C31E4(stepLog, &owner->stepIndex, *cmdTable);

    *(u8 *)((u8 *)owner + owner->stepIndex * 2 + 0x19) += 1;

    stepLog += owner->stepIndex * 2;
    sub_080C31E0(owner, owner->handlerTable[*stepLog]);

end:
    return;
}
