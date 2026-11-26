extern void *sub_080B063C(void *, s32, s32, s32, u16, u8);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback;
void sub_080AD9AC(void *parent)
{
  int flagValue;
  u8 *spawnArray;
  u8 *obj = (u8 *) parent;
  u32 i;
  void **out;
  u32 iValue;
  void **unusedPtr;
  void *dataBlock;
  flagValue = 0x22 * 0;
  dataBlock = *((void **) (obj + 0x3C));
  spawnArray = ((u8 *) dataBlock) + 0x48;
  i = 0;
  out = (void **) spawnArray;
  ;
  do
  {
    s32 spawnKind = 2;
    iValue = i;
    if (iValue != 0)
    {
      s32 xorVal = 6 ^ iValue;
      spawnKind = ((u32) ((-xorVal) | xorVal)) >> 31;
    }
    {
      void *spawned = sub_080B063C(obj, spawnKind, *((s32 *) (obj + 0x4C)), *((s32 *) (obj + 0x5C)), (u16) (*((s32 *) (obj + 0x6C))), (u8) iValue);
      *(out++) = spawned;
      *(((u8 *) spawned) + 0x90) = 0;
    }
    i++;
  }
  while (i <= 6);
  {
    s16 targetIndex = *((s16 *) (obj + 0x22));
    s32 clearValue = flagValue;
    *((u8 *) ((obj + (targetIndex * 2)) + 0x19)) = (u8) clearValue;
  }
  {
    s32 *callbackEntry = &gMainObjTimerCallback;
    sub_080C31E4(obj + 0x18, obj + 0x22, *callbackEntry);
  }
}
