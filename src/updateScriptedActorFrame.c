/* Per-frame update for a scripted actor: flag it visible or off-screen, tick
 * its tracker, sync animation flags, dispatch one action from
 * gActorActionHandlers, then refresh the sprite's camera-relative position. */
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern void hitTestEntities(void *);
extern s32 _call_via_r1(s32, s32);
extern void _call_via_r3(void *, void *, s32, u32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gActorActionHandlers[];
extern u32 gScriptEventCallbacks[];
struct SpriteFlags { u8 flags; };
struct AnimState { u16 flags; };
void updateScriptedActorFrame(u8 *entity)
{
  u8 *sprite;
  u8 *actor;
  u8 *animState;
  u8 *stepEntry;
  u8 *stepEntry2;
  u8 *scriptBase;
  u8 *scrollTable;
  u8 *frameCounterPtr;
  u8 *scrollXField;
  s32 outsideView;
  s32 stepOffset;
  u32 scrollOffset;
  u32 scrollX;
  u8 *screenY;
  u32 scrollY;
  u8 actionIndex;
  sprite = *((u8 **) (entity + 0x38));
  actor = *((u8 **) (entity + 0x3C));
  animState = actor + 0x34;
  outsideView = isOutsideCameraBounds(*((s32 *) (actor + 8)), *((s32 *) (actor + 0xC)));
  if (outsideView == 1)
  {
    ((struct SpriteFlags *) (sprite + 0x2A))->flags &= 0xBF;
    *((u8 *) ((*((u8 **) (actor + 0x28))) + 1)) = 0;
  }
  else
  {
    ((struct SpriteFlags *) (sprite + 0x2A))->flags |= 0x40;
    *((u8 *) ((*((u8 **) (actor + 0x28))) + 1)) = 5;
  }
  hitTestEntities(*((void **) (actor + 0x28)));
  if ((*((u16 *) (entity + 0x5C))) & 1)
  {
    ((struct AnimState *) actor)->flags |= 1;
  }
  if ((*((u16 *) actor)) & 1)
  {
    *((u8 *) ((*((u8 **) (actor + 0x28))) + 1)) = 0;
    stepEntry = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    if ((*((u8 *) (stepEntry + 0x1A))) != 3)
    {
      *((u8 *) (stepEntry + 0x1B)) = 0;
      {
        u32 *callbackTable = (u32 *) gScriptEventCallbacks;
        _call_via_r3(entity + 0x18, entity + 0x22, 3, *callbackTable);
      }
    }
  }
  if (updateObjectDisplayState(sprite, actor) != 0)
  {
    goto table;
  }
  *((u32 *) (entity + 0x14)) = (u32) gActorActionHandlers;
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
  stepEntry2 = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
  *((u8 *) (stepEntry2 + 0x19)) = (*((u8 *) (stepEntry2 + 0x19))) + 1;
  stepOffset = (*((s16 *) (entity + 0x22))) * 2;
  scriptBase = entity + 0x18;
  actionIndex = *((u8 *) (((u32) scriptBase) + ((u32) stepOffset)));
  _call_via_r1((s32) entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (actionIndex * 4))));
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
  if (((*((u16 *) (entity + 2))) & (0x80 << 8)) != 0)
  {
    return;
  }
  stepAnimationTrack(sprite, animState);
  advanceMotion(actor, 0);
  table:
  scrollTable = gCameraState;

  frameCounterPtr = gMainWorkspace;
  frameCounterPtr = frameCounterPtr + 0x18A8;
  scrollOffset = (((u32) (*frameCounterPtr)) + 1) * 0x40;
  scrollXField = scrollTable + 0x1278;
  scrollX = *((u32 *) (scrollXField + scrollOffset));
  *((u32 *) (sprite + 0x14)) = (*((u32 *) (actor + 8))) - ((scrollX + (0x80 << 8)) & 0xFFFF0000);
  scrollOffset = (((u32) (*frameCounterPtr)) + 1) * 0x40;
  scrollTable += 0x127C;
  screenY = sprite + 0x18;
  scrollY = *((u32 *) (scrollTable + scrollOffset));
  *((u32 *) screenY) = (*((u32 *) (actor + 0xC))) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
