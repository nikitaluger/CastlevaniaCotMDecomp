extern volatile unsigned char sub_08007B78(s32, s32, s32);
extern void sub_0806A7AC(s32, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
struct S_02025FF0
{
  u8 _0[0x24];
  u32 mode;
  u8 _1[0x2A - 0x28];
  u16 buttons;
  u8 _2[0x14AC - 0x2C];
  u32 event;
  u8 _3[0x18A8 - 0x14B0];
  u8 room;
};
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90
{
  u8 _0[0x146E];
  u16 buttons;
};
extern struct S_02021E90 D_02021E90;
extern u8 D_02023130[];
extern s32 D_08671BD0;
struct Step
{
  u8 _0[0x19];
  u8 timer;
};
struct Actor
{
  u8 _0[0x22];
  s16 step;
};
struct Interaction
{
  u8 _0[0x48];
  u32 active;
};
struct Position
{
  s32 x;
  s32 y;
  s32 z;
};

/* Handle the action button over a special map tile: when the map mode is idle
 * (or already reading input) read the tile attribute under the player. A door
 * tile (0x15, or 0x14 with no pending event) plays the transition animation and
 * returns the new script state; anything else cancels the interaction with
 * state 5. */
s32 sub_0806B2C8(struct Actor *actor, s32 entity, struct Interaction *interaction, struct Position *pos)
{
  u32 attr;
  if (D_02025FF0.mode != 0)
  {
    if (D_02025FF0.buttons & 0x40)
    {
      goto checkTile;
    }
    goto ret0;
  }
  if (!(D_02021E90.buttons & 0x40))
  {
    goto ret0;
  }
  checkTile:
  attr = sub_08007B78((s32) (D_02023130 + (D_02025FF0.room * 0x40)), pos->x, pos->y + 0x10000) & 0x3F;

  switch (attr)
  {
  case 0x15:
    sub_0806A7AC(entity, interaction, 0x34);
    ((struct Step *) (((u8 *) actor) + (actor->step * 2)))->timer = 0;
    {
      s32 *handlerTable = &D_08671BD0;
      sub_080C31E8(((u8 *) actor) + 0x18, ((u8 *) actor) + 0x22, 0x2F, *handlerTable);
    }
    return 0x2F;
  case 0x14:
    {
      s32 pending = D_02025FF0.event;
      if (pending == 0)
      {
        sub_0806A7AC(entity, interaction, 0x34);
        ((struct Step *) (((u8 *) actor) + (actor->step * 2)))->timer = (u8) pending;
        {
          s32 *handlerTable = &D_08671BD0;
          sub_080C31E8(((u8 *) actor) + 0x18, ((u8 *) actor) + 0x22, 0x30, *handlerTable);
        }
        return 0x30;
      }
    }
  default:
    sub_0806A7AC(entity, interaction, 2);
    interaction->active = 1;
    pos->z = 0;
    ((struct Step *) (((u8 *) actor) + (actor->step * 2)))->timer = 0;
    {
      s32 *handlerTable = &D_08671BD0;
      sub_080C31E8(((u8 *) actor) + 0x18, ((u8 *) actor) + 0x22, 5, *handlerTable);
    }
    return 5;
  }
  ret0:
  return 0;

}
