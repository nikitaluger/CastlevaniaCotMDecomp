extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(u8 *, s32);
extern s32 sub_0800583C(s32);
extern s32 sub_08005820(s32);
extern void sub_0805CA00(u8 *, u8 *);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern s32 sub_080C31E4(u8 *, u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct E5 {
    u8 _0; u8 f1; u8 f2; u8 f3;
    u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE;
    u32 f10; u16 f14;
};
struct P5 {
    u8 _0[8];
    s32 x; s32 y;
    u32 f10; u32 f14; u32 param;
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u32 updateFn;
    struct E5 *spriteDef;
};
struct Ref5 { s16 x; s16 y; };
struct RefHolder5 { u8 _0[4]; struct Ref5 *ref; };
struct Arg5 {
    u8 _0[2]; u16 flags;
    u8 _4[0x22-4];
    s16 index;
    u8 _24[0x38-0x24];
    u8 *object;
    struct P5 *state;
};
struct S5 { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct S5 D_02025FF0;
struct SC5 { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct SC5 D_02021E90;
struct TBL5 { u16 f0; s16 f2; u16 f4; u8 _6[0x14-6]; };
struct TBL6 { u16 f0; s16 f2; u16 f4; u8 _6[0x28-6]; };
extern struct TBL5 D_080CB2B8[];
extern struct TBL6 D_080CBDD0[];
extern u8 D_080CD400[];
extern u16 D_080CFE3C[];
extern u16 D_080CFE44[];
extern s32 D_08671BB0;

void sub_0805C3B4(struct Arg5 *arg0) {
    struct RefHolder5 *refHolder;
    u8 *sprite;
    struct P5 *state;
    u8 *anim;
    struct E5 *gfx;
    s32 slot;
    s16 kindVal;
    u32 attrs;
    u32 zero;
    u8 *table;
    u8 *table2;
    s32 kindIndex;
    u8 *scratch;
    u8 **childSlot;
    struct E5 *child;
    s32 i;
    u8 *extra;

    refHolder = (struct RefHolder5 *)*(u32 *)((u8 *)arg0 + 0xAC);
    sprite = (u8 *)sub_0800355C();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
    return;
ok0:
    arg0->object = sprite;
    sub_0800168C((u8 *)arg0, 0, 0x98, 0);
    state = arg0->state;
    if (state == NULL) goto fail;
    anim = (u8 *)state + 0x34;
    state->updateFn = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = 0x0805C9B9;
    zero = 0;
    kindVal = *(s16 *)((u8 *)refHolder->ref + 4);
    if (kindVal == 0x172) state->kind = 0x62;
    else if (kindVal == 0x173) state->kind = 0x7C;
    table = (u8 *)D_080CB2B8;
    kindIndex = state->kind;
    state->param = ((struct TBL5 *)(table + kindIndex * 20))->f2;
    state->x = refHolder->ref->x << 16;
    state->y = refHolder->ref->y << 16;
    slot = sub_08013C2C(state->kind);
    state->slot = slot;
    if ((s32)(slot << 16) < 0) goto fail;
    sub_0801131C(sprite, anim, (s32)D_080CD400 + state->kind * 0xC);
    gfx = (struct E5 *)sub_08016190();
    state->spriteDef = gfx;
    if (gfx == NULL) goto fail;
    goto fields;
fail:
    _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
    return;
fields:
    state->spriteDef->f1 = 0;
    state->spriteDef->f2 = 8;
    state->spriteDef->f3 = 1;
    state->spriteDef->f4 = ((struct TBL5 *)(table + state->kind * 20))->f0;
    state->spriteDef->f6 = D_080CFE3C[0];
    state->spriteDef->f8 = D_080CFE3C[1];
    state->spriteDef->fA = D_080CFE3C[2];
    state->spriteDef->fC = D_080CFE3C[3];
    state->spriteDef->fE = ((struct TBL5 *)(table + state->kind * 20))->f4;
    state->spriteDef->f10 = (u32)sprite;
    state->spriteDef->f14 = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | D_02025FF0.flags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    { u32 k2 = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)((u8 *)&D_02021E90 + k2 + ((D_02025FF0.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k2 = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)((u8 *)&D_02021E90 + k2 + ((D_02025FF0.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    scratch = anim + 0x14;
    *(u32 *)scratch = state->x;
    *((u32 *)scratch + 1) = state->y;
    *((u32 *)scratch + 2) = state->x + sub_0800583C(0x2000);
    *((u32 *)scratch + 3) = state->y + sub_0800583C(0x2000);
    table2 = (u8 *)D_080CBDD0;
    for (i = 0; i <= 4; i++) {
        child = (struct E5 *)sub_08016190();
        childSlot = (u8 **)(scratch + 0x3C + i * 4);
        *childSlot = (u8 *)child;
        if (child == NULL) goto fail;
        child->f1 = 0;
        child->f2 = 8;
        child->f3 = 1;
        child->f4 = ((struct TBL6 *)(table2 + state->kind * 40))->f4;
        child->f6 = D_080CFE44[i * 4];
        child->f8 = D_080CFE44[i * 4 + 1];
        child->fA = D_080CFE44[i * 4 + 2];
        child->fC = D_080CFE44[i * 4 + 3];
        child->fE = *((u16 *)(table2 + state->kind * 40 + 6));
        child->f10 = (u32)sprite;
        child->f14 = zero;
    }
    *(u32 *)(scratch + 0x10) = zero;
    *(u32 *)(scratch + 0x14) = sub_08005820(0x10000);
    *(u32 *)(scratch + 0x18) = zero;
    *(u32 *)(scratch + 0x1C) = 0x8000;
    *(u32 *)(scratch + 0x20) = 0x200;
    *(u32 *)(scratch + 0x24) = 0x180;
    sub_0805CA00((u8 *)arg0, sprite);
    sub_08011368(sprite, anim, 0, 1);
    sub_08016664((u8 *)arg0, 0);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = 0;
    {
        s32 *st = (s32 *)0x08671BB0;
        extra = (u8 *)arg0 + 0x18;
        _call_via_r2(extra, (u8 *)arg0 + 0x22, *st);
    }
    {
        u32 idx2 = 2 * (u32)arg0->index;
        idx2 += (u32)arg0;
        extra = (u8 *)idx2;
        *(u8 *)(extra + 0x19) = *(u8 *)(extra + 0x19) + 1;
    }
    extra += arg0->index * 2;
    _call_via_r1((u8 *)arg0, *(s32 *)(*(u8 **)((u8 *)arg0 + 0x14) + *(u8 *)extra * 4));
}
