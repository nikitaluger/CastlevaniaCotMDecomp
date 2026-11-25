extern u8 *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, u8 *);
extern u8 *sub_08016190(void);
extern void sub_0802279C(u8 *);
extern void sub_08022760(void);
extern void sub_080227D4(u8 *, u8 *);
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
    u8 _4[0x22 - 4];
    s16 index;
    u8 _24[0x38 - 0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 _40[0x4C - 0x40];
    s16 posX;
    u8 _4E[6];
    s16 posY;
    u8 _56[0x7C - 0x56];
    u16 kind;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState D_02025FF0;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable D_02021E90;
struct EffectDef { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x28 - 0x08]; };
extern struct EffectDef D_080CBDD0[];
extern u16 D_080CE830[];
extern u8 D_080CD400[];
extern u32 D_08671BB0;

void sub_080221F0(struct MainObj *arg0)
{
    u8 *effect;
    struct OwnerEffect *owner;
    u8 *anim;
    u8 *gfx;
    u8 *slotp;
    u32 *slot;
    s32 slotid;
    u32 zero;
    s32 i;
    u8 *base;

    effect = sub_0800355C();
    owner = NULL;
    anim = NULL;
    slotid = 0;
    zero = 0;
    if (effect != NULL) goto have_obj;
cleanup:
    sub_0802279C((u8 *)arg0);
    goto fail;
have_obj:
    arg0->object = effect;
    sub_0800168C((u8 *)arg0, 0, 0x84, 0);
    if (arg0->effect == NULL) goto cleanup;
    owner = arg0->effect;
    anim = ((u8 *)owner);
    anim += 0x34;
    owner->updateCb = *((u32 *)((u8 *)arg0 + 0x24));
    *((u32 *)((u8 *)arg0 + 0x24)) = (u32)sub_08022760;
    owner->kind = arg0->kind;
    owner->f18 = 1;
    owner->worldX = arg0->posX << 16;
    owner->worldY = arg0->posY << 16;
    slotid = sub_08013C2C(owner->kind);
    owner->slot = slotid;
    if ((slotid << 16) < 0) goto fail;
    sub_0801131C(effect, anim, (u8 *)((s32)D_080CD400 + owner->kind * 0xC));
    gfx = sub_08016190();
    owner->gfx = (struct EffectGfx *)gfx;
    if (gfx != NULL) goto have_gfx;
fail:
    sub_080C31E0((u8 *)arg0, *((s32 *)((u8 *)arg0 + 0x24)));
    return;
have_gfx:
    owner->gfx->type = zero;
    owner->gfx->layer = 8;
    owner->gfx->priority = 1;
    owner->gfx->gfxIndex = D_080CBDD0[owner->kind].gfxIndex;
    owner->gfx->anim0 = D_080CE830[0];
    owner->gfx->anim1 = D_080CE830[1];
    owner->gfx->anim2 = D_080CE830[2];
    owner->gfx->anim3 = D_080CE830[3];
    owner->gfx->palette = D_080CBDD0[owner->kind].palette;
    owner->gfx->object = (u32)effect;
    owner->gfx->tail = 0;
    {
        u32 flags;
        flags = (*((u16 *)effect) & 0xC00) |
                (((*((s16 *)((u8 *)owner + 0x22)) << 6) + 0x200) |
                 ((*((u16 *)((u8 *)owner + 0x22)) + 8) << 12));
        *((u16 *)effect) = flags;
        *((u16 *)effect) = flags | D_02025FF0.flags;
    }
    *((u32 *)(effect + 0x1C)) = 0x8000000A;
    base = (u8 *)&D_02021E90;
    *((u32 *)(effect + 0x14)) = owner->worldX - ((*((u32 *)(base + 0x1278 + ((D_02025FF0.scrollIndex + 1) << 6))) + 0x8000) & 0xFFFF0000);
    *((u32 *)(effect + 0x18)) = owner->worldY - ((*((u32 *)(base + 0x127C + ((D_02025FF0.scrollIndex + 1) << 6))) + 0xFFFF8000) & 0xFFFF0000);
    slotp = ((u8 *)owner) + 0x48;
    *((u16 *)slotp) = 0;
    *((u16 *)(slotp + 2)) = 0;
    *((u32 *)(slotp + 4)) = 0;
    for (i = 0; i < 2; i++)
    {
        gfx = sub_08016190();
        slot = (u32 *)(slotp + 0x34) + i;
        *slot = (u32)gfx;
        if (gfx == NULL) goto fail;
        ((struct EffectGfx *)*slot)->type = 0;
        ((struct EffectGfx *)*slot)->layer = 8;
        ((struct EffectGfx *)*slot)->priority = 1;
        ((struct EffectGfx *)*slot)->gfxIndex = D_080CBDD0[owner->kind].gfxIndex;
        ((struct EffectGfx *)*slot)->anim0 = D_080CE830[0];
        ((struct EffectGfx *)*slot)->anim1 = D_080CE830[1];
        ((struct EffectGfx *)*slot)->anim2 = D_080CE830[2];
        ((struct EffectGfx *)*slot)->anim3 = D_080CE830[3];
        ((struct EffectGfx *)*slot)->palette = D_080CBDD0[owner->kind].palette;
        ((struct EffectGfx *)*slot)->object = (u32)effect;
        ((struct EffectGfx *)*slot)->tail = 0;
    }
    *((u16 *)(effect + 0x28)) = 0x29;
    sub_080227D4((u8 *)arg0, effect);
    arg0->flags |= 0x1000;
    *((u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19)) = zero;
    {
        u32 *p = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *p);
    }
}
