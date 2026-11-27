s32 advanceAnimTrackByDelta(s32, void *, s32);
s32 sub_080A2E30(s32);
s32 sub_080A2E84(s32, s32);
extern s32 D_0866FDEC[];
extern s32 D_0866FDF4[];
inline u8 *bytePtr(void *arg0)
{
  return (u8 *) arg0;
}

/* Advances a movement track's animation frame using the facing state's table
 * index, reads the direction id stored in the track's current frame entry, and
 * when that differs from the facing state's previous direction (in particular
 * when leaving the special stop direction 0x24) tells the two linked objects to
 * restart their animation. Returns flag bit 1 of the track. */
u8 sub_080A1904(s32 entity, void *trackArg, void *facingArg)
{
  u8 *track = (u8 *) trackArg;
  u8 *facing = bytePtr(facingArg);
  void *frameData;
  s16 frameIndex;
  u8 *tableIndexPtr;
  u8 indexOffset;
  s32 dirIndex;
  u8 *frameBase;
  u8 *entry;
  u32 direction;
  u16 prevDirection;
  tableIndexPtr = bytePtr(facing + 0x16);
  advanceAnimTrackByDelta(entity, trackArg, D_0866FDEC[*tableIndexPtr]);
  frameData = *((void **) (track + 8));
  frameIndex = *((s16 *) (track + 0x0E));
  indexOffset = *bytePtr(track + 1);
  dirIndex = frameIndex + indexOffset;
  frameBase = *((u8 **) frameData);
  entry = bytePtr((dirIndex * 4) + frameBase) - 4;
  direction = *((u16 *) (entry + 2));
  prevDirection = *((u16 *) (facing + 0x14));
  if (direction != prevDirection)
  {
    if (prevDirection == 0x24)
    {
      sub_080A2E30(*((s32 *) (facing + 8)));
      sub_080A2E84(*((s32 *) (facing + 0x10)), D_0866FDF4[*bytePtr(facing + 0x16)]);
    }
    *((u16 *) (facing + 0x14)) = direction;
  }
  facing = track;
  return (*bytePtr(facing + 0)) & 2;
}
