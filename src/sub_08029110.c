extern void allocWorkSlot(void *a, s32 b, s32 c, s32 d);
extern s32 sub_08005820(s32 a);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, u32 c);
extern u32 gMainObjTimerCallback;
/* First step of an entity's scripted action: allocates its 4-byte work state,
 * restarts its animation with a random delay, clears the current step byte,
 * runs the script interpreter and dispatches the handler for the new step. */
void sub_08029110(u8 *arg0)
{
  int zero;
  u8 *work;
  zero = 0;
  allocWorkSlot(arg0, zero, 4, 0);
  work = *((u8 **) (arg0 + 0x3C));
  if (work == 0)
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  {
    s32 clear = 0;
    s32 zero16 = 0;
    *((u16 *) work) = (u16) zero16;
    *((s16 *) (work + 2)) = (s16) (sub_08005820(0x8D) + 0xB4);
    *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = clear;
  }
  {
    u32 *scriptHandlers = &gMainObjTimerCallback;
    u8 *stepBase = arg0 + 0x18;
    u8 *stepIndexPtr = arg0 + 0x22;
    u32 stepHandler = *scriptHandlers;
    sub_080C31E4(stepBase, stepIndexPtr, stepHandler);
    {
      s16 stepIndex = *((s16 *) (arg0 + 0x22));
      u8 *stepByte = (u8 *)((u32)stepIndex * 2 + (u32)arg0);
      stepByte[0x19]++;
      {
        s16 stepIndex2 = *((s16 *) (arg0 + 0x22));
        u8 *step = stepBase + (stepIndex2 * 2);
        sub_080C31E0(arg0, ((void **) (*((u32 *) (arg0 + 0x14))))[step[0]]);
      }
    }
  }
}
