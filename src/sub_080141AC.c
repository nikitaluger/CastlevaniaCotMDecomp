s32 sub_0805F9B4(s32, s32);

/* Movement bounds check: when the destination lies outside the camera view,
 * drop the entity's on-screen flag and stop the mover; report whether none of
 * the blocking bits (0xD) are set. While inside the view, keep the flag. */
s32 sub_080141AC(void *arg0, void *arg1)
{
  void *mover;
  u8 *viewFlags;
  unsigned short newFlags;
  s32 outside;
  outside = sub_0805F9B4(*((u32 *) (((u8 *) arg1) + 8)), *((u32 *) (((u8 *) arg1) + 0xC)));
  if (outside == 1)
  {
    viewFlags = ((u8 *) arg0) + 0x2A;
    *viewFlags = 0xBF & (*viewFlags);
    mover = *((void **) (((u8 *) arg1) + 0x28));
    if (mover != NULL)
    {
      *((u8 *) (((u8 *) mover) + 1)) = 0;
    }
    if (!(0xD & (*((u16 *) arg1))))
    {
      return 1;
    }
    return 0;
  }
  viewFlags = ((u8 *) arg0) + 0x2A;
  *viewFlags = (newFlags = 0x40 | (*viewFlags));
  return 0;
}
