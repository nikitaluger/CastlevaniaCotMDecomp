struct CaEntity {
    u8 _0[2];
    u16 flags;         /* 0x02 */
    u8 _04[0x10];
    u32 dispatch;      /* 0x14 */
    u8 _18[0xA];
    s16 step;          /* 0x22 */
    u32 script;        /* 0x24 */
    u8 _28[0x10];
    u32 object;        /* 0x38 */
    u32 part;          /* 0x3C */
    u8 _40[0xC];
    u32 f4C;           /* 0x4C */
    u8 _50[0xC];
    u32 f5C;           /* 0x5C */
    u8 _60[0x4C];
    u32 savedAC;       /* 0xAC */
};
struct CaWork {
    u8 _0[8];
    u32 x;             /* 0x08 */
    u32 y;             /* 0x0C */
    u8 _10[0xC];
    s16 kind;          /* 0x1C */
    u8 _1E[4];
    u32 updateFn;      /* 0x24 */
    u32 layer;         /* 0x28 */
};
struct CaSprite {
    u8 _0[0x14];
    u32 x;             /* 0x14 */
    u32 y;             /* 0x18 */
    u32 gfxId;         /* 0x1C */
};
struct CaLayer {
    u8 _0, kind, layer, priority;
    u16 gfxA;
    u16 attr0, attr1, attr2, attr3;
    u16 gfxB;
    u32 object;
};
struct CaKindEntry { u16 gfxA; u16 param; u16 gfxB; u8 _6[0xE]; };

void *allocSpriteObject(void);
void allocWorkSlot(void *, u32, u32, u32);
void installUpdateHandler(void *, void *, void *);
void initWorkStateForKind(void *, void *, void *, u32, u32);
void initSpriteGraphics(void *, void *, void *);
void setAnimationFrame(void *, void *, u32, u32);
void sub_080148D8(void *);
void *allocEffectPart(void);
void registerScriptObject(void *, u32);
void _call_via_r1(void *, void *);
void _call_via_r2(void *, void *, u32);
void updateScriptedEffectObject(void);
extern u8 gSpriteKindTable[];
extern u16 gAttackEffectAffineParams[];
extern u8 gSpriteAnimDataTable[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

void sub_0803CA24(struct CaEntity *entity)
{
    struct CaSprite *sprite;
    struct CaWork *work;
    u8 *anim;
    struct CaLayer *layer;
    u32 savedAC;
    s16 kind;
    u32 scrollIdx;
    s16 step;

    savedAC = entity->savedAC;
    sprite = (struct CaSprite *)allocSpriteObject();
    if (sprite == NULL) goto fail;
    entity->object = (u32)sprite;
    allocWorkSlot(entity, 0, 0x58, 0);
    if (entity->part == 0) goto fail;
    sprite->gfxId = 0x8000000A;
    work = (struct CaWork *)entity->part;
    anim = (u8 *)work + 0x34;
    installUpdateHandler(entity, work, &updateScriptedEffectObject);
    initWorkStateForKind(entity, sprite, work, savedAC, 0x2D);
    kind = work->kind;
    initSpriteGraphics(sprite, anim, (void *)(gSpriteAnimDataTable + (12 * ((s32)kind))));
    setAnimationFrame(sprite, anim, 0, 0);
    work->x = entity->f4C;
    work->y = entity->f5C;
    sub_080148D8(sprite);
    layer = (struct CaLayer *)allocEffectPart();
    work->layer = (u32)layer;
    if (layer == NULL) goto fail;
    savedAC = 0;
    layer->kind = 5;
    layer->layer = (u8)savedAC;
    layer->priority = (u8)savedAC;
    layer->gfxA = ((struct CaKindEntry *)(gSpriteKindTable + (((s32)kind) * 20)))->gfxA;
    layer->attr0 = gAttackEffectAffineParams[0];
    layer->attr1 = gAttackEffectAffineParams[1];
    layer->attr2 = gAttackEffectAffineParams[2];
    layer->attr3 = gAttackEffectAffineParams[3];
    layer->gfxB = ((struct CaKindEntry *)(gSpriteKindTable + (((s32)kind) * 20)))->gfxB;
    layer->object = (u32)sprite;
    {
        u8 *camera = gCameraState;
        u8 *state = gMainWorkspace;
        u8 *base1, *base2;
        scrollIdx = ((u32)*(state + 0x18A8) + 1) * 0x40;
        base1 = camera + 0x1278;
        sprite->x = work->x - ((*(u32 *)(base1 + scrollIdx) + 0x8000) & 0xFFFF0000);
        scrollIdx = ((u32)*(state + 0x18A8) + 1) * 0x40;
        base2 = camera + 0x127C;
        sprite->y = work->y - ((*(u32 *)(base2 + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    registerScriptObject(entity, 0);
    entity->flags |= 0x1000;
    step = entity->step;
    *((u8 *)entity + (step * 2) + 0x19) = (u8)savedAC;
    {
        u32 *timerTable = &gMainObjTimerCallbacks;
        u8 *p18 = (u8 *)entity + 0x18;
        u8 *p22 = (u8 *)entity + 0x22;
        _call_via_r2(p18, p22, *timerTable);
        step = *(s16 *)p22;
        { u8 *p19 = (u8 *)((((s32)step) * 2) + (u32)entity); p19[0x19] = (u8)(p19[0x19] + 1); }
        step = *(s16 *)p22;
        { u8 *q = p18 + (((s32)step) * 2); _call_via_r1(entity, *(u32 *)((((u32)(*q)) * 4) + entity->dispatch)); }
    }
    return;
fail:
    _call_via_r1(entity, entity->script);
}
