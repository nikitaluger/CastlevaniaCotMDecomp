void sub_08011368(void *, void *, s32, s32);
s32 sub_08012A94(void *, s32, s32);
void *sub_0801C9A0(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Spawn two result objects at mirrored X offsets from the script state, reset
 * the current script step's counter and call the step-advance handler. */
void sub_0801B354(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  void *sprite = *((void **) (obj + 0x38));
  void *scriptState = *((void **) (obj + 0x3C));
  u32 coord;
  s32 offset;
  s32 resultCoord;
  u32 *handler;
  sub_08011368(sprite, ((u8 *) scriptState) + 0x34, 5, 0);
  coord = (*((s32 *) (scriptState + 0x08))) + 0x110000;
  offset = sub_08012A94((void *) coord, *((s32 *) (scriptState + 0x0C)), 0x11);
  if (offset <= 0x7FFFFF)
  {
    resultCoord = (*((s32 *) (scriptState + 0x0C))) + offset;
    sub_0801C9A0((s32) coord, resultCoord);
  }
  coord = (*((s32 *) (scriptState + 0x08))) + 0xFFEF0000;
  offset = sub_08012A94((void *) coord, *((s32 *) (scriptState + 0x0C)), 0x11);
  if (offset <= 0x7FFFFF)
  {
    resultCoord = (*((s32 *) (scriptState + 0x0C))) + offset;
    sub_0801C9A0((s32) coord, resultCoord);
  }
  {
    u8 *stepCounter;
    s32 stepOffset;
    stepOffset = *(s16 *)(obj + 0x22) * 2;
    stepCounter = (u8 *)((u32)stepOffset + (u32)obj);
    *(u8 *)(stepCounter + 0x19) = 0;
  }
  handler = (u32 *) 0x08671BB0;
  sub_080C31E4(obj + 0x18, obj + 0x22, *handler);
}
