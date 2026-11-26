extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_08019254(u8 *, u8 *);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern void sub_080191DC(void *);

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
/* Effect component stored in the main object at +0x3C. */
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;      /* 16.16 fixed point */
    s32 worldY;
    u32 f10;
    u32 f14;
    u32 f18;
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
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable gCameraState;
struct EffectDef { u8 _0[8]; u16 gfxIndex; u16 palette; u8 _A[0x1C]; };
extern struct EffectDef gEffectGfxTable[];
extern u16 D_080CE5D0[];
extern u8 gSpriteAnimDataTable[];

/* Spawn a graphics effect from a main object: allocate a free object, build its
   EffectGfx from gEffectGfxTable/D_080CE5D0, and place it at the object's world coords. */
void sub_08018DE0(struct MainObj *arg0) {
    u8 *effect;
    struct OwnerEffect *owner;
    u8 *anim;
    u8 *gfx;
    s32 slot;
    u32 flags;
    u32 zero;
    u8 *scrollTable;

    effect = allocSpriteObject();
    owner = NULL;
    anim = NULL;
    slot = 0;
    if ((effect == NULL) ||
        (arg0->object = effect, allocWorkSlot((u8 *)arg0, 0, 0x48, 0), owner = arg0->effect, owner == NULL) ||
        (anim = (u8 *)owner + 0x34, owner->updateCb = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_080191DC,
         owner->kind = 0x55, owner->f18 = 1,
         owner->worldX = *(s16 *)((u8 *)arg0 + 0x4C) << 16, owner->worldY = *(s16 *)((u8 *)arg0 + 0x54) << 16,
         slot = findKindIndex(0x55), owner->slot = slot, ((s32)(slot << 16) < 0)) ||
        (initSpriteGraphics(effect, anim, (s32)gSpriteAnimDataTable + owner->kind * 0xC), gfx = allocEffectPart(), owner->gfx = (struct EffectGfx *)gfx, gfx == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    zero = 0;
    owner->gfx->type = zero;
    owner->gfx->layer = 8;
    owner->gfx->priority = 1;
    owner->gfx->gfxIndex = gEffectGfxTable[owner->kind].gfxIndex;
    owner->gfx->anim0 = D_080CE5D0[0];
    owner->gfx->anim1 = D_080CE5D0[1];
    owner->gfx->anim2 = D_080CE5D0[2];
    owner->gfx->anim3 = D_080CE5D0[3];
    owner->gfx->palette = gEffectGfxTable[owner->kind].palette;
    owner->gfx->object = (u32)effect;
    owner->gfx->tail = zero;
    flags = (*(u16 *)effect & 0xC00) |
          (((*(s16 *)((u8 *)owner + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)owner + 0x22) + 8) << 12));
    *(u16 *)effect = flags;
    *(u16 *)effect = flags | gMainWorkspace.flags;
    *(u32 *)(effect + 0x1C) = 0x80000009;
    scrollTable = (u8 *)&gCameraState;
    { u32 offset = 0x1278; *(u32 *)(effect + 0x14) = owner->worldX - ((*(u32 *)(scrollTable + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(effect + 0x18) = owner->worldY - ((*(u32 *)(scrollTable + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    setAnimationFrame(effect, anim, 0x24, 0);
    sub_08019254((u8 *)arg0, effect);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = zero;
    {
        s32 *audioCmd = (s32 *)0x08671BB0;
        _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *audioCmd);
    }
}
