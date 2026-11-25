extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

struct Reg03000830 {
    u16 pad0;
    u16 pad2;
    u16 field4;
    u16 pad6;
    u16 field8;
};

// Sets two system registers, clears then re-increments the object's frame
// counter, loads frame data through a pointer table, then dispatches the frame's
// handler function chosen by the byte at frameTable[id].
void sub_08001918(void *arg0)
{
  u8 *self = (u8 *) arg0;
  struct Reg03000830 *reg = (struct Reg03000830 *)0x03000830;
  u8 *frameTable;
  u8 handlerIndex;
  s32 *dataTablePtr;
  s16 *idPtr;

  reg->field4 = 0xFF;
  reg->field8 = 0;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
  dataTablePtr = (s32 *) 0x08671BB0;
  frameTable = self + 0x18;
  sub_080C31E4(frameTable, self + 0x22, *dataTablePtr);
  idPtr = &(*((s16 *) (self + 0x22)));
  *((u8 *) ((self + ((*idPtr) * 2)) + 0x19)) += 1;
  frameTable += (*idPtr) * 2;
  handlerIndex = *((u8 *) frameTable);
  sub_080C31E0(self, *((u32 *) ((*((u32 *) (self + 0x14))) + (handlerIndex * 4))));
}
