/* Spawns a kind-selected attack/effect entity: allocates the sprite and its descriptor,
 * copies the animation data, sets the world position from the coordinate tables, then
 * advances the parent's state index. */
struct A
{
  u8 _0[2];
  u16 flags;
  u8 _04[0x10];
  u32 indexTable;
  u8 _18[0xA];
  s16 stateIndex;
  u32 updateFn;
  u8 _28[0x10];
  u32 sprite;
  u32 state;
  u8 _40[0xC];
  u8 kindIndex;
  u8 _4D[0xF];
  u32 x;
  u8 _60[0xC];
  u32 y;
  u8 _70[0xC];
  u32 direction;
};
struct B
{
  u8 _0[8];
  u32 x;
  u32 y;
  u32 direction;
  u8 _14[8];
  s16 kind;
  u8 _1E[4];
  u16 slot;
  u32 updateFn;
  u32 spriteDef;
  u8 _2C[8];
  u32 f34;
};
struct Obj
{
  u16 attrs;
  u8 _02[0x12];
  u32 x;
  u32 y;
  u32 magic;
};
struct SpriteDef
{
  u8 f00;
  u8 f01;
  u8 f02;
  u8 f03;
  u16 f04;
  u16 f06;
  u16 f08;
  u16 f0A;
  u16 f0C;
  u16 f0E;
  u32 f10;
};
struct Tbl
{
  u8 _pad[4];
  u16 gfxA;
  u16 gfxB;
  u8 _08[0x20];
};
void *sub_0800355C(void);
void sub_0800168C(void *, u32, u32, u32);
void sub_08014288(void *, void *, void *);
void sub_08014290(void);
u32 sub_08013C2C(s16);
void sub_0801131C(void *, void *, void *);
void sub_08011368(void *, void *, u32, u32);
void sub_08014668(void *, u32);
void *sub_08016190(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
extern u8 D_080CBDD0[];
extern u16 D_080CF55C[];
extern u8 D_080CD400[];
extern u32 D_080CF564[];
extern u8 D_02025FF0[];
extern u8 D_02021E90[];
extern u32 D_08671BB0;
void sub_08044000(struct A *actor)
{
  struct Obj *sprite;
  struct B *state;
  u8 *scratchBuf;
  u8 *globalState;
  u8 *spriteCfg;
  u8 *spriteTable;
  u32 attrs;
  u32 slotIndex;
  s16 stateIndex;
  sprite = (struct Obj *) sub_0800355C();
  if (sprite == NULL)
  {
    goto fail;
  }
  actor->sprite = (u32) sprite;
  sub_0800168C(actor, 0, 0x48, 0);
  if (actor->state == 0)
  {
    goto fail;
  }
  sprite->magic = 0x80000009;
  state = (struct B *) actor->state;
  scratchBuf = ((u8 *) state) + 0x34;
  sub_08014288(actor, state, &sub_08014290);
  state->kind = (s16) D_080CF564[actor->kindIndex];
  state->x = actor->x;
  state->y = actor->y;
  state->direction = actor->direction;
  slotIndex = sub_08013C2C(state->kind);
  state->slot = (u16) slotIndex;
  if (((s16) ((u16) slotIndex)) < 0)
  {
    goto fail;
  }
  attrs = ((u32) (((s32) ((s16) state->slot)) << 6)) + (0x80 << 2);
  attrs |= (slotIndex + 8) << 12;
  sprite->attrs = (u16) attrs;
  globalState = D_02025FF0;
  attrs |= *((u16 *) (globalState + 0x18C2));
  sprite->attrs = (u16) attrs;
  sub_0801131C(sprite, scratchBuf, (void *) (D_080CD400 + (12 * ((s32) state->kind))));
  sub_08011368(sprite, scratchBuf, 0x13, 0);
  sub_08014668(sprite, state->direction);
  spriteCfg = (u8 *) D_080CF55C;
  state->spriteDef = (u32) sub_08016190();
  if (state->spriteDef == 0)
  {
    goto fail;
  }
  goto cont;
  fail:
  sub_080C31E0(actor, actor->updateFn);

  return;
  cont:
  ((u8 *) state->spriteDef)[1] = 5;

  ((u8 *) state->spriteDef)[2] = 8;
  ((u8 *) state->spriteDef)[3] = 1;
  {
    u8 *defBytes = (u8 *) state->spriteDef;
    spriteTable = D_080CBDD0;
    ((struct SpriteDef *) defBytes)->f04 = ((struct Tbl *) (spriteTable + (((s32) state->kind) * 40)))->gfxA;
  }
  ((struct SpriteDef *) state->spriteDef)->f06 = *((u16 *) (&spriteCfg[0]));
  ((struct SpriteDef *) state->spriteDef)->f08 = *((u16 *) (&spriteCfg[2]));
  ((struct SpriteDef *) state->spriteDef)->f0A = *((u16 *) (&spriteCfg[4]));
  ((struct SpriteDef *) state->spriteDef)->f0C = *((u16 *) (&spriteCfg[6]));
  ((struct SpriteDef *) state->spriteDef)->f0E = ((struct Tbl *) (spriteTable + (((s32) state->kind) * 40)))->gfxB;
  *((u32 *) (((u8 *) state->spriteDef) + 0x10)) = (u32) sprite;
  {
    u8 *coordTable = D_02021E90;
    u8 *sceneState = D_02025FF0;
    u8 *base1;
    u8 *base2c;
    u32 coordIndex;
    sceneState += 0x18A8;
    coordIndex = ((u32)*sceneState + 1) * 0x40;
    base1 = coordTable + 0x1278;
    sprite->x = state->x - ((*(u32 *)(base1 + coordIndex) + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*sceneState + 1) * 0x40;
    base2c = coordTable + 0x127C;
    sprite->y = state->y - ((*(u32 *)(base2c + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  actor->flags |= 0x1000;
  stateIndex = *((s16 *) (((u8 *) actor) + 0x22));
  *((((u8 *) actor) + (((s32) stateIndex) * 2)) + 0x19) = 0;
  {
    u32 *callbackTable = &D_08671BB0;
    u8 *extra = ((u8 *) actor) + 0x18;
    u8 *stateIndexPtr = ((u8 *) actor) + 0x22;
    sub_080C31E4(extra, stateIndexPtr, *callbackTable);
    {
      s16 index2 = *((s16 *) stateIndexPtr);
      u8 *stateByte = (u8 *)((((s32) index2) * 2) + (u32) actor);
      stateByte[0x19] = (u8) (stateByte[0x19] + 1);
    }
    {
      s16 index3 = *((s16 *) stateIndexPtr);
      u8 *stateBytePtr = extra + (((s32) index3) * 2);
      sub_080C31E0(actor, *((u32 *) ((((u32) (*stateBytePtr)) * 4) + actor->indexTable)));
    }
  }
}
