inline s32 *wordPtr(u8 *arg0)
{
  return (s32 *) arg0;
}

/* Decelerates the target's horizontal velocity by 0x100 per frame, clamping at
 * zero. If the entity's sprite flip bit (attribute bit 4) changed, the velocity
 * is reversed first and the cached flip bit is updated. Returns 1 while the
 * target is still moving, 0 once it has stopped. */
s32 decelerateTargetX(u8 *entity, u8 *target)
{
  u16 *flipState;
  s32 velocity;
  s32 nextVelocity;
  flipState = (u16 *) (target + 0xA4);
  ;
  if ((*flipState) != ((*((u16 *) (entity + 2))) & 0x10))
  {
    *((s32 *) (target + 0xA0)) = -(*((s32 *) (target + 0xA0)));
    *flipState = (*((u16 *) (entity + 2))) & 0x10;
  }
  velocity = *((s32 *) (target + 0xA0));
  if (velocity == 0)
  {
    return 0;
  }
  if (velocity > 0)
  {
    nextVelocity = velocity - 256;
    *((s32 *) (target + 0xA0)) = nextVelocity;
    if (nextVelocity < 0)
    {
      *((s32 *) (target + 0xA0)) = 0;
      return 0;
    }
  }
  else
  {
    *wordPtr(target + 0xA0) = (nextVelocity = velocity + 256);
    if (nextVelocity > 0)
    {
      *((s32 *) (target + 0xA0)) = 0;
      return 0;
    }
  }
  return 1;
}
