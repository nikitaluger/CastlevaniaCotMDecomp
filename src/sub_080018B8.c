extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

struct InputRegs {
    u16 pad0;
    u16 pad2;
    u16 flashColor;
    u16 blend;
    u16 delay;
};

/* Script command: sets the screen flash colour and clears the frame delay and
 * the current script sub-state, advances the script, then marks the new step's
 * sub-state (1) and dispatches that step's command handler. */
void sub_080018B8(void *arg0)
{
  u8 *self = (u8 *) arg0;
  struct InputRegs *reg = (struct InputRegs *)0x03000830;
  u8 *stepBase;
  u8 commandId;
  s32 *advanceTable;
  s16 *stepPtr;

  reg->flashColor = 0xBF;
  reg->delay = 0;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
  advanceTable = (s32 *) 0x08671BB0;
  stepBase = self + 0x18;
  sub_080C31E4(stepBase, self + 0x22, *advanceTable);
  stepPtr = &(*((s16 *) (self + 0x22)));
  *((u8 *) ((self + ((*stepPtr) * 2)) + 0x19)) += 1;
  stepBase += (*stepPtr) * 2;
  commandId = *((u8 *) stepBase);
  sub_080C31E0(self, *((u32 *) ((*((u32 *) (self + 0x14))) + (commandId * 4))));
}
