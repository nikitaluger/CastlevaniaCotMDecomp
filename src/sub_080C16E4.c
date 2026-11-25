inline u32 nextCmdWord(u8 **cursor, int index)
{
  return (u32) cursor[index];
}

/* Read the next command argument byte into the track's +0x2D field and advance
 * the command cursor. */
void sub_080C16E4(void *arg1)
{
  u8 *track;
  u8 **cursor = &track[0x40];
  u8 val = cursor[0][0];
  track[0x2D] = val;
  cursor[0] = (u8 *) (nextCmdWord(cursor, 0) + 1);
  track = (u8 *) arg1;
}
