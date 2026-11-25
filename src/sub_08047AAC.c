extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08014668(u8 *);
extern void sub_08047FF0(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

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
    u32 spawnX;
    u32 spawnY;
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
    u32 spawnX;
    u8 _60[0x6C-0x60];
    u32 spawnY;
    u8 _70[0x7C-0x70];
    u16 kind;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState D_02025FF0;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable D_02021E90;
struct EffectDef { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x28-8]; };
extern struct EffectDef D_080CBDD0[];
extern u16 D_080CF8D0[];
extern u8 D_080CD400[];

/* Spawn an effect from a main object: allocate a free object, build its
   EffectGfx from D_080CBDD0/D_080CF8D0, place it at the object's world coords
   and hand it to sub_08014668 before scheduling the audio/command stream. */
void sub_08047AAC(struct MainObj *arg0) {
    u8 *effect;
    struct OwnerEffect *owner;
    u8 *anim;
    u8 *gfx;
    s32 slot;
    u32 flags;
    u32 zero, tailZero;
    u8 *scrollTable;
    s32 *audioCmd;
    u32 extra;

    effect = sub_0800355C();
    owner = NULL;
    gfx = NULL;
    slot = 0;
    if ((effect == NULL) ||
        (arg0->object = effect, sub_0800168C((u8 *)arg0, 0, 0x54, 0), owner = arg0->effect, owner == NULL) ||
        (anim = (u8 *)owner + 0x34, owner->updateCb = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_08047FF0,
         owner->kind = arg0->kind, owner->f18 = 1,
         owner->worldX = arg0->posX << 16, owner->worldY = arg0->posY << 16,
         slot = sub_08013C2C(owner->kind), owner->slot = slot, ((s32)(slot << 16) < 0)) ||
        (sub_0801131C(effect, anim, (s32)D_080CD400 + owner->kind * 0xC), gfx = sub_08016190(), owner->gfx = (struct EffectGfx *)gfx, gfx == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    zero = 0;
    tailZero = 0;
    owner->gfx->type = zero;
    owner->gfx->layer = 8;
    owner->gfx->priority = 1;
    owner->gfx->gfxIndex = D_080CBDD0[owner->kind].gfxIndex;
    owner->gfx->anim0 = D_080CF8D0[0];
    owner->gfx->anim1 = D_080CF8D0[1];
    owner->gfx->anim2 = D_080CF8D0[2];
    owner->gfx->anim3 = D_080CF8D0[3];
    owner->gfx->palette = D_080CBDD0[owner->kind].palette;
    owner->gfx->object = (u32)effect;
    owner->gfx->tail = tailZero;
    flags = (*(u16 *)effect & 0xC00) |
          (((*(s16 *)((u8 *)owner + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)owner + 0x22) + 8) << 12));
    *(u16 *)effect = flags;
    *(u16 *)effect = flags | D_02025FF0.flags;
    *(u32 *)(effect + 0x1C) = 0x80000003;
    scrollTable = (u8 *)&D_02021E90;
    { u32 offset = 0x1278; *(u32 *)(effect + 0x14) = owner->worldX - ((*(u32 *)(scrollTable + offset + ((D_02025FF0.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(effect + 0x18) = owner->worldY - ((*(u32 *)(scrollTable + offset + ((D_02025FF0.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    extra = (u32)((u8 *)owner + 0x48);
    *(u16 *)(extra + 0xA) = tailZero;
    *(u16 *)(extra + 0x8) = 0x23;
    extra = arg0->spawnX;
    owner->spawnX = extra;
    owner->spawnY = arg0->spawnY;
    sub_08014668(effect);
    sub_08011368(effect, anim, 0x0B, 0);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = zero;
    audioCmd = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *audioCmd);
}
