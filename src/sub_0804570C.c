void setAnimationFrame(void *, void *, s32, s32);
s32 sub_080458CC(void *, void *);
void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptStepCallbacks;

struct WaitCtrl { u16 flags; u16 mode; u16 timer; };

/* Script step: start animation frame 5 and reset the work object's motion;
 * each tick decrements a 16-bit timer, and when it expires re-arm it for 90
 * frames if the target is still valid, otherwise clear the mode, clear the
 * step byte and advance the script. */
void sub_0804570C(void *arg0)
{
  void *sprite;
  void *work;
  void *anim;
  int zero;
  void *selfPtr;
  struct WaitCtrl *ctrl;
  s32 remaining;
  s32 *handlerPtr;
  sprite = *((void **) (((u8 *) arg0) + 0x38));
  work = *((void **) (((u8 *) arg0) + 0x3C));
  if (1)
  {
    anim = ((u8 *) work) + 0x34;
    ctrl = (struct WaitCtrl *)((u8 *)work + 0x48);
    zero = 0;
    *((u32 *) (((u8 *) work) + 0x14)) = zero;
    *((u32 *) (((u8 *) work) + 0x10)) = 0;
    setAnimationFrame(sprite, anim, 5, 0);
    remaining = ctrl->timer - 1;
  }
  ctrl->timer = remaining;
  selfPtr = arg0;
  if ((remaining << 16) < 0)
  {
    if (sub_080458CC(arg0, sprite) == 1)
    {
      ctrl->timer = 0x5A;
    }
    else
    {
      ctrl->mode = 0;
      *((u8 *) ((((u8 *) selfPtr) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
      handlerPtr = (s32 *) (&gScriptStepCallbacks);
      sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0, *handlerPtr);
    }
  }
}
