extern s32 sub_08000EDC(s32 mode, s32 src, s32 dest, s32 size, s32 width);
extern void sub_08000F50(void);
extern void sub_08008C78(void *work);
extern s32 sub_080C2F24(s32 value, s32 divisor); /* BIOS Div: returns the remainder */
extern void sub_080C31E8(void *scriptData, void *scriptIndex, s32 arg, s32 callback);

inline s8 *inline_fn(void *arg0)
{
  return (s8 *) arg0;
}

/* Updates a graphics effect: ticks a frame counter and a global counter (every 14
 * frames), refills and DMA-transfers the double-buffered pattern while the script
 * flag is clear, and fires a script callback when the global count reaches 16. */
void sub_08008A60(void *arg0)
{
  s32 frameCount;
  void *work;
  s32 *callback;
  work = *((void **) (inline_fn(arg0) + 0x3C));
  frameCount = (*((s32 *) (inline_fn(work) + 0x10))) + 1;
  *((s32 *) (inline_fn(work) + 0x10)) = frameCount;
  if (sub_080C2F24(frameCount, 0xE) == 0)
  {
    *((u16 *) (inline_fn((void *) 0x03000830) + 8)) = (u16) ((*((u16 *) (inline_fn((void *) 0x03000830) + 8))) + 1);
  }
  if (!(1 & (*((u8 *) (inline_fn(((*((s16 *) (inline_fn(arg0) + 0x22))) * 2) + arg0) + 0x19)))))
  {
    *((s32 *) (((s8 *) work) + 0xC)) = (s32) ((*((s32 *) (((s8 *) work) + 0xC))) - 1);
    sub_08008C78(work);
    sub_08000EDC(0, work + (((*((s32 *) (inline_fn(work) + 0x14))) * 0x140) + 0x1C), 0x04000012, 2, 0x10);
    *((s32 *) (inline_fn(work) + 0x14)) = (s32) (((*((s32 *) (((s8 *) work) + 0x14))) + 1) & 1);
  }
  if ((*((u16 *) (inline_fn((void *) 0x03000830) + 8))) == 0x10)
  {
    sub_08000F50();
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    callback = &(*((s32 *) 0x08671BD0));
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 8, *callback);
  }
}
