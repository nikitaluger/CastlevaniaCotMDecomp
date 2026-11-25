s32 sub_08011EE8(void *, s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Advance the entity's physics block one step under gravity 0x16C1; when the
 * step reports it has hit the ground (bit 2 of the block's status word), clear
 * the current step timer and run the next command-script handler. */
void sub_08099880(void *arg0)
{
  s32 *scriptTable;
  void *work;
  work = *((void **) (((u8 *) arg0) + 0x3C));
  sub_08011EE8(work, 0x16C1, 0);
  if (4 & (*((u16 *) (((u8 *) work) + 2))))
  {
    *((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptTable);
  }
}
