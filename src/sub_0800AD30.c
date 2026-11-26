extern void sub_08005E80(s32);
extern void sub_080102F0(u8);
extern void sub_08010320(u8);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD8[];
extern u8 gGameStatus[];

/* Actor update: clear a flag on the linked object, then, when its trigger byte
 * is set, play a sound and upload its animation graphics; finally reset the
 * object's state field and advance the script step via the callback table. */
void sub_0800AD30(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *gfxBuffer = gGameStatus;
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *gfxIndexPtr;
  u8 *savedIndexPtr;
  u8 i;
  s32 *scriptCb;
  u8 *gfxSrc;
  u8 *statePtr;

  *((u8 *) ((*((u8 **) (work + 0x630))) + 0x40)) = 0;
  if (*((u8 *) (work + 0x639)))
  {
    sub_08005E80(0x155);
    gfxIndexPtr = self + 0x50;
    sub_080102F0(*gfxIndexPtr);
    i = 0;
    gfxBuffer++;
    gfxSrc = work + 0x600;
    savedIndexPtr = gfxIndexPtr;
    do
    {
      gfxBuffer[i] = gfxSrc[i];
      i++;
    }
    while (i <= 7);
    sub_08010320(*savedIndexPtr);
  }
  statePtr = (u8 *)(work + 0x635);
  i = 0;
  *statePtr = 3;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x17)) = i;
  scriptCb = (s32 *) 0x08671BD8;
  sub_080C31E8(self + 0x18, self + 0x22, 0x10, *scriptCb);
}
