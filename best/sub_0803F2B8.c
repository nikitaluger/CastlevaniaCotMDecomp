extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
s16 findKindIndex(s16);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_0803F7CC(u8 *);
extern void sub_0801D678(u8 *, u8 *);
extern void _call_via_r1(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern void sub_080C31E0(u8 *, s32);
extern void sub_0801D5F8(void);

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
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;
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
struct EffectDef { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x28-8]; };
extern struct EffectDef gEffectGfxTable[];
extern u16 gKind87EffectAffineParams[];
extern u8 gSpriteAnimDataTable[];

void sub_0803F2B8(struct MainObj *obj) {
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
    if (sprite == NULL) {
        sub_0803F7CC((u8 *)obj);
        goto tail;
    }
    obj->object = sprite;
    allocWorkSlot((u8 *)obj, 0, 0x48, 0);
    work = obj->effect;
    if (work == NULL) {
        sub_0803F7CC((u8 *)obj);
        goto tail;
    }
    anim = (u8 *)work + 0x34;
    work->updateCb = *(u32 *)((u8 *)obj + 0x24);
    *(u32 *)((u8 *)obj + 0x24) = (u32)sub_0801D5F8;
    zero = 0;
    work->kind = 0x57;
    work->active = 1;
    work->worldX = obj->posX << 16;
    work->worldY = obj->posY << 16;
    animSlot = findKindIndex(0x57);
    work->slot = animSlot;
    if ((s32)(animSlot << 16) < 0) {
        goto tail;
    }
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    layerBytes = allocEffectPart();
    work->gfx = (struct EffectGfx *)layerBytes;
    if (layerBytes == NULL) {
        sub_080C31E0((u8 *)obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }
    work->gfx->type = zero;
    work->gfx->layer = 8;
    work->gfx->priority = 1;
    work->gfx->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->gfx->anim0 = ((u16 *)0x080CF43C)[0];
    work->gfx->anim1 = ((u16 *)0x080CF43C)[1];
    work->gfx->anim2 = ((u16 *)0x080CF43C)[2];
    work->gfx->anim3 = ((u16 *)0x080CF43C)[3];
    work->gfx->palette = gEffectGfxTable[work->kind].palette;
    work->gfx->object = (u32)sprite;
    work->gfx->tail = 0;
    oamAttr = (*(u16 *)sprite & 0xC00) |
              (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
               ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamAttr;
    *(u16 *)sprite = oamAttr | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = 0x80000009;
    cameraBase = (u8 *)&gCameraState;
    { u32 scrollOffset = 0x1278; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOffset = 0x127C; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    work->extraA = 0;
    work->extraB = 0;
    setAnimationFrame(sprite, anim, 9, 0);
    sub_0801D678((u8 *)obj, sprite);
    obj->flags |= 0x1000;
    *(u8 *)((u8 *)obj + 2 * obj->index + 0x19) = zero;
    callbackTable = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *callbackTable);
    return;
tail:
    _call_via_r1((u8 *)obj, *(s32 *)((u8 *)obj + 0x24));
}
