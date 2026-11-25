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
  u8 _10[8];
  u32 velY;
  s16 spriteType;
  u8 _1E[4];
  s16 attrIndex;
  u32 prevCallback;
  struct SpriteLayer *layer;
  u8 _2C[0x1C];
  s32 extra;
};
struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  u32 x;
  u8 _18[0xA];
  s16 childIndex;
  u32 callback;
  u8 _28[0x10];
  u8 *sprite;
  struct GfxState *state;
  u8 _40[0x6C];
  void *spawnParams;
};
struct S_02025FF0_2E { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0_2E D_02025FF0;
struct S_02021E90_2E { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90_2E D_02021E90;
struct Attr16 { u16 f0; s16 motion; };
struct Attr14 { u16 attr0; u16 attr1; u16 attr2; u8 _6[0xE]; };
extern u8 D_080CB2B8[];
extern u16 D_080CEB08[];
extern u8 D_080CD400[];
extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011408(u8 *, u8 *, s32, s32, s32);
extern s32 sub_08014938(s32);
extern void sub_08016664(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern void sub_0802E8EC(void);
extern u32 D_08671BB0;

/* Builds an entity's graphics from its spawn parameters: allocates the sprite
 * and state, fills a sprite layer, positions the sprite and updates the entity. */
void sub_0802E27C(struct Entity *arg0) {
    void *spawnParams;
    u8 *sprite;
    struct GfxState *state;
    u8 *anim;
    u8 *attrTable;
    struct SpriteLayer *layer;
    struct SpriteLayer *layer3;
    s16 *coords;
    u32 one;
    u32 spriteIndex;
    u32 attr;
    u8 *coordBase;
    u8 *childEntry;
    u8 *childEntry2;
    u8 *stateArr;
    u32 *lit;
    s32 **callbackTable;
    u32 index;

    spawnParams = arg0->spawnParams;
    sprite = sub_0800355C();
    state = NULL;
    layer = NULL;
    if ((sprite == NULL) ||
        (arg0->sprite = sprite, sub_0800168C((u8 *)arg0, 0, 0x50, 0), state = arg0->state, state == NULL) ||
        (anim = (u8 *)state + 0x34, state->prevCallback = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0802E8EC,
         state->spriteType = 0x29, attrTable = (u8 *)0x080CB2B8, state->velY = ((struct Attr16 *)attrTable)[0xCD].motion,
         coords = *(s16 **)((u8 *)spawnParams + 4),
         state->x = coords[0] << 16, state->y = coords[1] << 16,
         spriteIndex = sub_08013C2C(0x29), state->attrIndex = (s16)spriteIndex, ((s32)(spriteIndex << 16) < 0)) ||
        (sub_0801131C(sprite, anim, (s32)D_080CD400 + state->spriteType * 0xC), layer = (struct SpriteLayer *)sub_08016190(), state->layer = layer, layer == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    state->layer->byte1 = 0;
    state->layer->byte2 = 8;
    layer3 = state->layer;
    one = 1;
    layer3->byte3 = one;
    state->layer->attr0 = ((struct Attr14 *)attrTable)[state->spriteType].attr0;
    state->layer->attr1 = D_080CEB08[0];
    state->layer->attr2 = D_080CEB08[1];
    state->layer->attr3 = D_080CEB08[2];
    state->layer->attr4 = D_080CEB08[3];
    state->layer->attr5 = ((struct Attr14 *)attrTable)[state->spriteType].attr2;
    state->layer->sprite = (u32)sprite;
    state->layer->flags14 = 0;
    attr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attr;
    *(u16 *)sprite = attr | D_02025FF0.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    state->extra = 0;
    if (sub_08014938(state->x) > 0)
        *(u16 *)(sprite + 2) = (u16)(*(u16 *)(sprite + 2) | 0x10);
    sub_08011408(sprite, anim, 0, state->extra, one);
    sub_08016664((u8 *)arg0, 0);
    arg0->flags |= 0x1000;
    childEntry = (u8 *)(arg0->childIndex * 2 + (u32)arg0);
    childEntry[0x19] = 0;
    lit = &D_08671BB0;
    stateArr = (u8 *)arg0 + 0x18;
    sub_080C31E4(stateArr, (u8 *)arg0 + 0x22, *lit);
    childEntry2 = (u8 *)(arg0->childIndex * 2 + (u32)arg0);
    childEntry2[0x19] = (u8)(childEntry2[0x19] + 1);
    stateArr += arg0->childIndex * 2;
    index = stateArr[0];
    callbackTable = *(s32 **)((u8 *)arg0 + 0x14);
    _call_via_r1((u8 *)arg0, callbackTable[index]);
}
