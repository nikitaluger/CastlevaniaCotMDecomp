extern s32 sub_08005910(s32, s32);
extern void sub_08005E80(s32);
extern void sub_0808DC88(s32, s32, s32);
extern void sub_080A8B44(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
inline char *inline_fn(void *arg0) { return (char *) arg0; }

/*
 * Handles two sub-states of a scripted attack: sub-state 3/6 toggle the
 * actor's state byte and fire an aimed effect, while sub-state 0x14 advances
 * a counter on the actor's state data and dispatches the end callback.
 */
void sub_080A7834(void *arg0)
{
  s32 stepOffset;
  void *actor;
  char *counterPtr;
  u8 newCount;
  void **actorSlot;
  void *stateData;
  s32 *endCallbacks;
  s32 *angleTable;
  u8 subState;
  s32 angleOffset;
  s32 angle;
  s32 targetX;
  s32 aimAngle;

  actorSlot = (void **) (inline_fn(arg0) + 0x3C);
  actor = *actorSlot;
  stateData = inline_fn(actor) + 0x48;
  subState = *(((u8 *) ((((s16) (*((s16 *) (inline_fn(arg0) + 0x22)))) * 2) + ((u32) arg0))) + 0x19);
  if (subState == 3)
  {
    *((u8 *) (inline_fn(actor) + 0xEE)) = 1;
  }
  else
  {
    angle = aimAngle;
    if (subState == 6)
    {
      *((u8 *) (inline_fn(actor) + 0xEE)) = 0;
      aimAngle = (*((s32 *) (inline_fn(actor) + 0xE8))) + sub_08005910((*((s32 *) (inline_fn(actor) + 0xDC))) - (*((s32 *) (inline_fn(actor) + 0xC8))), (*((s32 *) (inline_fn(actor) + 0xD8))) - (*((s32 *) (inline_fn(stateData) + 0x7C))));
      angleTable = (s32 *) 0x08671BFC;
      angle = aimAngle;
      targetX = (*((s32 *) (inline_fn(actor) + 0x08))) + (angleOffset = (sub_080C31E0(angle + 0x4000, *angleTable) >> 8) * 0x2C00);
      angle = (*((s32 *) (inline_fn(actor) + 0x0C))) + ((sub_080C31E0(angle, *angleTable) >> 8) * 0x2C00);
      sub_0808DC88(targetX, angle, 8);
      sub_0808DC88(targetX, angle, 0x18);
      sub_080A8B44(arg0, actor);
      sub_08005E80(0x179);
    }
  }
  stepOffset = ((s16) (*((s16 *) (inline_fn(arg0) + 0x22)))) * 2;
  subState = *(((u8 *) (stepOffset + ((u32) arg0))) + 0x19);
  if (subState == 0x14)
  {
    counterPtr = inline_fn(stateData) + 0x100;
    newCount = (*((u8 *) counterPtr)) + 1;
    stepOffset = 0;
    *((u8 *) (inline_fn(stateData) + 0x100)) = newCount;
    *(((u8 *) ((((s16) (*((s16 *) (inline_fn(arg0) + 0x22)))) * 2) + ((u32) arg0))) + 0x19) = stepOffset;
    endCallbacks = (s32 *) 0x08671BB0;
    sub_080C31E4(inline_fn(arg0) + 0x18, inline_fn(arg0) + 0x22, *endCallbacks);
  }
}
