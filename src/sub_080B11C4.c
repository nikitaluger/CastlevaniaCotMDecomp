extern void startScriptOnce(s32, s32, s32);
extern void sub_080B3148(void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;
struct S_02025FF0_b11c4
{
  u8 _0[0x1750];
  s32 playerY;
};
extern struct S_02025FF0_b11c4 gMainWorkspace;

/* AI script step: at flag 0xF request state 2 on the target object; at flag 0x1E
 * spawn effect 0x1BB, stop motion, aim the heading toward the player's side, then
 * clear the flag and advance the script. */
void sub_080B11C4(void *entity)
{
  u8 *self;
  u8 *work;
  s32 target;
  self = (u8 *) entity;
  work = *((u8 **) (self + 0x3C));
  target = *((s32 *) (self + 0x4C));
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 0xF)
  {
    startScriptOnce(target, 2, 0);
  }
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 0x1E)
  {
    s32 yThreshold;
    sub_080B3148(self);
    *((s32 *) (work + 0x10)) = 0;
    yThreshold = *((s32 *) (work + 0x0C));
    yThreshold = yThreshold + 0x2C0000;
    if (gMainWorkspace.playerY > ((*((s32 *) (work + 0x0C))) + 0x2C0000))
    {
      *((s32 *) (work + 0x14)) = 0x8000;
    }
    else
    {
      *((s32 *) (work + 0x14)) = (s32) 0xFFFF8000;
    }
    *((s8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    {
      void **scriptTable = &gMainObjTimerCallbacks;
      sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
  }
}
