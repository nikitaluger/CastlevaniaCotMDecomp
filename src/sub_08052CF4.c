/* Spawns the fixed-kind (0x4F) attack/effect entity from the parent's state: allocates the
 * sprite and its descriptor, copies the animation data, sets the world position from the
 * coordinate tables, then advances the parent's state index. */
extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern void sub_080530FC(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 param; s16 kind; u8 _1E[4]; s16 slot; u32 updateFn; struct E *spriteDef; };
struct Ref { s16 x; s16 y; };
struct RefHolder { u8 _0[4]; struct Ref *ref; };
struct Arg0 { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 stateIndex; u8 _24[0x38-0x24]; u8 *sprite; struct P *state; u8 _40[0x4C-0x40]; s16 f4C; u8 _4E[6]; s16 f54; u8 _56[0xAC-0x56]; struct RefHolder *refHolder; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct TBL3 { u16 f0; s16 f2; u16 f4; u8 _6[0x14-6]; };
extern struct TBL3 D_080CB2B8[];
extern u16 D_080CFAD8[];
extern u8 D_080CD400[];

void sub_08052CF4(struct Arg0 *arg0) {
    u8 *sprite;
    struct P *state;
    u8 *scratchBuf;
    u8 *childDef;
    s32 slotIndex;
    u32 attrs;
    u32 zero;
    u8 *coordBase;
    u8 *table;
    s32 *tablePtr;
    struct RefHolder *refHolder;
    s32 kindIndex;
    u8 *extra;

    refHolder = arg0->refHolder;
    sprite = sub_0800355C();
    state = NULL;
    childDef = NULL;
    slotIndex = 0;
    if ((sprite == NULL) ||
        (arg0->sprite = sprite, sub_0800168C((u8 *)arg0, 0, 0x4C, 0), state = arg0->state, state == NULL) ||
        (scratchBuf = (u8 *)state + 0x34, state->updateFn = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_080530FC,
         state->kind = 0x4F,
         table = (u8 *)D_080CB2B8,
         kindIndex = state->kind, state->param = ((struct TBL3 *)table)[kindIndex].f2,
         state->x = refHolder->ref->x << 16, state->y = refHolder->ref->y << 16,
         slotIndex = sub_08013C2C(0x4F), state->slot = slotIndex, ((s32)(slotIndex << 16) < 0)) ||
        (sub_0801131C(sprite, scratchBuf, (s32)D_080CD400 + state->kind * 0xC), childDef = sub_08016190(), state->spriteDef = (struct E *)childDef, childDef == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    zero = 0;
    state->spriteDef->f1 = 0;
    state->spriteDef->f2 = 8;
    state->spriteDef->f3 = 1;
    state->spriteDef->f4 = ((struct TBL3 *)table)[state->kind].f0;
    state->spriteDef->f6 = D_080CFAD8[0];
    state->spriteDef->f8 = D_080CFAD8[1];
    state->spriteDef->fA = D_080CFAD8[2];
    state->spriteDef->fC = D_080CFAD8[3];
    state->spriteDef->fE = ((struct TBL3 *)table)[state->kind].f4;
    state->spriteDef->f10 = (u32)sprite;
    state->spriteDef->f14 = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | D_02025FF0.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    coordBase = (u8 *)&D_02021E90;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + coordOff + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + coordOff + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)((u8 *)state + 0x48) = zero;
    sub_08011368(sprite, scratchBuf, 0, 1);
    sub_08016664((u8 *)arg0, 0);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->stateIndex + 0x19) = 0;
    tablePtr = (s32 *)0x08671BB0;
    extra = (u8 *)arg0 + 0x18;
    _call_via_r2(extra, (u8 *)arg0 + 0x22, *tablePtr);
    {
        u32 idx2 = 2 * (u32)arg0->stateIndex;
        u8 *stateBytePtr;
        idx2 += (u32)arg0;
        stateBytePtr = (u8 *)idx2;
        *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
    }
    {
        extra += arg0->stateIndex * 2;
        sub_080C31E0((u8 *)arg0, *(s32 *)(*(u8 **)((u8 *)arg0 + 0x14) + *extra * 4));
    }
}
