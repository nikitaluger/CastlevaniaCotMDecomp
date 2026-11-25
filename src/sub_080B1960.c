extern void sub_080986C0(void *);

/* After refreshing the input object, if its direction byte (+0x25) changed to
 * a horizontal direction, nudge the position at obj+0x0C by one unit:
 * +0x10000 for right (0 or 6), -0x10000 for left (2 or 4). */
void sub_080B1960(void *arg0, void *arg1)
{
  u8 *dirPtr;
  u8 oldDir;
  s32 dir;
  dirPtr = ((u8 *) arg1) + 0x25;
  oldDir = *dirPtr;
  sub_080986C0(arg1);
  dir = *dirPtr;
  if (oldDir == dir)
  {
    goto done;
  }
  if (dir == 2)
  {
    goto moveLeft;
  }
  if (dir <= 2)
  {
    if (dir == 0)
    {
      goto moveRight;
    }
    goto done;
  }
  if (dir == 4)
  {
    goto moveLeft;
  }
  if (dir != 6)
  {
    goto done;
  }
  moveRight:
  *((s32 *) (((u8 *) arg0) + 0x0C)) += 0x10000;

  goto done;
  moveLeft:
  *((s32 *) (((u8 *) arg0) + 0x0C)) += 0xFFFF0000;

  done:
  return;

}
