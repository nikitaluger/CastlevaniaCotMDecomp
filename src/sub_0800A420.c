/*
 * Actor countdown script step: publish the work's countdown byte (and its
 * complement) to the timer display register; when it reaches zero, blank the
 * display, advance the script and switch state, otherwise decrement it.
 */
struct S_03000830
{
  u8 _[4];
  u16 f04;  /* display word, 0 when the countdown is finished */
  u16 f06;  /* packed countdown value */
};
s32 sub_080C31E0(void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

#define IDLE_DISPLAY  0x3F52
#define COUNT_START   0x10
#define NEXT_ARG      5

void sub_0800A420(void *arg0)
{
  void *work = *((void **) (((u8 *) arg0) + 0x3C));
  struct S_03000830 *timerDisplay = (struct S_03000830 *) 0x03000830;
  u8 countdown;
  short countdownReload;
  u16 idleValue = IDLE_DISPLAY;
  timerDisplay->f04 = idleValue;
  countdown = *((u8 *) (((u8 *) work) + 0x637));
  timerDisplay->f06 = countdown | ((COUNT_START - countdown) << 8);
  countdownReload = *((volatile u8 *) (((u8 *) work) + 0x637));
  {
    short countdownNow = countdownReload;
    if (countdownNow == 0)
    {
      timerDisplay->f04 = countdownNow;
      *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
      {
        s32 *nextScriptTable = (s32 *) 0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, NEXT_ARG, *nextScriptTable);
      }
      {
        u8 *scriptBytePtr = (u8 *) ((((u32) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2) + ((u32) arg0));
        scriptBytePtr[0x19] = (u8) (scriptBytePtr[0x19] + 1);
      }
      {
        s32 scriptIndex = (*((s16 *) (((u8 *) arg0) + 0x22))) * 2;
        u8 *scriptBase = ((u8 *) arg0) + 0x18;
        u8 scriptByte = *(scriptBase + scriptIndex);
        u8 **stateTable = *((u8 **) (((u8 *) arg0) + 0x14));
        sub_080C31E0(arg0, (s32) stateTable[scriptByte]);
      }
    }
    else
    {
      *((u8 *) (((u8 *) work) + 0x637)) = (u8) (countdownReload - 1);
    }
  }
}
