extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_0804BB5C(void);
extern void sub_0804BB7C(u8 *, u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

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
    u8 _40[0x4C-0x40];
    s16 posX;
    u8 _4E[6];
    s16 posY;
    u8 _56[0x5C-0x56];
    u16 kind;
    u8 _5E[0x6C-0x5E];
    s16 f6C;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable gCameraState;
struct EffectDef { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x28 - 0x08]; };
extern struct EffectDef gEffectGfxTable[];
extern u16 D_080CF990[];
extern u8 gSpriteAnimDataTable[];

void sub_0804B760(struct MainObj *arg0) {
    u8 *effect;
    struct OwnerEffect *owner;
    u8 *anim;
    u8 *gfx;
    s32 slot;
    u32 flags;
    u8 *scrollTable;
    u32 *audioCmd;
    s16 idx;
    u8 *entries;
    u8 *counterPtr;
    u8 *entry;
    u32 zero;

    effect = allocSpriteObject();
    owner = NULL;
    anim = NULL;
    slot = 0;
    if ((effect == NULL) ||
        (arg0->object = effect, allocWorkSlot((u8 *)arg0, 0, 0x4C, 0), owner = arg0->effect, owner == NULL) ||
        (anim = (u8 *)owner + 0x34,
         owner->updateCb = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0804BB5C,
         owner->kind = arg0->kind, owner->f18 = 1,
         owner->worldX = arg0->posX << 16, owner->worldY = arg0->posY << 16,
         slot = findKindIndex(owner->kind), owner->slot = slot, ((s32)(slot << 16) < 0)) ||
        (initSpriteGraphics(effect, anim, (s32)gSpriteAnimDataTable + owner->kind * 0xC), gfx = allocEffectPart(), owner->gfx = (struct EffectGfx *)gfx, gfx == NULL)) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    zero = 0;
    owner->gfx->priority = 1;
    owner->gfx->layer = 8;
    owner->gfx->type = zero;
    owner->gfx->gfxIndex = gEffectGfxTable[owner->kind].gfxIndex;
    owner->gfx->anim0 = D_080CF990[0];
    owner->gfx->anim1 = D_080CF990[1];
    owner->gfx->anim2 = D_080CF990[2];
    owner->gfx->anim3 = D_080CF990[3];
    owner->gfx->palette = gEffectGfxTable[owner->kind].palette;
    owner->gfx->object = (u32)effect;
    owner->gfx->tail = 0;
    flags = (*(u16 *)effect & 0xC00) |
          (((*(s16 *)((u8 *)owner + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)owner + 0x22) + 8) << 12));
    *(u16 *)effect = flags;
    *(u16 *)effect = flags | gMainWorkspace.flags;
    *(u32 *)(effect + 0x1C) = 0x8000000A;
    scrollTable = (u8 *)&gCameraState;
    { u32 offset = 0x1278; *(u32 *)(effect + 0x14) = owner->worldX - ((*(u32 *)(scrollTable + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(effect + 0x18) = owner->worldY - ((*(u32 *)(scrollTable + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    setAnimationFrame(effect, anim, 0x1C, 0);
    if (arg0->f6C > 0) {
        *(u16 *)(effect + 2) |= 0x10;
        owner->f10 = 0x6000;
    } else {
        owner->f10 = 0xFFFFA000;
    }
    sub_0804BB7C((u8 *)arg0, effect);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = zero;
    audioCmd = (u32 *)0x08671BB0;
    entries = (u8 *)arg0 + 0x18;
    sub_080C31E4(entries, (u8 *)arg0 + 0x22, *audioCmd);
    idx = arg0->index;
    counterPtr = (u8 *)(((s32)idx * 2) + (u32)arg0);
    counterPtr[0x19] = (u8)(counterPtr[0x19] + 1);
    idx = arg0->index;
    entry = entries + (s32)idx * 2;
    sub_080C31E0((u8 *)arg0, *(s32 *)(*(u8 **)((u8 *)arg0 + 0x14) + *(u8 *)entry * 4));
}
