/* identical to sub_0801B42C (matched), with its names changed by decompdecomp */
extern s32 sub_0800583C(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_08012A94(s32, s32, s32);
extern void ResultObj_New(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080C36E4(s16, s32);
/* On a periodic trigger, spawn two result objects at mirrored offsets; advance
 * the step counters and end the script step once the repeat limit is passed. */
void sub_08017C88(u8 *obj)
{
  s32 sprite;
  u8 *scriptState;
  s32 *limitPtr;
  u8 *stateArg;
  u8 *control;
  s32 range;
  s32 maxOffset;
  s32 offset;
  s32 coord;
  s32 resultCoord;
  u8 *stepCounterPtr;
  s32 *handlerTable;
  sprite = *((s32 *) (obj + 0x38));
  scriptState = *((u8 **) (obj + 0x3C));
  stateArg = scriptState + 0x34;
  control = scriptState + 0x48;
  setAnimationFrame(sprite, stateArg, 9, 0);
  limitPtr = &maxOffset;
  if ((sub_080C36E4(*((s16 *) (control + 0x16)), 3) << 16) == 0)
  {
    range = 0x10000;
    coord = ((*((s32 *) (scriptState + 8))) + (((*((s16 *) (control + 0x18))) + 1) * 0x110000)) + (sub_0800583C(range) * 3);
    offset = sub_08012A94(coord, *((s32 *) (scriptState + 0xC)), 0x11);
    maxOffset = 0x7FFFFF;
    if (offset <= maxOffset)
    {
      resultCoord = (*((s32 *) (scriptState + 0xC))) + offset;
      ResultObj_New(coord, resultCoord);
    }
    coord = ((*((s32 *) (scriptState + 8))) - (((*((s16 *) (control + 0x18))) + 1) * 0x110000)) + (sub_0800583C(range) * 3);
    offset = sub_08012A94(coord, *((s32 *) (scriptState + 0xC)), 0x11);
    if (offset <= (*limitPtr))
    {
      resultCoord = (*((s32 *) (scriptState + 0xC))) + offset;
      ResultObj_New(coord, resultCoord);
    }
    *((u16 *) (control + 0x18)) = (*((u16 *) (control + 0x18))) + 1;
  }
  *((u16 *) (control + 0x16)) = (*((u16 *) (control + 0x16))) + 1;
  if ((*((s16 *) (control + 0x18))) > 9)
  {
    stepCounterPtr = (u8 *) ((((u32) (*((s16 *) (obj + 0x22)))) * 2) + ((u32) obj));
    *((u8 *) (stepCounterPtr + 0x19)) = 0;
    handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *handlerTable);
  }
}
