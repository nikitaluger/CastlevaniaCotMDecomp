extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(u8 *, u32);
extern s32 sub_08014A04(u8 *, s32, s32, s32, s32);
extern s32 sub_08014A6C(u8 *, u32, s32, s32);
extern void sub_08014B1C(u8 *, u8 *, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(u8 *, u8 *, s32, u32);
extern s32 divInt32(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Sub-state byte at entity + index*2 + 0x19. */
struct WaypointState { u8 _0[0x19]; u8 state; };

/* Walks an entity toward a route waypoint: refreshes its animation, steers
 * it, and signals completion through a callback once it arrives. */
void sub_08020944(u8 *entity)
{
  u8 *sprite;
  u8 *motion;
  u8 *animState;
  u8 *steer;
  u8 *coordBase;
  u8 **coordEntryRef;
  u8 *indexPtr;
  u8 *coordEntry;
  u32 routeIndex;
  u32 coordOffset;
  u32 coordX;
  u32 coordY;
  s32 targetX;
  s32 targetY;
  s32 angleDiff;
  sprite = *((u8 **) (entity + 0x38));
  motion = *((u8 **) (entity + 0x3C));
  animState = motion + 0x34;
  steer = motion + 0x48;
  setAnimationFrame(sprite, animState, 0, 1);
  coordBase = gCameraState;
  indexPtr = gMainWorkspace;
  indexPtr += 0x18A8;
  routeIndex = *indexPtr;
  coordEntryRef = &coordEntry;
  coordOffset = (routeIndex + 1) * 0x40;
  coordEntry = coordBase + 0x1278;
  coordX = *((u32 *) ((*coordEntryRef) + coordOffset));
  targetX = coordX + (0xF1 << 15);
  coordEntry = coordBase + 0x127C;
  coordY = *((u32 *) (coordOffset + (*coordEntryRef)));
  targetY = coordY + (0x9E << 14);
  if (sub_08014A04(motion, targetX, targetY, 0x80 << 13, 0x80 << 13) == 1)
  {
    angleDiff = *((s16 *) (steer + 0xA));
    if (angleDiff == 1)
    {
      *((u16 *) (steer + 0xC)) = angleDiff;
    }
  }
  if (((*((u8 *) (animState + 1))) == 1) && ((*((u32 *) (animState + 4))) == 1))
  {
    *((u16 *) (steer + 4)) = 0;
  }
  {
    u32 *trigFuncs = (u32 *) 0x08671BFC;
    *((u32 *) (steer + 0)) = sub_080C31E0(divInt32(((u32) (*((s16 *) (steer + 4)))) << 16, 0x24), *trigFuncs) << 1;
  }
  *((u16 *) (steer + 4)) = (*((u16 *) (steer + 4))) + 1;
  if ((*((s16 *) (steer + 0xC))) == 1)
  {
    if (sub_08014A6C(motion, *((u32 *) (steer + 0x28)), 0x80 << 6, 0) == 1)
    {
      u8 *stateBytePtr;
      stateBytePtr = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
      *((u8 *) (stateBytePtr + 0x19)) = 0;
      {
        u32 *callbacks = (u32 *) 0x08671BD0;
        sub_080C31E8(entity + 0x18, entity + 0x22, 2, *callbacks);
      }
    }
  }
  else
  {
    sub_08014B1C(motion, steer + 0x24, targetX, targetY);
    setSpriteFlip(sprite, *((u32 *) (steer + 0x28)));
  }
}
