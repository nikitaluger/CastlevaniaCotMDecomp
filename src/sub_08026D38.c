/* Spawns a kind-selected attack/effect entity from the parent's state: allocates the sprite
 * and its descriptor, copies the animation data, sets its world position and extra state from
 * the coordinate tables, then advances the parent's state index. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_080279B4(void);
extern void sub_080279D8(u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 param; s16 kind; u8 _1E[4]; s16 slot; u32 updateFn; struct E *spriteDef; };
struct Arg0 { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 stateIndex; u8 _24[0x38-0x24]; u8 *sprite; struct P *state; u8 _40[0x4C-0x40]; s16 x; u8 _4E[6]; s16 y; u8 _56[0x5C-0x56]; s16 param; u8 _5E[0x6C-0x5E]; u16 kind; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 gCameraState;
struct SpriteDef { u8 _0[4]; u16 gfxA; u16 gfxB; u8 _8[0x28-8]; };
extern struct SpriteDef gEffectGfxTable[];
extern u16 D_080CE910[];
extern u32 D_080CE918[];
extern u8 gSpriteAnimDataTable[];
extern s32 gMainObjTimerCallback[];

void sub_08026D38(struct Arg0 *arg0) {
    u8 *sprite;
    struct P *state;
    u8 *scratchBuf;
    u8 *childDef;
    s32 slotIndex;
    u32 attrs;
    u32 zero;
    u32 zero2;
    u8 *coordBase;
    u8 *extra;
    s32 *tablePtr;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        sub_080279D8((u8 *)arg0);
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    arg0->sprite = sprite;
    allocWorkSlot((u8 *)arg0, 0, 0xAC, 0);
    state = arg0->state;
    if (state == NULL) {
        sub_080279D8((u8 *)arg0);
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    scratchBuf = (u8 *)state + 0x34;
    state->updateFn = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_080279B4;
    state->kind = arg0->kind;
    zero = 0;
    zero2 = 0;
    state->param = 1;
    state->x = arg0->x << 16;
    state->y = arg0->y << 16;
    slotIndex = findKindIndex(state->kind);
    state->slot = slotIndex;
    if ((s32)(slotIndex << 16) < 0) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    initSpriteGraphics(sprite, scratchBuf, (s32)gSpriteAnimDataTable + state->kind * 0xC);
    childDef = allocEffectPart();
    state->spriteDef = (struct E *)childDef;
    if (childDef == NULL) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }

    state->spriteDef->f1 = zero;
    state->spriteDef->f2 = 8;
    state->spriteDef->f3 = 1;
    state->spriteDef->f4 = gEffectGfxTable[state->kind].gfxA;
    state->spriteDef->f6 = D_080CE910[0];
    state->spriteDef->f8 = D_080CE910[1];
    state->spriteDef->fA = D_080CE910[2];
    state->spriteDef->fC = D_080CE910[3];
    state->spriteDef->fE = gEffectGfxTable[state->kind].gfxB;
    state->spriteDef->f10 = (u32)sprite;
    state->spriteDef->f14 = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    extra = (u8 *)state + 0x48;
    *(u32 *)(extra + 0x10) = zero2;
    *(u32 *)(extra + 0x58) = (u32)((s32)arg0->param * 8 + (s32)D_080CE918);
    setAnimationFrame(sprite, scratchBuf, 0x0F, 0x01);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->stateIndex + 0x19) = zero2;
    tablePtr = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *tablePtr);
}
