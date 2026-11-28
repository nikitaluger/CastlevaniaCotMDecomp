extern void stepDelayTimer(void *, s32);
extern unsigned short getTileAttrAtPos(s32, s32, s32);
extern void setEntityForm(s32, void *, s32);
extern s32 handleSpecialTileAction(s32, s32, void *, void *);
extern void resetActorForm(s32, void *);
struct TileActionWorkspace {
  u8 _0[0x24];
  u32 mode;
  u8 _1[0x2A - 0x28];
  u16 buttons;
  u8 _2[0x18A8 - 0x2C];
  u8 room;
};
extern struct TileActionWorkspace gMainWorkspace;
struct TileActionCamera { u8 _0[0x146E]; u16 buttons; };
extern struct TileActionCamera gCameraState;
extern u8 gTilemapPages[];
struct TileActionWork {
  u8 _0[0x38];
  s32 probeOffset;
  u8 _1[4];
  s32 state;
  u8 _2[4];
  s32 active;
  u8 _3[0xC4 - 0x4C];
  s32 resultStep;
};
struct TileActionPosition { s32 x; s32 y; s32 z; };
static inline u32 isDownPressed(u32 b)
{
  u32 m = 0x80;
  m &= b;
  return m;
}
/* Pick the next script step for a tile action: fail when Down is held or any of
 * the three tiles around the position blocks movement; otherwise reset the
 * entity form, run the special-tile handler and dispatch the step it returns. */
u16 selectTileActionStep(s32 actor, s32 entity, struct TileActionWork *work, struct TileActionPosition *position)
{
  u32 buttons;
  s32 result;
  s32 *resultSlot;
  work->active = 0;
  if (gMainWorkspace.mode != 0) buttons = gMainWorkspace.buttons;
  else buttons = gCameraState.buttons;
  if (isDownPressed(buttons)) goto fail;
  if ((getTileAttrAtPos((s32)(gTilemapPages + gMainWorkspace.room * 0x40), position->x, position->y + 0x10000) & 0x4000) ||
      (getTileAttrAtPos((s32)(gTilemapPages + gMainWorkspace.room * 0x40), position->x - work->probeOffset, position->y + 0x10000) & 0x4000) ||
      (getTileAttrAtPos((s32)(gTilemapPages + gMainWorkspace.room * 0x40), position->x + work->probeOffset, position->y + 0x10000) & 0x4000)) goto fail;
  work->state = 1;
  resetActorForm(entity, work);
  result = handleSpecialTileAction(actor, entity, work, position);
  resultSlot = (s32 *)((u8 *)work + 0xC4);
  *resultSlot = result;
  if (result != 0) {
    stepDelayTimer((u8 *)work + 0x28, entity);
    return (u16)*resultSlot;
  }
  stepDelayTimer((u8 *)work + 0x28, entity);
  return 4;
fail:
  work->state = 2;
  setEntityForm(entity, work, 5);
  stepDelayTimer((u8 *)work + 0x28, entity);
  position->z = 0;
  return 8;
}
