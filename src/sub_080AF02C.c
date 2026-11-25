/* Global game/graphics state; the word at 0x18C2 holds flags OR'ed into every
 * sprite object that is created. */
struct GfxGlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GfxGlobalState D_02025FF0;

/* 20-byte sprite table entry, indexed by animation id (0x64): tile id at 0x00,
 * palette id at 0x04. */
struct SpriteIds { u16 tile; u8 _2[2]; u16 pal; u8 _8[0xC]; };

/* Render layer allocated by sub_08016190() and handed to the sprite object. */
struct EffectLayer {
    u8 _0;
    u8 f1;          /* layer frame/index */
    u8 f2;          /* size, 8 for every layer spawned here */
    u8 f3;          /* 1 when the layer is active */
    u16 f4;         /* tile id from D_080CB2B8 */
    u16 f6;         /* four words copied from the shared layer table */
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;         /* palette/tile id from D_080CB2B8 */
    u32 sprite;     /* 0x10: sprite object owning this layer */
};

/* 0x48-byte work block of a scripted effect object. */
struct EffectOwner {
    u8 _0[8];
    u32 f8, fC;
    u8 _10[0xC];
    u16 animId;     /* 0x1C: animation id (0x64) */
    u8 _1E[4];
    u16 animSlot;   /* 0x22: its slot in the 4-entry animation table */
    u8 _24[4];
    struct EffectLayer *layer;  /* 0x28 */
    u8 _2C[0x1C];
    u32 f48;
};

/* Per-kind animation entry: animation id at 0x00. */
struct AnimEntry { s16 animId; s16 _2; };

extern struct SpriteIds D_080CB2B8[];
extern u32 D_08102544[];
extern u8 D_0810254C[];
extern struct AnimEntry D_0810253C[];
extern u16 D_0810251C[];
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_080B05EC(void *, void *, u8, s32);
extern void sub_080114DC(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_08097D90(void);

/* Spawn a two-variant scripted effect object from a main object: allocate its
 * sprite and 0x48-byte work block, give the block the destructor as handler,
 * set up graphics/animation from the per-kind tables in D_08102544,
 * D_0810254C and D_0810253C, attach one render layer, then start the
 * kind-specific step script (kind 0 or 1). */
void sub_080AF02C(u8 *obj) {
    s32 sprite; struct EffectOwner *owner; u8 *gfxState; u8 *defaults; u8 *kindPtr; u8 one; s32 animSlot; struct EffectLayer *layer;
    u32 *gfxTable; s32 kind;
    sprite = (s32)sub_0800355C();
    if (sprite == 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    *(u32 *)(obj + 0x38) = sprite;
    sub_0800168C(obj, 0, 0x48, 0);
    if (*(u32 *)(obj + 0x3C) == 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    gfxTable = D_08102544;
    kindPtr = obj + 0x4C;
    *(u32 *)(sprite + 0x1C) = gfxTable[*(u8 *)kindPtr];
    owner = (struct EffectOwner *)*(u32 *)(obj + 0x3C);
    gfxState = (u8 *)owner + 0x34;
    sub_08014288(obj, (u8 *)owner, sub_08097D90);
    owner->animId = 0x64;
    animSlot = sub_08013C2C(0x64);
    owner->animSlot = animSlot;
    if ((animSlot << 16) < 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    *(u16 *)sprite |= D_02025FF0.gfxFlags;
    sub_080B05EC((void *)sprite, gfxState, D_0810254C[*(u8 *)kindPtr], 2);
    sub_080114DC((void *)sprite, gfxState, D_0810253C[*(u8 *)kindPtr].animId, 0);
    defaults = (u8 *)D_0810251C;
    layer = sub_08016190();
    owner->layer = layer;
    if (layer == NULL) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    layer->f1 = 5;
    owner->layer->f2 = 8;
    owner->layer->f3 = (one = 1);
    owner->layer->f4 = D_080CB2B8[*(s16 *)((u8 *)owner + 0x1C)].tile;
    owner->layer->f6 = *(u16 *)(defaults + 0);
    owner->layer->f8 = *(u16 *)(defaults + 2);
    owner->layer->fA = *(u16 *)(defaults + 4);
    owner->layer->fC = *(u16 *)(defaults + 6);
    owner->layer->fE = D_080CB2B8[*(s16 *)((u8 *)owner + 0x1C)].pal;
    owner->layer->sprite = sprite;
    *(u8 *)(obj + 0x50) = 0;
    *(u16 *)(obj + 2) |= 0x1000;
    *(u16 *)(obj + 2) |= 0x800;
    kind = *kindPtr;
    switch (kind) {
    case 0:
        *(u32 *)(obj + 0x14) = 0x080AF1AD;
        *(u16 *)(obj + 0x22) = one;
        sub_080C31E0(obj, (void *)0x080AF1AD);
        break;
    case 1:
        *(u32 *)(obj + 0x14) = 0x080AF28D;
        *(u16 *)(obj + 0x22) = kind;
        sub_080C31E0(obj, (void *)0x080AF28D);
        break;
    }
}
