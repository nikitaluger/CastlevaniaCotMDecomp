extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct Control { u8 pad[0xE]; u16 timer; };

/* Play animation 11 on the parent; count the control timer down and, when it
 * expires, reload it with 30 frames, clear the current script byte and advance
 * the command stream. */
void sub_0803F120(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  s32 gfx = *((s32 *) (obj + 0x38));
  u8 *state = *((u8 **) (obj + 0x3C));
  u8 *anim = state + 0x34;
  struct Control *control = (struct Control *)(state + 0x48);
  s32 *stepHandler;
  long long countdown;
  setAnimationFrame(gfx, anim, 0x0B, 0);
  countdown = control->timer - 1;
  control->timer = countdown;
  if (((s16) countdown) < 0)
  {
    control->timer = 0x1E;
    *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
    stepHandler = (s32 *) 0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *stepHandler);
  }
}
