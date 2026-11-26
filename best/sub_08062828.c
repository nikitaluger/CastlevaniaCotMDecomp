extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0c
{
  u8 _0[0x14EC];
  u8 f14EC;
  u8 f14ED;
  u8 f14EE;
  u8 f14EF;
  u8 f14F0;
  u8 _1[0x1508 - 0x14F1];
  s32 f1508;
  u8 _2[0x1780 - 0x150C];
  s32 f1780[0x20];
};
extern struct S_02025FF0c gMainWorkspace;
extern u8 gGameStatus;
struct DMA3
{
  vu32 src;
  vu32 dst;
  vu32 ctrl;
};
extern struct DMA3 D_040000D4;
inline static u8 andBF(u8 b)
{
  u32 m = 0xBF;
  m &= b;
  return (u8) m;
}

void sub_08062828(u8 *arg0)
{
  void *obj;
  s32 **new_var;
  u8 *p5368 = &gGameStatus;
  struct DMA3 *dma;
  unsigned int i;
  s32 *g;
  void *new_var2[2];
  s32 zero;
  if ((allocWorkSlot(arg0, 0, 0x138, 3) == 0) || ((obj = allocSpriteObject(), obj == 0)))
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  *((void **) (arg0 + 0x38)) = obj;
  *((s32 *) (((u8 *) obj) + 0x1C)) = 0x80000005;
  {
    u8 *p2a = ((u8 *) obj) + 0x2A;
    *p2a = andBF(*p2a);
  }
  gMainWorkspace.f14EE = 0;
  gMainWorkspace.f14ED = 0;
  gMainWorkspace.f14F0 = 0;
  gMainWorkspace.f14EC = 0;
  gMainWorkspace.f1508 = *((s32 *) (p5368 + 0x300));
  dma = &D_040000D4;
  dma->src = 0x084548A4;
  dma->dst = 0x06016000;
  dma->ctrl = 0x80000DE0;
  (void) dma->ctrl;
  dma->src = 0x08472074;
  dma->dst = 0x06011800;
  dma->ctrl = 0x80000400;
  (void) dma->ctrl;
  dma->src = 0x08453EC0;
  dma->dst = 0x05000220;
  dma->ctrl = 0x80000030;
  (void) dma->ctrl;
  dma->src = 0x08453F20;
  dma->dst = 0x05000380;
  dma->ctrl = 0x80000040;
  (void) dma->ctrl;
  i = 0;
  g = (s32 *) 0x08671BB0;
  new_var2[0] = arg0 + 0x18;
  new_var2[1] = arg0 + 0x22;
  zero = 0;
  {
    s32 *p = (s32 *) (((u8 *) (&gMainWorkspace)) + 0x1780);
    for (; i < 0x20; i++)
    {
      do { *(p++) = zero; } while (0);
    }

  }
  gMainWorkspace.f1780[0] = (s32) arg0;
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
  new_var = &g;
  sub_080C31E4(new_var2[0], new_var2[1], *(*new_var));
}

