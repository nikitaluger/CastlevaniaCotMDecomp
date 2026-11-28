extern volatile unsigned char getMapTileAttribute(s32, s32, s32);
extern void setEntityForm(s32, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
struct SpecialTileWorkspace
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
extern struct SpecialTileWorkspace gMainWorkspace;
struct CameraButtonView
{
  u8 _0[0x146E];
  u16 buttons;
};
extern struct CameraButtonView gCameraState;
extern u8 gTilemapPages[];
extern s32 gScriptStepCallbacks;
struct ActorStep
{
  u8 _0[0x19];
  u8 timer;
};
struct TileActionActor
{
  u8 _0[0x22];
  s16 step;
};
struct TileInteraction
{
  u8 _0[0x48];
  u32 active;
};
struct TileWorldPosition
{
  s32 x;
  s32 y;
  s32 z;
};

/* Handle the action button over a special map tile: when map mode is idle (or
 * already reading input) read the tile attribute under the player. A warp tile
 * (0x15, or 0x14 with no pending event) plays the transition animation and
 * returns the new script state; anything else cancels with state 5. */
s32 handleSpecialTileAction(struct TileActionActor *actor, s32 entity, struct TileInteraction *interaction, struct TileWorldPosition *pos)
{
  u32 tileAttr;
  if (gMainWorkspace.mode != 0)
  {
    if (gMainWorkspace.buttons & SPECIAL_TILE_INTERACT_BUTTON)
    {
      goto checkTile;
    }
    goto ret0;
  }
  if (!(gCameraState.buttons & SPECIAL_TILE_INTERACT_BUTTON))
  {
    goto ret0;
  }
  checkTile:
  tileAttr = getMapTileAttribute((s32) (gTilemapPages + (gMainWorkspace.room * 0x40)), pos->x, pos->y + 0x10000) & SPECIAL_TILE_ATTR_MASK;

  switch (tileAttr)
  {
  case SPECIAL_TILE_WARP:
    setEntityForm(entity, interaction, 0x34);
    ((struct ActorStep *) (((u8 *) actor) + (actor->step * 2)))->timer = 0;
    {
      s32 *stepCallbacks = &gScriptStepCallbacks;
      sub_080C31E8(((u8 *) actor) + 0x18, ((u8 *) actor) + 0x22, 0x2F, *stepCallbacks);
    }
    return 0x2F;
  case SPECIAL_TILE_DOOR:
    {
      s32 pendingEvent = gMainWorkspace.event;
      if (pendingEvent == 0)
      {
        setEntityForm(entity, interaction, 0x34);
        ((struct ActorStep *) (((u8 *) actor) + (actor->step * 2)))->timer = (u8) pendingEvent;
        {
          s32 *stepCallbacks = &gScriptStepCallbacks;
          sub_080C31E8(((u8 *) actor) + 0x18, ((u8 *) actor) + 0x22, 0x30, *stepCallbacks);
        }
        return 0x30;
      }
    }
  default:
    setEntityForm(entity, interaction, 2);
    interaction->active = 1;
    pos->z = 0;
    ((struct ActorStep *) (((u8 *) actor) + (actor->step * 2)))->timer = 0;
    {
      s32 *stepCallbacks = &gScriptStepCallbacks;
      sub_080C31E8(((u8 *) actor) + 0x18, ((u8 *) actor) + 0x22, 5, *stepCallbacks);
    }
    return 5;
  }
  ret0:
  return 0;

}
