extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
struct EntryData { u8 _0[6]; u16 angle; };

/* Initialize a scripted object's fixed-point fields from an entry-table record,
 * mark it active, run the spawn callback, then dispatch the next script command
 * through the object's jump table. */
void sub_08044348(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 *entryList;
  u8 *entryBytes;
  u8 *flagPtr;
  s32 rangeBase;
  s32 fineOffset;
  s32 positionFixed;
  s32 coarseOffset;
  s32 positionValue;
  u16 angleBase;
  u8 zero;
  u8 *cmdArgs;
  s32 *pTable;
  entryList = *((s32 **) (self + 0xAC));
  angleBase = *((u16 *) (((u8 *) entryList[1]) + 2));
  rangeBase = ((angleBase | 7) << 16) + (0xA0 << 14);
  *((s32 *) (self + 0x3C)) = rangeBase;
  {
    u32 angleField = ((struct EntryData *)(entryList[1]))->angle;
    u32 masked = 0x7F;
    masked &= angleField;
    fineOffset = (masked << 16) + (0x80 << 12);
  }
  *((s32 *) (self + 0x4C)) = rangeBase - fineOffset;
  entryBytes = (u8 *) entryList[1];
  coarseOffset = ((*((u16 *) (entryBytes + 6))) >> 7) << 16;
  positionValue = ((s32) (*((s16 *) entryBytes))) << 16;
  *((s32 *) (self + 0x5C)) = positionValue - coarseOffset;
  positionFixed = ((s32) (*((s16 *) ((u8 *) entryList[1])))) << 16;
  *((s32 *) (self + 0x6C)) = positionFixed + coarseOffset;
  flagPtr = (u8 *) (self + 0x7C);
  zero = 0;
  *flagPtr = 1;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
  pTable = (s32 *) 0x08671BB0;
  cmdArgs = self + 0x18;
  sub_080C31E4(cmdArgs, self + 0x22, *pTable);
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
  cmdArgs = cmdArgs + ((*((s16 *) (self + 0x22))) * 2);
  sub_080C31E0(self, *((void **) ((*((u32 *) (self + 0x14))) + ((*((u8 *) cmdArgs)) * 4))));
}
