extern s32 sub_080A845C(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gTrigFuncPtr;
extern u32 gMenuScriptCallback;

/* Decay a state counter and scale two trig lookups by it to set the state's
 * motion components; when the counter reaches zero, advance the script step. */
void sub_080A66C0(u8 *self)
{
  u8 *state;
  u8 *work;
  u8 *counter;
  u8 *anglePtr;
  u32 *trigFunc;
  u32 *cmdParam;
  s32 count;
  state = *((u8 **) (self + 0x3C));
  work = state + 0x48;
  counter = work + 0xEC;
  if ((--(*((s32 *) counter))) < 0)
  {
    *((s32 *) counter) = 0;
  }
  trigFunc = &gTrigFuncPtr;
  anglePtr = state + 0x130;
  *((s32 *) (state + 0xFC)) = (sub_080C31E0((*((s32 *) (state + 0x130))) + 0x4000, *trigFunc) * (*((s32 *) counter))) >> 7;
  *((s32 *) (state + 0x100)) = (sub_080C31E0(*((s32 *) anglePtr), *trigFunc) * (*((s32 *) counter))) >> 7;
  sub_080A845C(self, work);
  count = *((s32 *) counter);
  if (count == 0)
  {
    s16 scriptIdx = *((s16 *) (self + 0x22));
    *((u8 *) ((self + (scriptIdx * 2)) + 0x17)) = count;
    cmdParam = &gMenuScriptCallback;
    sub_080C31E8(self + 0x18, self + 0x22, 0, *cmdParam);
  }
}
