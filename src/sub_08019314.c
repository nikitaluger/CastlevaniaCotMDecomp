struct SpriteLayer
{
  u8 _0;
  u8 byte1;
  u8 byte2;
  u8 byte3;
  u16 attr0;
  u16 attr1;
  u16 attr2;
  u16 attr3;
  u16 attr4;
  u16 attr5;
  u32 sprite;
  u16 flags14;
};
struct GfxState
{
  u8 _0[8];
  s32 x;
  s32 y;
  u32 z;
  u32 velX;
  u32 velY;
  s16 spriteType;
  u8 _1E[4];
  s16 attrIndex;
  u32 prevCallback;
  struct SpriteLayer *layer;
};
struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x22-4];
  s16 childIndex;
  u8 _24[0x38-0x24];
  u8 *sprite;
  struct GfxState *state;
  u8 _40[0x4C-0x40];
  s16 param1;
  u8 _4E[6];
  s16 param2;
  u8 _56[0x5C-0x56];
  s16 param3;
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct AttrEntry { u8 _0[4]; u16 f4; u16 f6; u8 _8[4]; u16 fC; u16 fE; u8 _10[0x18]; };
extern struct AttrEntry D_080CBDD0[];
extern u16 D_080CE5E8[];
extern u32 D_080CE600[];
extern u8 D_080CD400[];
extern s32 D_08671BB0[];
extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08019954(void);
extern void sub_08019978(u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

/* Builds an entity's graphics: allocates its sprite and state, fills a sprite
 * layer, positions the sprite, then updates the entity's child bookkeeping. */
void sub_08019314(struct Entity *arg0) {
    u8 *sprite;
    struct GfxState *state;
    u8 *anim;
    u8 *layer;
    s32 spriteIndex;
    u32 attr;
    u32 zero;
    u8 *coordBase;
    u8 *extra;
    u8 *stateArr;
    s32 *lit;

    sprite = sub_0800355C();
    if (sprite == NULL) {
        sub_08019978((u8 *)arg0);
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    arg0->sprite = sprite;
    sub_0800168C((u8 *)arg0, 0, 0x5C, 0);
    state = arg0->state;
    if (state == NULL) {
        sub_08019978((u8 *)arg0);
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    anim = (u8 *)state + 0x34;
    state->prevCallback = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_08019954;
    state->spriteType = 0x55;
    zero = 0;
    state->velY = 1;
    state->x = arg0->param1 << 16;
    state->y = arg0->param2 << 16;
    spriteIndex = sub_08013C2C(0x55);
    state->attrIndex = spriteIndex;
    if ((s32)(spriteIndex << 16) < 0) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    sub_0801131C(sprite, anim, (s32)D_080CD400 + state->spriteType * 0xC);
    layer = sub_08016190();
    state->layer = (struct SpriteLayer *)layer;
    if (layer == NULL) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }

    state->layer->byte1 = zero;
    state->layer->byte2 = 8;
    state->layer->byte3 = 1;
    state->layer->attr0 = D_080CBDD0[state->spriteType].fC;
    state->layer->attr1 = D_080CE5E8[0];
    state->layer->attr2 = D_080CE5E8[1];
    state->layer->attr3 = D_080CE5E8[2];
    state->layer->attr4 = D_080CE5E8[3];
    state->layer->attr5 = D_080CBDD0[state->spriteType].fE;
    state->layer->sprite = (u32)sprite;
    state->layer->flags14 = zero;
    attr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attr;
    *(u16 *)sprite = attr | D_02025FF0.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    extra = (u8 *)state + 0x48;
    *(u32 *)(extra + 0) = (u32)state->x;
    *(u32 *)(extra + 4) = (u32)state->y;
    *(u32 *)(extra + 0x10) = (u32)((s32)arg0->param3 * 12 + (s32)D_080CE600);
    sub_08011368(sprite, anim, 0x1A, 0x00);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->childIndex + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    stateArr = (u8 *)arg0 + 0x18;
    sub_080C31E4(stateArr, (u8 *)arg0 + 0x22, *lit);
    ++*(u8 *)((u8 *)arg0 + 2 * arg0->childIndex + 0x19);
    stateArr += 2 * arg0->childIndex;
    sub_080C31E0((u8 *)arg0, *(s32 *)(*(u32 *)((u8 *)arg0 + 0x14) + (u32)*stateArr * 4));
}
