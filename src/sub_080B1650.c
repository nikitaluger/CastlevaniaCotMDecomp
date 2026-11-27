/* Move an actor along a scripted path: update its direction offset, play a
 * periodic sound, launch a movement step, and end the script past byte 0x80. */
extern s32 sub_0809856C(s32, s32, s32);
extern s32 startScriptOnce(void *, s32, s32);
extern s32 sub_080B1960(s32, void *);
extern s32 sub_080B30B4(s8, s32, s32);
extern s32 sub_080C31E4(void *, void *, s32);

void sub_080B1650(void *arg0)
{
  s32 work;
  unsigned int scriptState;
  u8 direction;
  void *param;
  int dispatchArg;
  work = *((s32 *) (((s8 *) arg0) + 0x3C));
  param = *((void **) (((s8 *) arg0) + 0x4C));
  sub_080B1960(work, param);
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))) > 0x10U)
  {
    sub_0809856C(0x181, work + 0x60, 7);
    scriptState = *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19));
    if (!(1 & scriptState))
    {
      if (2 & scriptState)
      {
        sub_080B30B4((s8) (*((u8 *) (((s8 *) param) + 0x35))), 0, work);
      }
      else
      {
        sub_080B30B4((s8) (*((u8 *) (((s8 *) param) + 0x35))), 1, work);
      }
    }
  }
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))) > 0x80U)
  {
    direction = *((u8 *) (((s8 *) param) + 0x25));
    if (direction == 0)
    {
      startScriptOnce(param, 1, 1);
      *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = direction;
      dispatchArg = 0x08671BB0;
      sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) dispatchArg));
    }
  }
}
