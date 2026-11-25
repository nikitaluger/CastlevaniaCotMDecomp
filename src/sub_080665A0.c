extern s32 sub_0806A7AC(s32, s32, s32);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
inline int addScrollOrigin(int addr)
{
  return (*((s32 *) addr)) + 0x00600000;
}

/* Loads an actor's tiles and palette by DMA, computes its scroll offset,
 * advances its animation step and dispatches the resulting state. */
void sub_080665A0(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 *scroll;
  s16 step;
  s32 mapPtr = *((s32 *) (self + 0x6C));
  s32 work = mapPtr + 4;
  s32 gfxPtr = *((s32 *) (self + 0x38));
  sub_0806A7AC(gfxPtr, work, 0x57);
  *((s32 *) (mapPtr + 0x108)) = *((s32 *) (work + 4));
  scroll = (s32 *) (mapPtr + 0x110);
  *scroll = addScrollOrigin(work + 4) - (*((s32 *) (gfxPtr + 0x18)));
  {
    void *sub = sub_0806D2A0(arg0, 0x34, 0x0A, 0x12);
    if (sub != 0)
    {
      *((u16 *) (((u8 *) sub) + 0x7C)) = 0;
    }
  }
  {
    volatile u32 *dma = (volatile u32 *) 0x040000D4;
    dma[0] = 0x08472B04;
    dma[1] = 0x06013000;
    dma[2] = 0x80000400;
    (void) dma[2];
    dma[0] = 0x084F8038;
    dma[1] = 0x05000280;
    dma[2] = 0x80000010;
    (void) dma[2];
  }
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
  {
    const u32 *animCmd = (const u32 *) 0x08671BB0;
    void *sequence = self + 0x18;
    sub_080C31E4(sequence, self + 0x22, *animCmd);
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
    work = 2;
    step = *((s16 *) (self + 0x22));
    sequence = ((u8 *) sequence) + (step * work);
    sub_080C31E0(arg0, *((u32 *) ((*((u32 *) (self + 0x14))) + ((*((u8 *) sequence)) * 4))));
  }
}
