s32 sub_080141AC(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_08014328(void *, void *, void *);
void sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, s32, u32);
extern u8 D_0866E610[];
extern u32 D_08671BDC[];

/* Holds the currently selected target object at offset 0x1870. */
struct S_02025FF0
{
  u8 _0x000[0x1870];
  void *currentTarget;
};
extern struct S_02025FF0 D_02025FF0;

/*
 * Runs one frame of a scripted task that tracks a target: handles a hit,
 * clears the step flag once the target is selected, advances to the next
 * handler from D_0866E610, and copies the target's position/orientation onto
 * the subject and actor.
 */
void sub_080512FC(u8 *task)
{
  u8 *actor;
  u8 *subject;
  u8 *stepState;
  u8 *stateEntry;
  s32 stepOffset;
  u32 handlerIndex;
  u32 *callbackSrc;
  void *target;
  void *targetActor;
  void *targetAgain;
  void *targetActorAgain;

  actor = *((u8 **) (task + 0x38));
  subject = *((u8 **) (task + 0x3C));
  sub_08013C5C(task, actor);
  if ((sub_080141AC(actor, subject) != 1) || ((*((u8 *) (task + 0x70))) != 0))
  {
    sub_08013978(task, *((void **) (subject + 0x28)));
    sub_080142C0(*((void **) (task + 0x28)), *((void **) (subject + 0x28)));
    if ((*((void **) (task + 0x28))) == D_02025FF0.currentTarget)
    {
      stepState = (u8 *) ((((u32) (*((s16 *) (task + 0x22)))) * 2) + ((u32) task));
      if (((u8) (stepState[0x1A] - 1)) > 1)
      {
        stepState[0x1B] = 0;
        callbackSrc = D_08671BDC;
        sub_080C31E8(task + 0x18, task + 0x22, 1, *callbackSrc);
      }
    }
    if (sub_08014328(*((void **) (task + 0x28)), actor, subject) == 0)
    {
      *((u32 *) (task + 0x14)) = (u32) D_0866E610;
      *((u16 *) (task + 0x22)) = (*((u16 *) (task + 0x22))) + 1;
      ;
      *((u8 *) (((u8 *) ((((u32) (*((s16 *) (task + 0x22)))) * 2) + ((u32) task))) + 0x19)) = (*((u8 *) (((u8 *) ((((u32) (*((s16 *) (task + 0x22)))) * 2) + ((u32) task))) + 0x19))) + 1;
      stepOffset = (*((s16 *) (task + 0x22))) * 2;
      stateEntry = task;
      stateEntry += 0x18;
      handlerIndex = *((u8 *) (((u32) stateEntry) + ((u32) stepOffset)));
      sub_080C31E0((s32) task, *((u32 *) ((*((u32 *) (task + 0x14))) + (handlerIndex * 4))));
      *((u16 *) (task + 0x22)) = (*((u16 *) (task + 0x22))) - 1;
    }
    *((u32 *) (subject + 0x08)) = *((u32 *) (task + 0x4C));
    *((u32 *) (subject + 0x0C)) = *((u32 *) (task + 0x5C));
    if ((*((void **) (task + 0x28))) != D_02025FF0.currentTarget)
    {
      target = *((void **) (task + 0x28));
      targetActor = *((void **) (((u8 *) target) + 0x38));
      *((u16 *) actor) = *((u16 *) targetActor);
      targetAgain = *((void * volatile *) (task + 0x28));
      targetActorAgain = *((void **) (((u8 *) targetAgain) + 0x38));
      *((u16 *) (actor + 2)) = *((u16 *) (((u8 *) targetActorAgain) + 2));
    }
    if ((*((u8 *) (task + 0x70))) != 0)
    {
      ((u8 *) (*((void **) (subject + 0x28))))[1] = 0;
    }
    sub_08013C8C(task, actor);
  }
}
