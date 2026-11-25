extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* "Delay 10 frames" script command: takes 10 frames off the shared frame-delay
 * counter (gfxState[4] at 0x03000830+8). When it is about to run out, the
 * current step's flag byte (actor+0x19 + step*2, step = s16 at actor+0x22) is
 * cleared, the script advances one command via sub_080C31E4(actor+0x18,
 * actor+0x22, *scriptTable), the flag is set to 1 and the new command's handler
 * is dispatched from the actor's command table (actor+0x14, indexed by the
 * command byte at actor+0x18 + step*2). */
void sub_08002844(void *actor)
{
  vu16 *gfxState = (vu16 *) 0x03000830;
  int zeroInt;
  u16 framesLeft = gfxState[4];
  void *self;
  zeroInt = 0;
  if (framesLeft <= 0xA)
  {
    s16 step;
    u8 *stepSlot;
    s32 *scriptTable;
    u8 zero = 0;
    gfxState[4] = zeroInt;
    step = *((s16 *) (((u8 *) actor) + 0x22));
    *((u8 *) ((((u8 *) actor) + (step * 2)) + 0x19)) = zero;
    scriptTable = (s32 *) 0x08671BB0;
    stepSlot = ((u8 *) actor) + 0x18;
    sub_080C31E4(stepSlot, ((u8 *) actor) + 0x22, *scriptTable);
    self = actor;
    step = *((s16 *) (((u8 *) actor) + 0x22));
    *((u8 *) ((((u8 *) self) + (step * 2)) + 0x19)) += 1;
    step = *((s16 *) (((u8 *) actor) + 0x22));
    stepSlot += step * 2;
    {
      u8 command = *stepSlot;
      s32 *commandTable = *((s32 **) (((u8 *) actor) + 0x14));
      sub_080C31E0(actor, commandTable[command]);
    }
  }
  else
  {
    gfxState[4] = framesLeft - 0xA;
  }
}
