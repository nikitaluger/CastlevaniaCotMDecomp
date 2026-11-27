extern void *createChildObject(s32, s32);
extern s32 sub_0800F464(u8);
extern s32 setLayerTilemap(s32, s32);
extern s32 sub_0805FEC8(s32);
struct S_020278D0
{
  u8 _0[0x48];
  void *f48;
  u8 _4C[0xF7 - 0x4C];
  u8 fF7;
};
extern struct S_020278D0 gMenuState;
struct S_02021E90
{
  u8 _0[0x1262];
  u16 f1262;
};
extern struct S_02021E90 gCameraState;
struct DMA
{
  volatile u32 src;
  volatile u32 dst;
  volatile u32 ctrl;
};
extern struct DMA D_040000D4;
inline int inline_fn()
{
  return (0xC & gCameraState.f1262) << 0xC;
}

void sub_0800DE50(s32 arg0)
{
  int new_var2;
  u32 new_var3;
  u8 *d;
  u16 sp0;
  u16 *new_var;
  u32 temp_r1;
  void *temp_r0;
  d = (u8 *) 0x02025368;
  setLayerTilemap(0, 0xA8 << 2);
  if (d[0x3C7] != 0)
  {
    sub_0805FEC8(0x8121);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0x2AB);
  new_var2 = 2;
  if (d[0xF2 << new_var2] != 0)
  {
    sub_0805FEC8(0x8122);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0x2B6);
  if (d[0x3C9] != 0)
  {
    sub_0805FEC8(0x8123);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0xB0 << 2);
  if (d[0x3CA] != 0)
  {
    sub_0805FEC8(0x8124);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0x2CB);
  if (d[0x3CB] != 0)
  {
    sub_0805FEC8(0x8125);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0x2D6);
  if (d[0xF3 << 2] != 0)
  {
    sub_0805FEC8(0x8127);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0xB8 << 2);
  if (d[0x3CD] != 0)
  {
    sub_0805FEC8(0x8128);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  setLayerTilemap(0, 0x2EB);
  if (d[0x3CE] != 0)
  {
    sub_0805FEC8(0x8129);
  }
  else
  {
    sub_0805FEC8(0x8120);
  }
  sub_0800F464(gMenuState.fF7);
  new_var3 = (u32) (&sp0);
  sp0 = 0;
  D_040000D4.src = new_var3;
  temp_r1 = inline_fn();
  D_040000D4.dst = temp_r1 + 0x06000040;
  D_040000D4.ctrl = 0x810007E0;
  temp_r1 = D_040000D4.ctrl;
  sp0 = 0;
  new_var = &sp0;
  D_040000D4.src = (u32) new_var;
  D_040000D4.dst = temp_r1 + 0x06000020;
  temp_r1 = (D_040000D4.ctrl = 0x81000010);
  temp_r0 = createChildObject(arg0, 0x1B);
  gMenuState.f48 = temp_r0;
  *((u8 *) (((u8 *) temp_r0) + 0x3C)) = 4;
}

