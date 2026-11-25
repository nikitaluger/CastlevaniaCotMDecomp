/* Spawns the fixed-kind (0x1E) attack/effect entity from the parent: allocates the sprite
 * and descriptor, picks the animation from the parent's flags, sets the world position and
 * copies the parent's extra parameters, then advances the parent's state index. */
extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08020478(void);
struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 param; s16 kind; u8 _1E[4]; s16 slot; u32 updateFn; struct E *spriteDef; };
struct Arg0 { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 stateIndex; u8 _24[0x38-0x24]; u8 *sprite; struct P *state; u8 _40[0x4C-0x40]; s16 x; u8 _4E[6]; s16 y; u8 _56[0x5C-0x56]; u16 animFlags; u8 _5E[0x6C-0x5E]; u32 paramA; u8 _70[0x7C-0x70]; u32 paramB; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
struct SpriteDef { u8 _0[8]; u16 gfxA; u16 gfxB; u8 _C[0x28-0xC]; };
extern struct S_02025FF0 D_02025FF0;
extern struct S_02021E90 D_02021E90;
extern u8 D_080CD400[];
extern struct SpriteDef D_080CBDD0[];
extern u16 D_080CE79C[];
extern s32 D_08671BB0[];

void sub_080200A0(struct Arg0 *arg0) {
    u8 *sprite;
    struct P *state;
    u8 *scratchBuf;
    s32 slotIndex;
    u32 attrs;
    u8 *coordBase;
    s32 *tablePtr;
    struct P *foundState;

    sprite = sub_0800355C();
    if (sprite == NULL) goto fail;
    arg0->sprite = sprite;
    sub_0800168C((u8 *)arg0, 0, 0x48, 0);
    foundState = arg0->state;
    if (foundState == NULL) goto fail;
    state = foundState;
    scratchBuf = (u8 *)state + 0x34;
    state->updateFn = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_08020478;
    state->kind = 0x1E;
    state->param = 2;
    state->x = arg0->x << 16;
    state->y = arg0->y << 16;
    slotIndex = sub_08013C2C(0x1E);
    state->slot = slotIndex;
    if ((s32)(slotIndex << 16) < 0) goto fail;
    sub_0801131C(sprite, scratchBuf, (s32)D_080CD400 + state->kind * 0xC);
    {
        if (*(u16 *)((u8 *)arg0 + 0x5C) & 0x100)
            sub_08011368(sprite, scratchBuf, 0x13, 0);
        else if (*(u16 *)((u8 *)arg0 + 0x5C) & 0x200)
            sub_08011368(sprite, scratchBuf, 0x15, 0);
        else
            sub_08011368(sprite, scratchBuf, 0x17, 0);
    }
    state->spriteDef = sub_08016190();
    if (state->spriteDef == NULL) {
    fail:
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    state->spriteDef->f1 = 0;
    state->spriteDef->f2 = 8;
    state->spriteDef->f3 = 1;
    state->spriteDef->f4 = D_080CBDD0[state->kind].gfxA;
    state->spriteDef->f6 = D_080CE79C[0];
    state->spriteDef->f8 = D_080CE79C[1];
    state->spriteDef->fA = D_080CE79C[2];
    state->spriteDef->fC = D_080CE79C[3];
    state->spriteDef->fE = D_080CBDD0[state->kind].gfxB;
    state->spriteDef->f10 = (u32)sprite;
    state->spriteDef->f14 = 0;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | D_02025FF0.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    state->f10 = arg0->paramA;
    state->f14 = arg0->paramB;
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->stateIndex + 0x19) = 0;
    tablePtr = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *tablePtr);
}
