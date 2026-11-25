extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern s32 sub_08005820(s32);
extern void sub_08058458(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
struct E
{
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 fE;
  u32 f10;
  u16 f14;
};
struct P
{
  u8 _0[8];
  s32 x;
  s32 y;
  u32 f10;
  u32 f14;
  u32 param;
  s16 kind;
  u8 _1E[4];
  s16 slot;
  u32 updateFn;
  struct E *spriteDef;
};
struct Ref
{
  s16 x;
  s16 y;
};
struct RefHolder
{
  u8 _0[4];
  struct Ref *ref;
};
struct Arg0
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x22 - 4];
  s16 stateIndex;
  u8 _24[0x38 - 0x24];
  u8 *sprite;
  struct P *state;
  u8 _40[0x4C - 0x40];
  s16 f4C;
  u8 _4E[6];
  s16 f54;
  u8 _56[0xAC - 0x56];
  struct RefHolder *refHolder;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
  u8 _18A9[0x19];
  u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90
{
  u8 _0[0x1278];
  u32 f1278;
  u32 f127C;
};
extern struct S_02021E90 D_02021E90;
struct TBL3
{
  u16 f0;
  s16 f2;
  u16 f4;
  u8 _6[0x14 - 6];
};
extern struct TBL3 D_080CB2B8[];
extern u16 D_080CFD58[];
extern u8 D_080CD400[];
extern s32 D_0202773C;
void sub_08057C40(struct Arg0 *arg0)
{
  u8 *sprite;
  struct P *state;
  u8 *scratchBuf;
  s32 new_var2;
  int new_var;
  u8 *childDef;
  s32 queryResult;
  u32 attrs;
  u32 zero;
  u8 *coordBase;
  u8 *table;
  s32 *tablePtr;
  struct RefHolder *refHolder;
  u32 direction;
  u8 *statePtr;
  refHolder = arg0->refHolder;
  sprite = sub_0800355C();
  state = NULL;
  childDef = NULL;
  queryResult = 0;
  if ((((sprite == NULL) || ((arg0->sprite = sprite, sub_0800168C((u8 *) arg0, 0, 0x54, 0), state = arg0->state, state == NULL))) || ((scratchBuf = ((u8 *) state) + 0x34, state->updateFn = *((u32 *) (((u8 *) arg0) + 0x24)), *((u32 *) (((u8 *) arg0) + 0x24)) = (u32) sub_08058458, zero = 0, state->kind = 0x32, table = (u8 *) D_080CB2B8, state->param = ((struct TBL3 *) (table + (0xFA * 4)))[0].f2, state->x = refHolder->ref->x << 16, state->y = refHolder->ref->y << 16, queryResult = sub_08013C2C(0x32), state->slot = queryResult, ((s32) (queryResult << 16)) < 0))) || ((sub_0801131C(sprite, scratchBuf, ((s32) D_080CD400) + (state->kind * 0xC)), childDef = sub_08016190(), state->spriteDef = (struct E *) childDef, childDef == NULL)))
  {
    sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
    return;
  }
  state->spriteDef->f1 = 0;
  state->spriteDef->f2 = 8;
  state->spriteDef->f3 = 1;
  new_var = 2;
  state->spriteDef->f4 = ((struct TBL3 *) table)[state->kind].f0;
  state->spriteDef->f6 = D_080CFD58[0];
  state->spriteDef->f8 = D_080CFD58[1];
  state->spriteDef->fA = D_080CFD58[new_var];
  state->spriteDef->fC = D_080CFD58[3];
  state->spriteDef->fE = ((struct TBL3 *) table)[state->kind].f4;
  state->spriteDef->f10 = (u32) sprite;
  state->spriteDef->f14 = zero;
  attrs = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) state) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) state) + 0x22))) + 8) << 12));
  *((u16 *) sprite) = attrs;
  *((u16 *) sprite) = attrs | D_02025FF0.f18C2;
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  coordBase = (u8 *) (&D_02021E90);
  {
    u32 coordOff = 0x1278;
    *((u32 *) (sprite + 0x14)) = state->x - (((*((u32 *) ((coordBase + coordOff) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 coordOff = 0x127C;
    u32 rawCoord = *((u32 *) ((coordBase + coordOff) + ((D_02025FF0.f18A8 + 1) << 6)));
    *((u32 *) (sprite + 0x18)) = ((u32) (state->y - 0x10000)) - ((rawCoord + 0xFFFF8000u) & 0xFFFF0000u);
  }
  {
    u8 *extra = ((u8 *) state) + 0x48;
    *((u16 *) (extra + 0)) = sub_08005820(0x79) + 0x78;
    *((u16 *) (extra + 2)) = zero;
    *((u16 *) (extra + 4)) = zero;
    *((u16 *) (extra + 6)) = 4;
    *((u32 *) (extra + 8)) = state->x;
  }
  direction = 0x2000;
  new_var2 = state->x;
  if (((s32) new_var2) > D_0202773C)
  {
    direction = 0xFFFFE000;
  }
  *((u32 *) (((u8 *) state) + 0x10)) = direction;
  *((u16 *) (((u8 *) state) + 4)) = 0x120;
  sub_08011368(sprite, scratchBuf, 0, 1);
  sub_08016664((u8 *) arg0, 0);
  arg0->flags |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->stateIndex)) + 0x19)) = 0;
  tablePtr = (s32 *) 0x08671BB0;
  statePtr = ((u8 *) arg0) + 0x18;
  sub_080C31E4(statePtr, ((u8 *) arg0) + 0x22, *tablePtr);
  {
    u32 idx2 = 2 * ((u32) arg0->stateIndex);
    u8 *stateBytePtr;
    idx2 += (u32) arg0;
    stateBytePtr = (u8 *) idx2;
    *((u8 *) (stateBytePtr + 0x19)) = (*((u8 *) (stateBytePtr + 0x19))) + 1;
  }
  {
    u8 *stateByte = statePtr + (2 * arg0->stateIndex);
    sub_080C31E0((u8 *) arg0, *((s32 *) ((*((u8 **) (((u8 *) arg0) + 0x14))) + ((*((u8 *) stateByte)) * 4))));
  }
}

