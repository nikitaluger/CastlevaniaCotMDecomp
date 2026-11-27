/* Spawn a kind-0x87 graphics effect from a main object: allocate a free sprite
 * and work slot, build the render descriptor from the effect tables, place it
 * at the object's world coordinates, copy the object's extra parameters and
 * dispatch the next script step. The chained condition preserves the original
 * short-circuit order of the setup checks. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void registerScriptObject(u8 *, s32);
extern void sub_0801D678(u8 *, u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern void sub_0801D5F8(void);

/* Graphics/animation descriptor hung off the spawned effect object. */
struct EffectGfx {
    u8 _0;
    u8 type;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
    u16 tail;
};
/* Per-object effect component stored in the main object at +0x3C. */
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;      /* 16.16 fixed point */
    s32 worldY;
    u32 extraA;
    u32 extraB;
    u32 active;
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u32 updateCb;
    struct EffectGfx *gfx;
};
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22-4];
    s16 index;
    u8 _24[0x38-0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 _40[0x4C-0x40];
    s16 posX;
    u8 _4E[6];
    s16 posY;
    u8 _56[0x5C-0x56];
    u32 extraA;
    u8 _60[0x6C-0x60];
    u32 extraB;
};
struct GameWorkspace { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 gfxFlags; };
extern struct GameWorkspace gMainWorkspace;
struct ScrollState { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollState gCameraState;
struct EffectDef { u8 _0[0x10]; u16 gfxIndex; u16 palette; u8 _14[0x28-0x14]; };
extern struct EffectDef gEffectGfxTable[];
extern u16 gKind87EffectAffineParams[];
extern u8 gSpriteAnimDataTable[];

void spawnKind87EffectFromObject(struct MainObj *obj) {
    u8 *sprite;
    struct OwnerEffect *work;
    u8 *anim;
    u8 *layerBytes;
    s32 animSlot;
    u32 oamAttr;
    u32 zero;
    u8 *cameraBase;
    s32 *callbackTable;

    sprite = allocSpriteObject();
    work = NULL;
    anim = NULL;
    animSlot = 0;
    if ((sprite == NULL) ||
        (obj->object = sprite, allocWorkSlot((u8 *)obj, 0, CHILD_SPRITE_WORK_SLOT_SIZE, 0), work = obj->effect, work == NULL) ||
        (anim = (u8 *)work + 0x34,
         work->updateCb = *(u32 *)((u8 *)obj + 0x24), *(u32 *)((u8 *)obj + 0x24) = (u32)sub_0801D5F8,
         zero = 0, work->kind = SPRITE_KIND_KIND87_EFFECT, work->active = 1,
         work->worldX = obj->posX << 16, work->worldY = obj->posY << 16,
         animSlot = findKindIndex(SPRITE_KIND_KIND87_EFFECT), work->slot = animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC), layerBytes = allocEffectPart(), work->gfx = (struct EffectGfx *)layerBytes, layerBytes == NULL)) {
        _call_via_r1((u8 *)obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }
    work->gfx->type = zero;
    work->gfx->layer = 8;
    work->gfx->priority = 1;
    work->gfx->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->gfx->anim0 = gKind87EffectAffineParams[0];
    work->gfx->anim1 = gKind87EffectAffineParams[1];
    work->gfx->anim2 = gKind87EffectAffineParams[2];
    work->gfx->anim3 = gKind87EffectAffineParams[3];
    work->gfx->palette = gEffectGfxTable[work->kind].palette;
    work->gfx->object = (u32)sprite;
    work->gfx->tail = 0;
    oamAttr = (*(u16 *)sprite & 0xC00) |
              (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
               ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamAttr;
    *(u16 *)sprite = oamAttr | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = CHILD_SPRITE_GFX_ID;
    cameraBase = (u8 *)&gCameraState;
    { u32 scrollOffset = 0x1278; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOffset = 0x127C; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    work->extraA = obj->extraA;
    work->extraB = obj->extraB;
    setAnimationFrame(sprite, anim, FIXED_EFFECT_ANIM_FRAME, 0);
    sub_0801D678((u8 *)obj, sprite);
    obj->flags |= CHILD_SPRITE_READY;
    *(u8 *)((u8 *)obj + 2 * obj->index + 0x19) = zero;
    callbackTable = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *callbackTable);
}
