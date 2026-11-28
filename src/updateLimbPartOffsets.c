extern s32 sub_080C31E0(u32, u32);
extern u32 gTrigFuncTable;

/* Recompute each limb's X offsets from its angle via the trig table, then copy
 * both offset triples and the angle into the two outer render parts. */
void updateLimbPartOffsets(struct LimbTransform *transform)
{
  u32 side = 0;
  u32 part;
  s32 zero;
  u32 *angles = transform->angles;
  for (; side <= 1; side++)
  {
    u32 angle = transform->angles[side];
    s32 adjusted = ((s32) angle) - 0x200;
    zero = 0;
    if (transform->limbs[side].parts[0]->sign > zero)
    {
      do
      {
        transform->offsetA[side].axis[0] = transform->offsetA[side].axis[2] + ((sub_080C31E0(angle + 0x3E00, gTrigFuncTable) >> 8) << 13);
      }
      while (0);
    }
    else
    {
      transform->offsetA[side].axis[0] = transform->offsetA[side].axis[2] - ((sub_080C31E0(angle + 0x3E00, gTrigFuncTable) >> 8) << 13);
    }
    transform->offsetB[side].axis[0] = transform->offsetB[side].axis[2] + ((sub_080C31E0(adjusted, gTrigFuncTable) >> 8) << 13);
  }

  for (side = 0; side <= 1; side++)
  {
    u32 *anglePtr = angles;
    for (part = 0; part <= 2; part++)
    {
      if (part != 1)
      {
        transform->limbs[side].parts[part]->offsetA = transform->offsetA[side].axis[part];
        transform->limbs[side].parts[part]->offsetB = transform->offsetB[side].axis[part];
        transform->limbs[side].parts[part]->angle = *(u32 *)((u32)anglePtr + (side << 2));
      }
    }
  }
}
