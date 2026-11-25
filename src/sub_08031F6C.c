/* Spawns a state-selected attack/effect entity: allocates the sprite and its descriptor,
 * sets its animation, world position and sprite attributes, then advances the parent's
 * state index and calls the parent's state callback. */
extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08032290(void);
extern void sub_080322B0(u8 *, void *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, void *);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 param; s16 kind; u8 _1E[4]; s16 slot; u32 updateFn; struct E *spriteDef; };
struct Arg0 { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 stateIndex; u8 _24[0x38-0x24]; u8 *sprite; struct P *state; u8 _40[0x4C-0x40]; s16 x; u8 _4E[6]; s16 y; u8 _56[0x5C-0x56]; s16 direction; u8 _5E[0x64-0x5E]; s16 kind; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct SpriteDef { u8 _0[8]; u16 gfxA; u16 gfxB; u8 _c[0x28-0xC]; };
extern struct SpriteDef D_080CBDD0[];
extern u16 D_080CEBA8[];
extern u8 D_080CD400[];
extern void *D_08671BB0;

void sub_08031F6C(struct Arg0 *arg0) {
    u8 *sprite;
    struct P *state;
    u8 *scratchBuf;
    u8 *childDef;
    s32 slotIndex;
    u32 attrs;
    u32 zero;
    u32 one;
    u8 *coordBase;

    sprite = sub_0800355C();
    if (sprite == NULL) goto fail;
    arg0->sprite = sprite;
    sub_0800168C((u8 *)arg0, 0, 0x48, 0);
    state = arg0->state;
    if (state == NULL) goto fail;
    scratchBuf = (u8 *)state + 0x34;
    state->updateFn = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_08032290;
    state->kind = arg0->kind;
    zero = 0;
    one = 1;
    state->param = one;
    state->x = arg0->x << 16;
    state->y = arg0->y << 16;
    slotIndex = sub_08013C2C(state->kind);
    state->slot = slotIndex;
    if ((slotIndex << 16) < 0) goto fail;
    sub_0801131C(sprite, scratchBuf, (s32)D_080CD400 + state->kind * 0xC);
    childDef = sub_08016190();
    state->spriteDef = (struct E *)childDef;
    if (childDef == NULL) goto fail;
    goto body;
fail:
    sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
    return;
body:
    state->spriteDef->f1 = zero;
    state->spriteDef->f2 = 8;
    state->spriteDef->f3 = one;
    state->spriteDef->f4 = D_080CBDD0[state->kind].gfxA;
    state->spriteDef->f6 = D_080CEBA8[0];
    state->spriteDef->f8 = D_080CEBA8[1];
    state->spriteDef->fA = D_080CEBA8[2];
    state->spriteDef->fC = D_080CEBA8[3];
    state->spriteDef->fE = D_080CBDD0[state->kind].gfxB;
    state->spriteDef->f10 = (u32)sprite;
    state->spriteDef->f14 = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | D_02025FF0.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)(sprite + 0x28) = 0x2E;
    if (arg0->direction > 0) *(u16 *)(sprite + 2) |= 0x10;
    sub_080322B0(sprite, (u8 *)state);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = zero;
    {
        void **callbackTable = &D_08671BB0;
        u8 *extra = (u8 *)arg0 + 0x18;
        sub_080C31E4(extra, (u8 *)arg0 + 0x22, *callbackTable);
        {
            u8 *bytePtr = (u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2);
            u8 *stateBytePtr = extra;
            u8 scriptIndex;
            void *callback;
            bytePtr += (u32)arg0;
            bytePtr[0x19]++;
            stateBytePtr += *(s16 *)((u8 *)arg0 + 0x22) * 2;
            scriptIndex = *stateBytePtr;
            callback = ((void **)*(void **)((u8 *)arg0 + 0x14))[scriptIndex];
            sub_080C31E0((u8 *)arg0, callback);
        }
    }
}
