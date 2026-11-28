#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
struct Effect385EC { u8 m0, kind, layer, priority; u16 gfxIndex, anim0, anim1, anim2, anim3, palette; u32 object; };
struct Work385EC { u8 pad0[8]; u32 worldX, worldY, f10, f14; u8 pad18[4]; s16 kind; u8 pad1E[4]; s16 slot; u8 pad24[4]; struct Effect385EC *effect; u8 pad2C[8]; u8 anim[8]; };
struct GfxAttr385EC { u8 pad0[4]; u16 gfxIndex, palette, gfxIndex2, palette2; u8 padC[0x1C]; };
struct WsFlags385EC { u8 pad[0x18c2]; u16 flags; };
struct WsFrame385EC { u8 pad[0x18a8]; u8 frame; };
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void copyBytes(u8 *, u8 *, s32);
extern void setSpriteFlipForDirection(u8 *, u32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void sub_08014290(void);
extern void _call_via_r1(u8 *, u32);
extern void _call_via_r2(u8 *, u8 *, u32);
extern u8 D_080CF0B4[], D_080CF0AC[], D_080CF060[], D_080CF068[];
extern u8 gSpriteAnimDataTable[], gCameraState[];
extern struct WsFlags385EC gMainWorkspace;
extern struct GfxAttr385EC gEffectGfxTable[];
extern u32 gMainObjTimerCallbacks[];

void sub_080385EC(u8 *entity) {
    u16 tbl[4];
    u8 *sprite;
    struct Work385EC *work;
    u8 *animator;
    u8 *variantPtr;
    u8 *kindTable;
    u16 *layerAttrs;
    struct Effect385EC *effect;
    s32 slot;
    u32 spriteAttr;
    u8 *camera;
    u8 *scrollX;
    u8 *scrollY;
    u32 idx;

    copyBytes((u8 *)tbl, D_080CF0B4, 8);
    sprite = allocSpriteObject();
    if (sprite == 0) goto fail;
    U32(entity, 0x38) = (u32)sprite;
    allocWorkSlot(entity, 0, 0x48, 0);
    if (U32(entity, 0x3c) == 0) goto fail;
    U32(sprite, 0x1c) = 0x0800000B;
    work = (struct Work385EC *)U32(entity, 0x3c);
    animator = (u8 *)work + 0x34;
    installUpdateHandler(entity, (u8 *)work, (void *)sub_08014290);
    kindTable = D_080CF0AC;
    work->kind = (s16)*(u32 *)(kindTable + U8(entity, 0x4c) * 4);
    work->worldX = U32(entity, 0x5c);
    work->worldY = U32(entity, 0x6c);
    work->f10 = U32(entity, 0x7c);
    work->f14 = U32(entity, 0x8c);
    slot = findKindIndex(work->kind);
    work->slot = slot;
    if ((slot << 16) < 0) goto fail;
    spriteAttr = ((u32)(work->slot << 6) + 0x200) | ((u32)(slot + 8) << 12);
    U16(sprite, 0) = spriteAttr;
    U16(sprite, 0) |= gMainWorkspace.flags;
    setSpriteFlipForDirection(sprite, work->f10);
    initSpriteGraphics(sprite, animator, (s32)((u8 *)gSpriteAnimDataTable + work->kind * 12));
    variantPtr = entity + 0xa0;
    setAnimationFrame(sprite, animator, ((s16 *)tbl)[*variantPtr], 1);
    if (*variantPtr == 0) goto case0;
    layerAttrs = (u16 *)D_080CF068;
    effect = allocEffectPart();
    work->effect = effect;
    if (effect == 0) goto fail;
    effect->kind = 5;
    work->effect->layer = 8;
    work->effect->priority = 1;
    work->effect->gfxIndex = gEffectGfxTable[work->kind].gfxIndex2;
    work->effect->anim0 = layerAttrs[0];
    work->effect->anim1 = layerAttrs[1];
    work->effect->anim2 = layerAttrs[2];
    work->effect->anim3 = layerAttrs[3];
    work->effect->palette = gEffectGfxTable[work->kind].palette2;
    goto common;
case0:
    layerAttrs = (u16 *)D_080CF060;
    effect = allocEffectPart();
    work->effect = effect;
    if (effect == 0) goto fail;
    goto case0body;
fail:
    _call_via_r1(entity, U32(entity, 0x24));
    return;
case0body:
    effect->kind = 5;
    work->effect->layer = 8;
    work->effect->priority = 1;
    work->effect->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->effect->anim0 = layerAttrs[0];
    work->effect->anim1 = layerAttrs[1];
    work->effect->anim2 = layerAttrs[2];
    work->effect->anim3 = layerAttrs[3];
    work->effect->palette = gEffectGfxTable[work->kind].palette;
common:
    work->effect->object = (u32)sprite;
    camera = gCameraState;
    idx = ((u32)((struct WsFrame385EC *)&gMainWorkspace)->frame + 1) * 0x40;
    scrollX = camera + 0x1278;
    U32(sprite, 0x14) = work->worldX - ((U32(scrollX, idx) + 0x8000) & 0xffff0000);
    idx = ((u32)((struct WsFrame385EC *)&gMainWorkspace)->frame + 1) * 0x40;
    scrollY = camera + 0x127c;
    U32(sprite, 0x18) = work->worldY - ((U32(scrollY, idx) + 0xffff8000) & 0xffff0000);
    {
        s32 zero = 0;
        u8 *stepPtr;
        U16(entity, 2) |= 0x1000;
        U8(entity + S16(entity, 0x22) * 2, 0x19) = (u8)zero;
        {
            u32 *scriptOps = gMainObjTimerCallbacks;
            u8 *scriptSlots = entity + 0x18;
            _call_via_r2(scriptSlots, entity + 0x22, *scriptOps);
            stepPtr = (u8 *)((u32)(S16(entity, 0x22) * 2) + (u32)entity) + 0x19;
            *stepPtr = (u8)(*stepPtr + 1);
            stepPtr = scriptSlots + S16(entity, 0x22) * 2;
            {
                u8 opcode = *stepPtr;
                void *handler = ((void **)U32(entity, 0x14))[opcode];
                _call_via_r1(entity, (u32)handler);
            }
        }
    }
}
