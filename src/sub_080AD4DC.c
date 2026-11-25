extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern void sub_08014288(u8 *, u8 *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_080B05EC(u8 *, u8 *, s32, s32);
extern void sub_080114DC(u8 *, u8 *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080AD84C(void);
extern void sub_080AD6BC(void);

/* Main object that owns the spawned effect. */
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x14 - 4];
    u32 updateCb;
    u8 _18[0x22 - 0x18];
    u16 counter;
    u32 failCb;
    u8 _28[0x38 - 0x28];
    u8 *object;
    u8 *effect;
    u8 _40[0x4C - 0x40];
    u8 kind;
    u8 _4D[0x8C - 0x4D];
    u8 spriteOffset;
    u8 _8D[0x94 - 0x8D];
    u8 flagByte;
};
/* Effect component stored in the main object at +0x3C. */
struct OwnerEffect {
    u8 _0[0x1C];
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u8 _24[4];
    void *gfxA;
    u8 _2C[0x48 - 0x2C];
    void *gfxB;
};
/* Graphics/animation descriptor hung off the effect object. */
struct EffectGfx {
    u8 _0;
    u8 type;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
};
struct GameState { u8 _0[0x18C2]; u16 flags; };
extern struct GameState D_02025FF0;
struct EffectDef { u8 _0[8]; u16 gfxIndex; u16 palette; u8 _C[0x28 - 0xC]; };
extern struct EffectDef D_080CBDD0[];
struct SpriteEntry { u32 base; };
extern struct SpriteEntry D_08102288[];
extern u8 D_08102294[];
extern s16 D_08102280[];
extern u8 D_08102268[];

/* Spawn a two-layer graphics effect from a main object: allocate a free object,
   build both EffectGfx descriptors from D_080CBDD0/D_08102268 and set animations. */
void sub_080AD4DC(struct MainObj *arg0)
{
    u8 *effect;
    u8 *work;
    struct OwnerEffect *owner;
    u8 *kindPtr;
    s32 slot;
    u32 one;
    u32 eight;
    u8 **workRef;
    struct SpriteEntry *spriteTable;

    effect = sub_0800355C();
    if (effect == NULL)
    {
        goto fail;
    }
    workRef = &work;
    arg0->object = effect;
    sub_0800168C((u8 *)arg0, 0, 0x4C, 0);
    if (arg0->effect == NULL)
    {
        goto fail;
    }
    spriteTable = D_08102288;
    kindPtr = ((u8 *)arg0) + 0x4C;
    *((u32 *)(effect + 0x1C)) = spriteTable[*kindPtr].base + arg0->spriteOffset;
    owner = *((struct OwnerEffect * volatile *) (((u8 *)arg0) + 0x3C));
    work = ((u8 *)owner) + 0x34;
    sub_08014288((u8 *)arg0, (u8 *)owner, sub_080AD84C);
    owner->kind = 0x64;
    slot = sub_08013C2C(0x64);
    owner->slot = slot;
    if ((slot << 16) < 0)
    {
        goto fail;
    }
    *((u16 *)effect) |= D_02025FF0.flags;
    sub_080B05EC(effect, *workRef, D_08102294[*kindPtr], 2);
    sub_080114DC(effect, work, D_08102280[*kindPtr], 0);
    work = (u8 *)(0x08102268 + ((*kindPtr) * 8));
    owner->gfxA = sub_08016190();
    if (owner->gfxA == NULL)
    {
        goto fail;
    }
    one = 1;
    ((struct EffectGfx *)owner->gfxA)->type = one;
    ((struct EffectGfx *)owner->gfxA)->layer = (eight = 8);
    ((struct EffectGfx *)owner->gfxA)->priority = one;
    ((struct EffectGfx *)owner->gfxA)->gfxIndex = D_080CBDD0[owner->kind].gfxIndex;
    ((struct EffectGfx *)owner->gfxA)->anim0 = *((u16 *)(work + 0));
    ((struct EffectGfx *)owner->gfxA)->anim1 = *((u16 *)(work + 2));
    ((struct EffectGfx *)owner->gfxA)->anim2 = *((u16 *)(work + 4));
    ((struct EffectGfx *)owner->gfxA)->anim3 = *((u16 *)(work + 6));
    ((struct EffectGfx *)owner->gfxA)->palette = D_080CBDD0[owner->kind].palette;
    ((struct EffectGfx *)owner->gfxA)->object = (u32)effect;
    work = (u8 *)(0x08102268 + ((*kindPtr) * 8));
    owner->gfxB = sub_08016190();
    if (owner->gfxB != NULL)
    {
        goto secondGfx;
    }
fail:
    sub_080C31E0((u8 *)arg0, arg0->failCb);
    return;
secondGfx:
    ((struct EffectGfx *)owner->gfxB)->type = one;
    ((struct EffectGfx *)owner->gfxB)->layer = eight;
    ((struct EffectGfx *)owner->gfxB)->priority = one;
    ((struct EffectGfx *)owner->gfxB)->gfxIndex = D_080CBDD0[owner->kind].gfxIndex;
    ((struct EffectGfx *)owner->gfxB)->anim0 = *((u16 *)(work + 0));
    ((struct EffectGfx *)owner->gfxB)->anim1 = *((u16 *)(work + 2));
    ((struct EffectGfx *)owner->gfxB)->anim2 = *((u16 *)(work + 4));
    ((struct EffectGfx *)owner->gfxB)->anim3 = *((u16 *)(work + 6));
    ((struct EffectGfx *)owner->gfxB)->palette = D_080CBDD0[owner->kind].palette;
    ((struct EffectGfx *)owner->gfxB)->object = (u32)effect;
    *((u8 *)(((u8 *)arg0) + 0x94)) = 0;
    arg0->flags |= 0x1000;
    arg0->flags |= 0x800;
    arg0->updateCb = (u32)sub_080AD6BC;
    arg0->counter = one;
    sub_080C31E0((u8 *)arg0, (u32)sub_080AD6BC);
}
