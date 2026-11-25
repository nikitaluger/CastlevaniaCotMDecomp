/* Spawn a fresh child actor for this script step after a capacity check: set a
 * flag bit and a global display value on it, clear the current script slot,
 * then dispatch the next command in the table. */
struct S_02025FF0
{
  u8 _[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
s32 sub_0800168C(void *, s32, s32, s32);
void *sub_0800355C(void);
void sub_0806D2D0(void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
struct ST { u8 pad[2]; u16 f2; };
void sub_08082708(void *scriptStep)
{
  void *newActor;
  u8 zero;
  struct ST *actorFlags;
  if (sub_0800168C(scriptStep, 0, 0x68, 3) == 0)
  {
    sub_080C31E0(scriptStep, *((s32 *) (((u8 *) scriptStep) + 0x24)));
    return;
  }
  newActor = sub_0800355C();
  if (newActor == NULL)
  {
    sub_0806D2D0(scriptStep);
    return;
  }
  *((void **) (((u8 *) scriptStep) + 0x38)) = newActor;
  *((s32 *) (((u8 *) newActor) + 0x1C)) = 0x80000004;
  actorFlags = (struct ST *)newActor;
  actorFlags->f2 |= 0x400;
  zero = 0;
  *((u16 *) newActor) = D_02025FF0.w;
  *((u8 *) ((((u8 *) scriptStep) + ((*((s16 *) (((u8 *) scriptStep) + 0x22))) * 2)) + 0x19)) = zero;
  {
    s32 *paramPtr = (s32 *) 0x08671BB0;
    sub_080C31E4(scriptStep + 0x18, scriptStep + 0x22, *paramPtr);
  }
  {
    u8 *slotPtr = (u8 *) ((((u32) (*((s16 *) (((u8 *) scriptStep) + 0x22)))) * 2) + ((u32) scriptStep));
    slotPtr[0x19] = (u8) (slotPtr[0x19] + 1);
  }
  {
    s32 cmdOffset = (*((s16 *) (((u8 *) scriptStep) + 0x22))) * 2;
    u8 *cmdArray = ((u8 *) scriptStep) + 0x18;
    u8 cmdIndex = *(cmdArray + cmdOffset);
    u8 **cmdTable = *((u8 **) (((u8 *) scriptStep) + 0x14));
    sub_080C31E0(scriptStep, (s32) cmdTable[cmdIndex]);
  }
}
