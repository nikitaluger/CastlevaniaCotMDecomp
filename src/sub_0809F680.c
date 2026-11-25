void sub_080A0244(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Clear the work state at +0x92 and set the +0x6C flag on each of the six
 * sub-objects listed there, then reset the script step and advance. */
void sub_0809F680(u8 *arg0)
{
  u8 *work = *((u8 **) (arg0 + 0x3C));
  s32 *subObjects = (s32 *) (0x48 + work);
  u32 i;
  void *stepPtr;
  void *scriptPtr;
  if ((*((u8 *) (arg0 + 0x6C))) != 0)
  {
    *((u16 *) (work + 0x92)) = 0;
    i = 0;
    scriptPtr = arg0 + 0x18;
    stepPtr = arg0 + 0x22;
    {
      s32 *p = subObjects;
      do
      {
        sub_080A0244(*(p++), 1);
        i++;
      }
      while (i <= 5);
    }
    *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
    {
      s32 *resultTable = (s32 *) 0x08671BB0;
      sub_080C31E4(scriptPtr, stepPtr, *resultTable);
    }
  }
}
