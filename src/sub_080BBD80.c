void sub_08000E98(s32, s32, s32, s32, s32);
extern s32 D_08670690[];
extern u8 D_0600BF80[];
inline s32 poseEntry(s32 *table, s32 pose, s32 facing)
{
  return table[pose + (facing * 3)];
}

/* Upload the tile graphics for the current pose: look the entry up by pose and
 * facing direction and DMA-copy it into VRAM at 0x0600BF80. */
void sub_080BBD80(void *arg0)
{
  u8 *self = (u8 *) arg0;
  void *owner = *((void **) (self + 0x28));
  u8 *animState = *((u8 **) (((u8 *) owner) + 0x4C));
  s32 pose = *((s32 *) (self + 0x5C));
  if (pose != 0)
  {
    s32 notFacing = ~((s32) ((s8) (*((vu8 *) (animState + 0x35)))));
    short facing = ((u32) (notFacing | (-notFacing))) >> 31;
 do { } while (0);
    sub_08000E98(1, poseEntry(D_08670690, pose, facing), (s32) D_0600BF80, 0x80, 0x10);
  }
}
