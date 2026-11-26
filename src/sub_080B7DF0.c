/* Plays the cast sound and spawns three offset effects at counter 8, then
   resets the counter and dispatches the next behavior at counter 0x14. */
extern void sub_08005E80(s32);
extern void sub_080B9834(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback;

void sub_080B7DF0(void *arg0)
{
  s32 spawnY;
  s32 spawnX;
  s32 dir;
  s32 *callbackPtr;
  void *gfx;
  unsigned int zeroU;
  void *work;

  gfx = *((void **)((u8 *)arg0 + 0x38));
  zeroU = 0U;
  work = *((void **)((u8 *)arg0 + 0x3C));
  if ((*((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19))) == 8)
  {
    s32 facingRight;
    sub_08005E80(0x182);
    facingRight = (*(u16 *)((u8 *)gfx + 2)) & 0x10;
    dir = -1;
    if (facingRight)
    {
      dir = 1;
    }
    spawnX = (*((s32 *)((u8 *)work + 8))) - (dir << 0x14);
    spawnY = (*((s32 *)((u8 *)work + 0xC))) + 0xFFE80000;
    sub_080B9834(0, 0, spawnX, spawnY, dir);
    sub_080B9834(0, 1, spawnX, spawnY, dir);
    sub_080B9834(0, 2, spawnX, spawnY, dir);
  }
  if (*(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) == 0x14)
  {
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zeroU;
    callbackPtr = &gMainObjTimerCallback;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callbackPtr);
  }
}
