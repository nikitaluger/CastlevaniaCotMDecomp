/* Entity action: copies the paired object's coordinates and a target flag, picks
 * an animation from a per-entity id table, and triggers an attack or a message
 * depending on the entity's mode. */
extern void sub_080114A8(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_08011528(void *, void *);
extern void copyPoseAttrs(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
inline u8 *inline_fn(u8 *arg0)
{
  return arg0 - 4;
}

void sub_080B5F80(void *entity)
{
  u8 *self = entity;
  s32 animSlot = 0;
  u8 *target = *((u8 **) (self + 0x38));
  u8 *state = *((u8 **) (self + 0x3C));
  u8 *anim = state + 0x34;
  u8 *otherState = *((u8 **) ((*((u8 **) (self + 0x28))) + 0x3C));
  u16 flagValue;
  s32 animId;
  s32 entryIdx;
  u8 *entry;
  u32 *tablePtr;
  u8 *tableBase;
  sub_08011528(target, anim);
  *((u32 *) (state + 8)) = *((u32 *) (otherState + 8));
  *((u32 *) (state + 0xC)) = *((u32 *) (otherState + 0xC));
  *((u16 *) (target + 2)) = (flagValue = (*((u16 *) (target + 2))) & 0xFFEF);
  *((u16 *) (target + 2)) = flagValue | ((*((u16 *) ((*((u8 **) ((*((u8 **) (self + 0x28))) + 0x38))) + 2))) & 0x10);
  tablePtr = *((u32 **) (anim + 8));
  entryIdx = (*((s16 *) (anim + 0xE))) + (*((u8 *) (anim + 1)));
  tableBase = (u8 *) (*tablePtr);
  entry = inline_fn(tableBase + (entryIdx * 4));
  animId = *((u16 *) (entry + 2));
  switch (animId)
  {
    case 0x55:
      animSlot = 1;
      break;

    case 0x56:
      animSlot = 2;
      break;

    case 0x57:
      animSlot = 3;
      break;

  }

  copyPoseAttrs(*((void **) (state + 0x28)), (void *) (0x08102CD4 + (animSlot << 3)));
  if ((*((u8 *) (self + 0x4C))) != 0)
  {
    if ((*((u8 *) (anim + 0))) & 2)
    {
      sub_080114A8(target, anim, 0x6C, 1);
    }
  }
  if ((*((u8 *) (self + 0x4C))) == 0)
  {
    setObjectAnimation(target, anim, 0x6A, 0);
    if ((*((u8 *) (anim + 0))) & 2)
    {
      u8 *msgArg0;
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
      {
        s32 *lit = (s32 *) 0x08671BC0;
        msgArg0 = self + 0x18;
        sub_080C31E4(msgArg0, self + 0x22, *lit);
      }
    }
  }
}
