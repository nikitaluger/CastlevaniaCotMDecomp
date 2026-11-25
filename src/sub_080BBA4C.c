extern void sub_080BE568(s32, s32, s32);
/* Positions the two attached parts of a multi-part actor: picks 16.16 offsets
 * from the actor's movement mode and facing byte, then writes each part's
 * target position with sub_080BE568 (skipping part 1 while mode is 4). */
void sub_080BBA4C(void *arg0)
{
  s32 offsetsX[2];
  u32 *yPtr;
  u32 i;
  u8 *dirPtr;
  u32 mode;
  u32 baseY2;
  s32 offsetsY[2];
  void *actor = arg0;
  u8 *work = *((u8 **) (((u8 *) actor) + 0x3C));
  u8 *parts = work + 0x48;
  actor = *((u8 **) (((u8 *) actor) + 0x4C));
  mode = *((u32 *) (parts + 0x44));
  if (mode == 2)
  {
    goto case2;
  }
  if (mode > 2)
  {
    goto check3;
  }
  if (mode == 1)
  {
    goto case1;
  }
  goto default_case;
  check3:
  if (mode == 3)
  {
    goto case3;
  }

  goto default_case;
  case1:
  dirPtr = actor;

  dirPtr += 0x35;
  offsetsX[0] = (*((s8 *) dirPtr)) * 0x340000;
  offsetsY[0] = 0xFFE90000;
  offsetsX[1] = (*((s8 *) dirPtr)) << 16;
  baseY2 = 0xFFEC0000;
  goto store_sp3;
  case2:
  dirPtr = actor;

  dirPtr += 0x35;
  offsetsX[0] = *((s8 *) dirPtr);
  offsetsX[0] = offsetsX[0] * 0x1D0000;
  offsetsY[0] = 0xFFE80000;
  offsetsX[1] = -((*((s8 *) dirPtr)) << 16);
  baseY2 = 0xFFE60000;
  goto store_sp3;
  case3:
  dirPtr = actor;

  dirPtr += 0x35;
  offsetsX[0] = (*((s8 *) dirPtr)) * 0x350000;
  offsetsY[0] = 0x230000;
  offsetsX[1] = -((*((s8 *) dirPtr)) * 0x180000);
  baseY2 = 0x240000;
  store_sp3:
  offsetsY[1] = baseY2;

  goto loop_start;
  default_case:
  actor = ((u8 *) actor) + 0x35;

  offsetsX[0] = (((s32) (((u32) (*((u8 *) actor))) << 24)) >> 24) << 20;
  offsetsY[0] = 0xFFF10000;
  loop_start:
  i = 0;

  yPtr = offsetsY;
  do
  {
    s32 targetX = (*((s32 *) (work + 0x08))) + offsetsX[i];
    s32 targetY = (*((s32 *) (work + 0x0C))) + yPtr[0];
    if ((i != 1) || ((*((u32 *) (parts + 0x44))) != 4))
    {
      u32 off;
      s32 part;
      off = (u32) (((u8 *) parts) + 0x24);
      off += i << 2;
      part = *((s32 *) off);
      sub_080BE568(part, targetX, targetY);
    }
    yPtr++;
    i++;
  }
  while (i <= 1);
}
