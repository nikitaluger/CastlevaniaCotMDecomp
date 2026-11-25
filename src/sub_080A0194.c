/*
 * Positions a spawned effect from its source position: mirrors it 16 px left or
 * right depending on the actor's facing flag (bit 0x10), and raises it 36 px
 * plus the caller's y offset.
 */
void sub_080A0194(void *effect, void *actor, void *pos, s32 yOffset)
{
  if (effect != NULL)
  {
    s32 dir;
    s32 yBias;
    dir = ((*((u16 *) (((u8 *) actor) + 2))) & 0x10) ? (1) : (-1);
    *((s32 *) (((u8 *) effect) + 0x6C)) = dir;
    *((s32 *) (((u8 *) effect) + 0x4C)) = (*((s32 *) (((u8 *) pos) + 8))) + (dir << 0x14);
    yBias = 0xFFDC0000;
    *((s32 *) (((u8 *) effect) + 0x5C)) = (*((s32 *) (((u8 *) pos) + 0xC))) + (yOffset + yBias);
  }
}
