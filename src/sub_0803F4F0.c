/* Per-frame update for one actor: mark it visible/off-screen and tick its
 * sub-state, sync animation flags, run a scripted action dispatched through
 * D_0866E080, then refresh the sprite's camera-relative screen position. */
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_08016238(void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
struct SpriteFlags { u8 flags; };
struct AnimState { u16 flags; };
void sub_0803F4F0(u8 *entity)
{
  u8 *anim;
  u8 *actor;
  u8 *actorTarget;
  u8 *child;
  u8 *frameEntry;
  u8 *patternBase;
  u8 *coordBase;
  u8 *camIndexPtr;
  u8 *coordXField;
  s32 boundsResult;
  s32 frameOffset;
  u32 coordIndex;
  u32 camX;
  u8 *screenYPos;
  u32 camY;
  u8 patternValue;
  anim = *((u8 **) (entity + 0x38));
  actor = *((u8 **) (entity + 0x3C));
  actorTarget = actor + 0x34;
  boundsResult = sub_0805F9B4(*((s32 *) (actor + 8)), *((s32 *) (actor + 0xC)));
  if (boundsResult == 1)
  {
    ((struct SpriteFlags *) (anim + 0x2A))->flags &= 0xBF;
    *((u8 *) ((*((u8 **) (actor + 0x28))) + 1)) = 0;
  }
  else
  {
    ((struct SpriteFlags *) (anim + 0x2A))->flags |= 0x40;
    *((u8 *) ((*((u8 **) (actor + 0x28))) + 1)) = 5;
  }
  sub_08016238(*((void **) (actor + 0x28)));
  if ((*((u16 *) (entity + 0x5C))) & 1)
  {
    ((struct AnimState *) actor)->flags |= 1;
  }
  if ((*((u16 *) actor)) & 1)
  {
    *((u8 *) ((*((u8 **) (actor + 0x28))) + 1)) = 0;
    child = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    if ((*((u8 *) (child + 0x1A))) != 3)
    {
      *((u8 *) (child + 0x1B)) = 0;
      {
        u32 *actionData = (u32 *) 0x08671BDC;
        sub_080C31E8(entity + 0x18, entity + 0x22, 3, *actionData);
      }
    }
  }
  if (sub_08013B5C(anim, actor) != 0)
  {
    goto table;
  }
  *((u32 *) (entity + 0x14)) = 0x0866E080;
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
  frameEntry = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
  *((u8 *) (frameEntry + 0x19)) = (*((u8 *) (frameEntry + 0x19))) + 1;
  frameOffset = (*((s16 *) (entity + 0x22))) * 2;
  patternBase = entity + 0x18;
  patternValue = *((u8 *) (((u32) patternBase) + ((u32) frameOffset)));
  sub_080C31E0((s32) entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (patternValue * 4))));
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
  if (((*((u16 *) (entity + 2))) & (0x80 << 8)) != 0)
  {
    return;
  }
  sub_080113A8(anim, actorTarget);
  sub_0801165C(actor, 0);
  table:
  coordBase = gCameraState;

  camIndexPtr = gMainWorkspace;
  camIndexPtr = camIndexPtr + 0x18A8;
  coordIndex = (((u32) (*camIndexPtr)) + 1) * 0x40;
  coordXField = coordBase + 0x1278;
  camX = *((u32 *) (coordXField + coordIndex));
  *((u32 *) (anim + 0x14)) = (*((u32 *) (actor + 8))) - ((camX + (0x80 << 8)) & 0xFFFF0000);
  coordIndex = (((u32) (*camIndexPtr)) + 1) * 0x40;
  coordBase += 0x127C;
  screenYPos = anim + 0x18;
  camY = *((u32 *) (coordBase + coordIndex));
  *((u32 *) screenYPos) = (*((u32 *) (actor + 0xC))) - ((camY + 0xFFFF8000) & 0xFFFF0000);
}
