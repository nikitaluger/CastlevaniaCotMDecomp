struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;

/* One render layer allocated by allocEffectPart. */
struct Kind68RenderLayer {
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
struct Kind68WorkState {
    u8 _0[8];
    u32 x;           /* 0x08: world X from the script */
    u32 y;           /* 0x0C: world Y from the script */
    u32 motion;      /* 0x10: scripted motion scaled by a random factor */
    u32 scale;       /* 0x14: the random scale factor */
    u8 _18[4];
    s16 kind;        /* 0x1C: KIND68_EFFECT_KIND */
    u8 _1E[4];
    s16 animSlot;    /* 0x22: index returned by findKindIndex */
    u8 _24[4];
    struct Kind68RenderLayer *layer; /* 0x28 */
};

/* Script thread that owns the spawned effect. */
struct Kind68ScriptThread {
    u16 f0;
    u16 flags;                /* 0x02: KIND68_EFFECT_READY */
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
    s32 motion;               /* 0x6C: signed motion; sets flip and scales */
};

/* gEffectGfxTable record; this kind reads the pair at +0x08/+0x0A. */
struct Kind68GfxRecord {
    u8 _0[8];
    u16 gfx;      /* 0x08 */
    u16 palette;  /* 0x0A */
    u8 _C[0x1C];
};
extern struct Kind68GfxRecord gEffectGfxTable[];
extern u16 gKind68LayerAttrs[];
extern char gKind68AnimDataTable[];
extern u32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void setSpriteFlipForDirection(void *, s32); /* set the sprite's X-flip from a signed value */
extern s32 sub_0800583C(s32);          /* pseudo-random offset in [-range, range) */
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/*
 * Spawn a script-driven kind-0x68 effect: allocate its sprite and work block,
 * flip and scale it from the scripted motion, seed the render layer from the
 * shared tables, install the per-frame updater, then clear and advance the
 * script step. On any failure the script's cleanup callback runs instead.
 */
void spawnKind68ScriptEffect(struct Kind68ScriptThread *actor) {
    s32 sprite;
    struct Kind68WorkState *work;
    u8 *animState;
    u16 *defaults;
    u32 value;
    u8 *scriptPtr;
    void **scriptTablePtr;
    u8 *scriptEntry;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    actor->sprite = (void *)sprite;
    allocWorkSlot(actor, 0, KIND68_EFFECT_WORK_SIZE, 0);
    if (actor->work == NULL) goto fail;
    *((u32 *)(sprite + 0x1C)) = KIND68_EFFECT_GFX_ID;
    work = (struct Kind68WorkState *)actor->work;
    animState = ((u8 *)work) + 0x34;
    installUpdateHandler(actor, (u8 *)work, updateActorEffectSubObject);
    work->kind = KIND68_EFFECT_KIND;
    value = findKindIndex();
    work->animSlot = value;
    if ((s16)value < 0) goto fail;
    value = work->animSlot;
    value = value << 6;
    value = value + 0x200;
    value &= 0xFC0;
    *((u16 *)sprite) = value;
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    work->x = actor->spawnX;
    work->y = actor->spawnY;
    setSpriteFlipForDirection((void *)sprite, -actor->motion);
    {
        s32 scale = sub_0800583C(KIND68_SCALE_JITTER) + KIND68_SCALE_BASE;
        work->motion = actor->motion * scale;
        work->scale = scale;
    }
    initSpriteGraphics((void *)sprite, animState, (s32)gKind68AnimDataTable);
    setAnimationFrame((void *)sprite, animState, 0, 1);
    defaults = gKind68LayerAttrs;
    work->layer = allocEffectPart();
    if (work->layer == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->cleanup);
    return;
ok:
    work->layer->kind = KIND68_EFFECT_LAYER_KIND;
    work->layer->layer = KIND68_EFFECT_LAYER_NUM;
    work->layer->priority = KIND68_EFFECT_LAYER_PRI;
    work->layer->gfxIndex = gEffectGfxTable[work->kind].gfx;
    work->layer->anim0 = defaults[0];
    work->layer->anim1 = defaults[1];
    work->layer->anim2 = defaults[2];
    work->layer->anim3 = defaults[3];
    work->layer->palette = gEffectGfxTable[work->kind].palette;
    work->layer->sprite = (void *)sprite;
    actor->flags |= KIND68_EFFECT_READY;
    {
        s16 idx = actor->step;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) = 0;
    }
    scriptTablePtr = &gScriptStepCallbackTable;
    scriptPtr = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)actor) + 0x22, (s32)(*scriptTablePtr));
    {
        s16 idx = actor->step;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) += 1;
        idx = actor->step;
        scriptEntry = scriptPtr + ((u32)idx * 2);
        sub_080C31E0(actor, *((void **)(actor->scriptTable + ((*scriptEntry) * 4))));
    }
}
