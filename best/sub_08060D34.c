#define REG_DMA3 ((DMA_REG *)0x040000D4)
#define DMA3(S, D, C) do {     REG_DMA3->src = (u32)(S);     REG_DMA3->dst = (D);     REG_DMA3->cnt = (C); } while (0)
#define RB (void)REG_DMA3->cnt
typedef volatile struct 
{
  u32 src;
  u32 dst;
  u32 cnt;
} DMA_REG;
struct S_02021E90
{
  u8 _0[0x13B8];
  u8 b13B8[0x80];
  u8 _1438[4];
  u8 b143C;
  u8 b143D;
  u8 _143E[4];
  u8 b1442;
  u8 b1443;
  u8 _1444[4];
  u32 p1448;
};
extern struct S_02021E90 gCameraState;
extern volatile int postDisplaySprite(void *a, void *b, void *c, u32 d, u32 e);
u32 sub_08060D34(void)
{
  u32 v;
  u8 *new_var;
  do
  {
    switch (gCameraState.b1442)
    {
      case 1:
        if (gCameraState.b143C != 0)
      {
        return postDisplaySprite((void *) 1, &gCameraState.b13B8[0], (void *) gCameraState.p1448, 0x20, 0x10);
      }
        DMA3(&gCameraState.b13B8[0], gCameraState.p1448, 0x80000010);
        return REG_DMA3->cnt;

      case 0:
        if (gCameraState.b1443 & 1)
      {
        if (gCameraState.b143C != 0)
        {
          return postDisplaySprite((void *) 1, &gCameraState.b13B8[0], (void *) gCameraState.p1448, 0x80, 0x10);
        }
        REG_DMA3->src = (u32) (&gCameraState.b13B8[2]);
        v = gCameraState.p1448;
        REG_DMA3->dst = v + 2;
        REG_DMA3->cnt = 0x80000001;
        RB;
        DMA3(&gCameraState.b13B8[6], v + 6, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0xA], v + 0xA, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0xE], v + 0xE, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x12], v + 0x12, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x16], v + 0x16, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x1A], v + 0x1A, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x1E], v + 0x1E, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x22], v + 0x22, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x26], v + 0x26, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x2A], v - (-0x2A), 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x2E], v + 0x2E, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x32], v + 0x32, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x36], v + 0x36, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x3A], v + 0x3A, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x3E], v + 0x3E, 0x80000021);
      }
      else
      {
        if (gCameraState.b143C != 0)
        {
          return postDisplaySprite((void *) 1, &gCameraState.b13B8[0], (void *) gCameraState.p1448, 0x80, 0x10);
        }
        REG_DMA3->src = (u32) (&gCameraState.b13B8[0]);
        v = (REG_DMA3->dst = gCameraState.p1448);
        REG_DMA3->cnt = 0x80000021;
        RB;
        DMA3(&gCameraState.b13B8[0x44], v + 0x44, 0x80000001);
        RB;
        new_var = &gCameraState.b13B8[0x48];
        DMA3(new_var, v + 0x48, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x4C], v + 0x4C, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x50], v + 0x50, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x54], v + 0x54, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x58], v + 0x58, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x5C], v + 0x5C, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x60], v + 0x60, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x64], v + 0x64, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x68], v + 0x68, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x6C], v + 0x6C, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x70], v + 0x70, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x74], v + 0x74, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x78], v + 0x78, 0x80000001);
        RB;
        DMA3(&gCameraState.b13B8[0x7C], v + 0x7C, 0x80000001);
        RB;
      }
        do
      {
        break;
      }
      while (0);

      default:
        return v;

    }

    return REG_DMA3->cnt;
  }
  while (0);
}

