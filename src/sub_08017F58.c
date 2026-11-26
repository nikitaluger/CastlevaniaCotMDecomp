void setAnimationFrame(u32, void *, u32, u32);
void sub_08018694(void *, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
s32 sub_080C364C(s32, s32);

/* Drive a timed script step: turn the 60-frame tick counter into a phase,
 * run the phase callback to update an output value, then clear the step's
 * references and advance the script once the lifetime runs out. */
void sub_08017F58(void *arg0)
{
  u32 *phaseCallback;
  u16 zero16;
  void *sprite;
  void *scriptState;
  u8 *stateArg;
  u8 *control;
  s32 tmp;
  s32 zero;
  u32 *handlerTable;
  u8 *ctl;
  sprite = *((void **) (((u8 *) arg0) + 0x38));
 if (0) { }
  scriptState = *((void **) (((u8 *) arg0) + 0x3C));
  stateArg = ((u8 *) scriptState) + 0x34;
  control = ((u8 *) scriptState) + 0x48;
  setAnimationFrame(sprite, stateArg, 0xB, 0);
  if ((*((s16 *) (((u8 *) control) + 0x24))) > 0x3B)
  {
    *((u16 *) (((u8 *) control) + 0x24)) = 0;
  }
  phaseCallback = (u32 *) 0x08671BFC;
  *((s32 *) (((u8 *) control) + 0x20)) = sub_080C31E0(sub_080C364C(((s32) (*((s16 *) (((u8 *) control) + 0x24)))) << 16, 0x3C), *phaseCallback) * 2;
  tmp = (*((u16 *) (((u8 *) control) + 0x24))) + 1;
  zero = 0;
  *((u16 *) (((u8 *) control) + 0x24)) = tmp;
  tmp = (*((u16 *) (((u8 *) control) + 0x16))) - 1;
  zero16 = (u16) zero;
  *((u16 *) (((u8 *) control) + 0x16)) = tmp;
  ctl = control;
  if ((tmp << 16) < 0)
  {
    sub_08018694(arg0, 2);
    *((s32 *) (((u8 *) ctl) + 0x20)) = zero;
    *((u16 *) (((u8 *) ctl) + 0x24)) = zero16;
    *((u8 *) (((u8 *) ((((u32) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2) + ((u32) arg0))) + 0x19)) = 0;
    handlerTable = (u32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *handlerTable);
  }
}
