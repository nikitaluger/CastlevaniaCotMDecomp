struct S_D
{
  u8 _0[0x10];
  u32 state10;
  u32 f14;
  u8 _1[4];
  u32 f1C;
  u8 _2[0x1824];
  u32 f1844;
};
extern struct S_D D_02025FF0;
void sub_080C31E8(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

/* Script step (advance-table entry 8): clear the step's sub-state byte, run the
 * advance callback with the global game-state value plus one, bump the
 * sub-state, then dispatch the step's command handler. */
void sub_0808942C(void *arg0)
{
  u8 *self;
  u8 *commandTableBase;
  self = (u8 *) arg0;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
  {
    s32 *advanceTable = (s32 *) 0x08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, D_02025FF0.state10 + 1, *advanceTable);
  }
  {
    u8 *stepByte = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) arg0));
    stepByte[0x19] = (u8) (stepByte[0x19] + 1);
  }
  {
    s32 stepOffset = (*((s16 *) (self + 0x22))) * 2;
    u8 *stepBase = self + 0x18;
    u8 commandId = *(stepBase + stepOffset);
    u8 **commandTable = *((u8 **) (commandTableBase = self + 0x14));
    sub_080C31E0(arg0, commandTable[commandId]);
  }
}
