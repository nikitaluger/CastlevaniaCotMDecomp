extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct R { u8 pad[0xE]; u16 timer; u16 phase; };

/* Decrement the control timer; once it expires, reset it, set the phase to 3,
 * clear the current step and advance the command stream. */
void sub_0803EFBC(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  s32 gfx = *((s32 *) (obj + 0x38));
  u8 *state = *((u8 **) (obj + 0x3C));
  u8 *anim = state + 0x34;
  struct R *control = (struct R *)(state + 0x48);
  s32 *stepHandler;
  long long countdown;
  setAnimationFrame(gfx, anim, 0x0B, 0);
  countdown = control->timer - 1;
  control->timer = countdown;
  if (((s16) countdown) < 0)
  {
    control->timer = 0;
    control->phase = 3;
    *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
    stepHandler = (s32 *) 0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *stepHandler);
  }
}
