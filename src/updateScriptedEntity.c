/* Per-frame update for a scripted effect entity: drop it when it leaves the
 * camera view, track hits and script flags, dispatch the current script step,
 * advance animation/motion, then project its world position onto the sprite. */
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern void sub_0801EF8C(void *, void *);
extern s32 hitTestEntities(void *);
extern void _call_via_r1(void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern void playSound(s32);
extern u32 sScriptStepCallbacks[];
extern u32 gScriptedEntityStepTable[];
struct SpriteDefFlags { u8 a; u8 flag; };
struct StateFlags { u16 f0; };
struct CameraScroll { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
struct WorkspaceCounter { u8 _0[0x18A8]; u8 frameCounter; };
extern struct CameraScroll gCameraState;
extern struct WorkspaceCounter gMainWorkspace;
void updateScriptedEntity(u8 *self)
{
  u8 *sprite;
  u8 *state;
  u8 *gfxInit;
  u8 *stepState;
  u8 *target;
  s32 stepOffset;
  u8 *script;
  u8 command;
  u8 *cameraBase;
  u32 scrollOffset;
  u32 *callback;
  s16 stepIndex;
  u16 *stepWords;
  sprite = *((u8 **) (self + 0x38));
  state = *((u8 **) (self + 0x3C));
  gfxInit = state + 0x34;
  stepState = state + 0x48;
  ((struct SpriteDefFlags *) (*((u32 *) (state + 0x28))))->flag |= 5;
  if ((*((s16 *) stepState)) <= 0)
  {
    if (isOutsideCameraBounds(*((s32 *) (state + 0x08)), *((s32 *) (state + 0x0C))) == 1)
    {
      _call_via_r1(self, *((u32 *) (self + 0x24)));
      return;
    }
  }
  if (hitTestEntities(*((u8 **) (state + 0x28))) != 0)
  {
    ((struct StateFlags *) state)->f0 |= 0x01;
  }
  if (((*((u16 *) ((*((u32 *) (state + 0x28))) + 0x14))) & 1) || ((*((u16 *) (self + 0x5C))) & 2))
  {
    ((struct StateFlags *) state)->f0 |= 0x01;
  }
  else
    if ((*((u16 *) (self + 0x5C))) & 2)
  {
    ((struct StateFlags *) state)->f0 |= 0x01;
  }
  if ((*((u16 *) state)) & 0x01)
  {
    ((struct SpriteDefFlags *) (*((u32 *) (state + 0x28))))->flag &= 0xFB;
    if ((*((u8 *) ((((*((s16 *) (self + 0x22))) * 2) + ((u32) self)) + 0x1A))) != 2)
    {
      playSound(0x18A);
      *((u8 *) ((((*((s16 *) (self + 0x22))) * 2) + ((u32) self)) + 0x1B)) = 0;
      callback = sScriptStepCallbacks;
      _call_via_r3(self + 0x18, self + 0x22, 2, *callback);
    }
  }
  if (updateObjectDisplayState(sprite, state) != 0)
  {
    goto common;
  }
  *((u32 *) (self + 0x14)) = (u32) gScriptedEntityStepTable;
  *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) + 1;
  stepIndex = *((s16 *) (self + 0x22));
  stepWords = (u16 *) self;
  ((u8 *) (&stepWords[stepIndex]))[0x19] = ((u8 *) (&stepWords[stepIndex]))[0x19] + 1;
  stepOffset = (*((s16 *) (self + 0x22))) * 2;
  script = self + 0x18;
  command = script[stepOffset];
  _call_via_r1(self, *((u32 *) ((*((u32 *) (self + 0x14))) + (command * 4))));
  *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) - 1;
  if (((*((u16 *) (self + 2))) & 0x8000) != 0)
  {
    goto end;
  }
  stepAnimationTrack(sprite, gfxInit);
  advanceMotion(state, 0);
  common:
  sub_0801EF8C(sprite, state);

  target = *((u8 **) (state + 0x28));
  *((u16 *) (target + 0x14)) = 0;
  cameraBase = (u8 *) (&gCameraState);
  scrollOffset = 0x1278;
  *((u32 *) (sprite + 0x14)) = (*((u32 *) (state + 8))) - (((*((u32 *) ((cameraBase + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  scrollOffset = 0x127C;
  *((u32 *) (sprite + 0x18)) = (*((u32 *) (state + 0x0C))) - (((*((u32 *) ((cameraBase + scrollOffset) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  end:
  ;

  ;
}
