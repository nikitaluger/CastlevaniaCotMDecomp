extern void *gMainObjTimerCallback;
s32 sub_0800583C(void);
void sub_080B089C(s32, s32);
void divideInt(s32, s16);
void sub_080C31E4(void *, void *, void *);

/* Updates an effect entity: clears a sprite flag, runs two countdowns, spawns a
 * child at a jittered position, writes hardware registers, and advances the
 * script step when the repeat counter expires. */
void sub_080ABA48(void *arg0)
{
  u8 *entity = (u8 *) arg0;
  u8 *sprite = *((u8 **) (entity + 0x38));
  int stepAmount;
  u8 *state = *((u8 **) (entity + 0x3C));
  s16 step = *((s16 *) (entity + 0x22));
  if (!((*((u8 *) ((entity + (step * 2)) + 0x19))) & 2))
  {
    *((u16 *) (sprite + 0)) = ((*((u16 *) (sprite + 0))) & 0x0FFF) | 0xE000;
  }
  {
    u8 *repeatCounter;
    u8 *cycleCounter = state + 0x94;
    s32 count = *((u8 *) cycleCounter);
    s32 wrapCheck;
    count--;
    *((u8 *) cycleCounter) = count;
    wrapCheck = (count << 1) << 23;
    repeatCounter = state + 0x95;
    if (wrapCheck == 0)
    {
      *((u8 *) cycleCounter) = 8;
      *((u8 *) repeatCounter) = (*((u8 *) repeatCounter)) - 1;
    }
    *((u16 *) (sprite + 6)) = (*((u16 *) (sprite + 6))) - 1;
    stepAmount = 6;
    *((u16 *) (sprite + 4)) = (*((u16 *) (sprite + 4))) + stepAmount;
    divideInt(0x18000000, *((s16 *) (sprite + 4)));
    step = 0;
    sub_080B089C((*((s32 *) (state + 8))) + sub_0800583C(), 0x00880000);
    if ((*((u8 *) repeatCounter)) == step)
    {
      *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = step;
      {
        void **eventPtr = &gMainObjTimerCallback;
        sub_080C31E4(entity + 0x18, entity + 0x22, *eventPtr);
      }
    }
    {
      u16 *hardware = (u16 *) 0x03000830;
      u8 repeat;
      hardware[2] = 0xFD << stepAmount;
      repeat = *((u8 *) repeatCounter);
      hardware[3] = repeat | ((0x10 - repeat) << 8);
    }
  }
}
