s32 checkActorViewBounds(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void releaseActorSlotsAlt(void *);
void updateActorWorldPosition(void *);
void playSound(u16);
void sub_080C31E8(void *, void *, s32, u32);
s32 updateObjectDisplayState(void *, void *);
s32 sub_080C31E0(s32, s32);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, s32);
void syncSpriteToWorldPosition(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 sPlayerAltScriptStepTable[];
extern u32 gScriptEventCallbacks[];

/*
 * Alternate-variant per-frame actor update: test whether the actor has left
 * the camera view, run its reaction/attack and script-step logic using the
 * alternate script table, advance the animation, and place the sprite relative
 * to the camera.
 */
void updatePlayerActorAlt(u8 *actor)
{
  u8 *sprite;
  u8 *player;
  u8 *animState;
  u8 *extra;
  u8 *coordTable;
  u8 *camIndexPtr;
  u32 tableIndex;
  u32 camOffset;
  u32 outsideView;
  u8 scriptByte;
  u8 *scriptPtr;
  s32 scriptIdx;
  s32 zero;
  sprite = *((u8 **) (actor + 0x38));
  player = *((u8 **) (actor + 0x3C));
  animState = player + 0x34;
  extra = player + 0x48;
  if (checkActorViewBounds(sprite, player) == 1)
  {
    *((u16 *) (extra + 0x0A)) = 0;
  }
  else
  {
    *((u16 *) (extra + 0x0A)) = 1;
  }
  zero = 0;
  *((u32 *) (extra + 0x00)) = zero;
  outsideView = *((s16 *) (extra + 0x0A));
  if (outsideView == ((unsigned short) 1))
  {
    applySpritePaletteVariant(actor, sprite);
    if (sub_08013558(sprite, player, *((void **) (player + 0x28))) != 0)
    {
      spawnContactEffectOnHit(actor, *((void **) (player + 0x28)));
    }
    uploadPendingSpriteGraphic(actor, *((void **) (player + 0x28)));
    outsideView = outsideView & (*((u16 *) player));
    if (outsideView && ((*((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x1A))) != 4))
    {
      u32 *scriptTable;
      releaseActorSlotsAlt(actor);
      updateActorWorldPosition(actor);
      playSound(0x85);
      *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x1B)) = zero;
      scriptTable = gScriptEventCallbacks;
      sub_080C31E8(actor + 0x18, actor + 0x22, 4, *scriptTable);
    }
    if ((*((u16 *) player)) & 0x0C)
    {
      releaseActorSlotsAlt(actor);
    }
  }
  if (updateObjectDisplayState(sprite, player) == 0)
  {
    u8 *scriptState;
    *((u32 *) (actor + 0x14)) = (u32) sPlayerAltScriptStepTable;
    *((u16 *) (actor + 0x22)) = (*((u16 *) (actor + 0x22))) + 1;
    scriptState = (u8 *) ((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor));
    *((u8 *) (scriptState + 0x19)) = (*((u8 *) (scriptState + 0x19))) + 1;
    scriptIdx = (*((s16 *) (actor + 0x22))) * 2;
    scriptPtr = actor;
    scriptPtr += 0x18;
    scriptByte = *((u8 *) (((u32) scriptPtr) + ((u32) scriptIdx)));
    sub_080C31E0((s32) actor, *((u32 *) ((*((u32 *) (actor + 0x14))) + (scriptByte * 4))));
    *((u16 *) (actor + 0x22)) = (*((u16 *) (actor + 0x22))) - 1;
    if (((*((u16 *) (actor + 2))) & 0x8000) == 0)
    {
      stepAnimationTrack(sprite, animState);
      advanceMotion(player, 0);
    }
    else
    {
      return;
    }
  }
  syncSpriteToWorldPosition(actor, sprite);
  {
    s32 worldPos = (*((s32 *) (player + 0x0C))) + (*((s32 *) (extra + 0x00)));
    coordTable = gCameraState;
    camIndexPtr = gMainWorkspace;
    camIndexPtr += 0x18A8;
    tableIndex = (((u32) (*camIndexPtr)) + 1) * 0x40;
    coordTable += 0x127C;
    camOffset = *((u32 *) (coordTable + tableIndex));
    *((u32 *) (sprite + 0x18)) = worldPos - ((camOffset + 0xFFFF8000) & 0xFFFF0000);
  }
}
