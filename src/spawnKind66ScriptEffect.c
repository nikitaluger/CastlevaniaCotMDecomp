struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;

/* One render layer allocated by allocEffectPart. */
struct Kind66RenderLayer {
    u8 mode;         /* 0x00 */
    u8 kind;         /* 0x01: RENDER_PART_KIND */
    u8 layer;        /* 0x02 */
    u8 priority;     /* 0x03 */
    u16 gfxIndex;    /* 0x04: tile id from gEffectGfxTable */
    u16 anim0;       /* 0x06 */
    u16 anim1;       /* 0x08 */
    u16 anim2;       /* 0x0A */
    u16 anim3;       /* 0x0C */
    u16 palette;     /* 0x0E: palette id from gEffectGfxTable */
    u32 sprite;      /* 0x10: owner sprite */
};

/* 0x48-byte work state in the script thread's slot at +0x3C. */
struct Kind66WorkState {
    u8 _0[8];
    u32 x;           /* 0x08: world X from the script */
    u32 y;           /* 0x0C: world Y from the script */
    u8 _10[0xC];
    s16 kind;        /* 0x1C: KIND66_EFFECT_KIND */
    u8 _1E[4];
    s16 animSlot;    /* 0x22: index returned by findKindIndex */
    u8 _24[4];
    struct Kind66RenderLayer *layer; /* 0x28 */
};

/* Script thread that owns the spawned effect. */
struct Kind66ScriptThread {
    u16 f0;
    u16 flags;                /* 0x02: KIND66_EFFECT_READY */
    u8 _4[0x14 - 4];
    void *scriptTable;        /* 0x14: handlers indexed by the step opcode */
    u8 _18[0x22 - 0x18];      /* 0x18: script opcode/timer stream */
    s16 step;                 /* 0x22: current script-step index */
    void *cleanup;            /* 0x24: callback run on failure */
    u8 _28[0x38 - 0x28];
    void *sprite;             /* 0x38 */
    void * volatile work;     /* 0x3C: work state above */
    u8 _40[0xC];
    u32 spawnX;               /* 0x4C */
    u8 _50[0xC];
    u32 spawnY;               /* 0x5C */
    u8 _60[0xC];
    s32 sizeParam;            /* 0x6C: fixed-point size (3.0 here) */
};

/* gEffectGfxTable record; this kind reads the tile/palette pair at +0x10/+0x12. */
struct Kind66GfxRecord {
    u8 _0[0x10];
    u16 gfx;      /* 0x10 */
    u16 palette;  /* 0x12 */
    u8 _14[0x14];
};
extern struct Kind66GfxRecord gEffectGfxTable[];
extern u16 gKind66LayerAttrs[];
extern char gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/*
 * Spawn a script-driven kind-0x66 effect: allocate its sprite and work block,
 * seed the animation and render layer from the shared tables, install the
 * per-frame updater, then clear and advance the script step. On any failure
 * the script's cleanup callback runs instead.
 */
void spawnKind66ScriptEffect(struct Kind66ScriptThread *actor) {
    s32 sprite;
    struct Kind66WorkState *work;
    u8 *animState;
    u16 *defaults;
    u32 kindIndex;
    u8 *scriptPtr;
    void **timerCallbacks;
    u8 *scriptEntry;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    actor->sprite = (void *)sprite;
    allocWorkSlot(actor, 0, KIND66_EFFECT_WORK_SIZE, 0);
    if (actor->work == NULL) goto fail;
    *((u32 *)(sprite + 0x1C)) = KIND66_EFFECT_GFX_ID;
    work = (struct Kind66WorkState *)actor->work;
    animState = ((u8 *)work) + 0x34;
    installUpdateHandler(actor, (u8 *)work, updateActorEffectSubObject);
    work->kind = KIND66_EFFECT_KIND;
    work->x = actor->spawnX;
    work->y = actor->spawnY;
    actor->sizeParam = KIND66_EFFECT_SCALE;
    kindIndex = findKindIndex(work->kind);
    work->animSlot = kindIndex;
    if ((s16)kindIndex < 0) goto fail;
    kindIndex = work->animSlot;
    kindIndex = kindIndex << 6;
    kindIndex = kindIndex + 0x200;
    kindIndex &= 0xFC0;
    *((u16 *)sprite) = kindIndex;
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    initSpriteGraphics((void *)sprite, animState, (work->kind * 0xC) + ((u32)KIND66_EFFECT_ANIM_TABLE));
    setAnimationFrame((void *)sprite, animState, 0, 1);
    defaults = gKind66LayerAttrs;
    work->layer = allocEffectPart();
    if (work->layer == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->cleanup);
    return;
ok:
    work->layer->kind = KIND66_EFFECT_LAYER_KIND;
    work->layer->layer = KIND66_EFFECT_LAYER_NUM;
    work->layer->priority = KIND66_EFFECT_LAYER_PRI;
    work->layer->gfxIndex = gEffectGfxTable[work->kind].gfx;
    work->layer->anim0 = defaults[0];
    work->layer->anim1 = defaults[1];
    work->layer->anim2 = defaults[2];
    work->layer->anim3 = defaults[3];
    work->layer->palette = gEffectGfxTable[work->kind].palette;
    work->layer->sprite = (void *)sprite;
    *((u16 *)((u8 *)sprite + 2)) |= 0x400;
    actor->flags |= KIND66_EFFECT_READY;
    {
        s16 idx = actor->step;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) = 0;
    }
    timerCallbacks = &gMainObjTimerCallbacks;
    scriptPtr = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)actor) + 0x22, (s32)(*timerCallbacks));
    {
        s16 idx = actor->step;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) += 1;
        idx = actor->step;
        scriptEntry = scriptPtr + ((u32)idx * 2);
        sub_080C31E0(actor, *((void **)(actor->scriptTable + ((*scriptEntry) * 4))));
    }
}
