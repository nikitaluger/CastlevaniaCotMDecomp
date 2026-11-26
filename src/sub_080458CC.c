s32 signOf(s32);
s32 sub_08014990(void *);
extern u8 gMainWorkspace[];
extern u8 D_080CF5AC[];
/* Targeting test: returns 1 when `target` faces the same way as the player
 * relative to this entity (bit 0x10), its flag bit matches, it lies within the
 * Y/X distance window, and the global state byte is one of the two IDs listed
 * in D_080CF5AC; otherwise 0. */
s32 sub_080458CC(void *entity, void *target)
{
  void *motion;
  s32 facingSign;
  u16 flagMask;
  s32 delta;
  s32 absDelta;
  u8 stateByte;
  s32 i;
  u32 globals;
  motion = *((void **) (((u8 *) entity) + 0x3C));
  facingSign = sub_08014990(target);
  if (facingSign != signOf(*((s32 *) (((u8 *) motion) + 8))))
  {
    return 0;
  }
  flagMask = (*((u16 *) (((u8 *) target) + 2))) & 0x10;
  globals = (u32) gMainWorkspace;
  if (flagMask != ((*((u16 *) ((*((s32 *) (globals + 0x171C))) + 2))) & 0x10))
  {
    return 0;
  }
  delta = (*((s32 *) (((u8 *) motion) + 0x0C))) - (*((s32 *) (globals + 0x172C)));
  absDelta = delta;
  if (delta < 0)
  {
    absDelta = -delta;
  }
  if (absDelta > 0x7FFFF)
  {
    return 0;
  }
  delta = (*((s32 *) (((u8 *) motion) + 8))) - (*((s32 *) (globals + 0x1728)));
  if (delta < 0)
  {
    delta = -delta;
  }
  if (delta > 0x4FFFFF)
  {
    return 0;
  }
  i = 0;
  ;
  for (; i <= 1; i++)
  {
    if ((*((u8 *) (globals + 0x173A))) == D_080CF5AC[i])
    {
      return 1;
    }
  }

  return 0;
}
