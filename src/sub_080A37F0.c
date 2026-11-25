inline int inline_fn(void *arg0, s32 arg1)
{
  return ((s32) arg0) + arg1;
}

/* Periodic ring-spawn update: advances a cooldown; on expiry it picks the Nth
 * free slot in the entity's slot array, derives an offset angle from that slot,
 * spawns an object around the entity through a sine lookup, and finally emits a
 * completion message once all ten steps have run. */
void sub_080A37F0(void *entity)
{
  void *targetObj;
  void *state;
  void *stateTail;
  void *ctrl;
  void *stateArg;
  void *ctrlArg;
  s32 cooldown;
  s32 targetCount;
  u32 slot;
  u32 candidate;
  void *slotArray;
  void *sinFunc;
  s32 angle;
  s32 sinX;
  s32 posX;
  s32 sinY;
  s32 posY;
  extern s32 D_08671BFC;
  extern s32 D_08671BD0;
  targetObj = *((void **) (((u8 *) entity) + 0x38));
  state = *((void **) (((u8 *) entity) + 0x3C));
  stateTail = (void *) (((u8 *) state) + 0x34);
  ctrl = (void *) (((u8 *) state) + 0x48);
  stateArg = state;
  ctrlArg = ctrl;
  sub_080A3E8C(targetObj, stateTail, stateArg, ctrlArg);
  cooldown = *((s32 *) (((u8 *) ctrl) + 0x34));
  if (cooldown == 0)
  {
    targetCount = sub_08005820(9 - (*((s32 *) (((u8 *) ctrl) + 0x30))));
    slot = 0;
    candidate = 0;
    if ((*((s32 *) (((u8 *) state) + 0x54))) != 0)
    {
      slotArray = (void *) (((u8 *) state) + 0x54);
      goto scan_slots;
    }
    slotArray = (void *) (((u8 *) state) + 0x54);
    if (cooldown == targetCount)
    {
      goto spawn;
    }
    advance_slot:
    slot += 1;

    scan_slots:
    candidate += 1;

    if (candidate > 8)
    {
      goto spawn;
    }
    if ((*((s32 *) ((u8 *) inline_fn(slotArray, (s32) (candidate * 4))))) != 0)
    {
      goto scan_slots;
    }
    if (slot != targetCount)
    {
      goto advance_slot;
    }
    slot = candidate;
    spawn:
    *((s32 *) ((u8 *) inline_fn(slotArray, (s32) (slot * 4)))) = 1;

    sinFunc = (void *) (&D_08671BFC);
    angle = slot << 12;
    sinX = _call_via_r1(angle + 0x4000, *((s32 *) sinFunc)) >> 8;
    posX = (*((s32 *) (((u8 *) state) + 0x08))) + (sinX * 0x3000);
    sinY = _call_via_r1(angle, *((s32 *) sinFunc)) >> 8;
    posY = (*((s32 *) (((u8 *) state) + 0x0C))) + (sinY * 0x3000);
    sub_080A55D8(posX, posY);
    *((s32 *) (((u8 *) ctrl) + 0x30)) = (*((s32 *) (((u8 *) ctrl) + 0x30))) + 1;
    *((s32 *) (((u8 *) ctrl) + 0x34)) = 0x1E;
  }
  else
  {
    *((s32 *) (((u8 *) ctrl) + 0x34)) = cooldown - 1;
  }
  if ((*((s32 *) (((u8 *) ctrl) + 0x30))) != 9)
  {
    return;
  }
  {
    void *msgFunc;
    ((u8 *) entity)[0x19 + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)] = 0;
    msgFunc = (void *) (&D_08671BD0);
    _call_via_r3(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 2, *((s32 *) msgFunc));
  }
}
