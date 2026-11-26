#define U(p) (*(u32*)(p))
#define H(p) (*(u16*)(p))
#define W(p) (*(vu32*)(p))
void allocWorkSlot(u8 *, s32, s32, s32);
void clearActorPool(void);
void decompressToVram(u32, u32);
void postDisplaySprite(s32, u32, u32, s32, s32);
void resetMapRender(void);
void setMapLayerParams(s32, s32, s32);
void setScreenTransition(s32);
void sub_08010250(void);
void sub_080C31E4(u8 *, u8 *, u32);
void sub_080C31E0(u8 *, u32);
extern u16 D_03000830;
inline u8 *inline_fn(u8 *arg0, int arg1)
{
  return (u8 *) (arg0 + arg1);
}

/* Initialises the current scene: allocates its work block, clears the actor pool and camera state, decompresses the scene's graphics into VRAM, sets up the map layers and display sprite, then starts the scene's script. */ void initScene(u8 *obj)
{
  u8 *base;
  u8 *r8p;
  u8 *p;
  vu16 *reg;
  vu32 *dma;
  u32 zero;
  u32 zero2;
  u32 dmaDst;
  u32 tmp;
  u8 *ptr;
  u32 *pp;
  s16 idx;
  u8 b;
  u16 buf;
  r8p = (u8 *) 0x02025358;
  allocWorkSlot(obj, 0, 0x63C, 0);
  base = (u8 *) 0x02021E90;
  {
    u8 *q0 = base + 0x125C;
    zero = 0;
    U(q0) = zero;
  }
  reg = &D_03000830;
  zero2 = 0;
  *reg = ((*reg) & 0xF0FF) | zero2;
  ptr = inline_fn(base, 0x1260);
  {
    u32 v = 0xD800;
    H(ptr) = v;
  }
  {
    u8 *q1 = base + 0x12A0;
    u32 v = 0xF800;
    H(q1) = v;
  }
  {
    u8 *q1 = base + 0x1320;
    H(q1) = zero;
  }
  ptr = inline_fn(ptr, 0x80);
  H(ptr) = zero;
  {
    u8 *q3 = base + 0x1262;
    u32 v = 0x0B;
    H(q3) = v;
  }
  ptr = inline_fn(ptr, -0x3E);
  {
    u32 v = 0x0B;
    v += 0xFE;
    H(ptr) = v;
  }
  {
    u8 *q2 = base + 0x1278;
    ptr = inline_fn(ptr, -0x26);
    U(ptr) = zero;
    U(q2) = zero;
  }
  {
    u8 *q2 = base + 0x12B8;
    ptr = inline_fn(ptr, 0x40);
    U(ptr) = zero;
    U(q2) = zero;
  }
  clearActorPool();
  buf = 0;
  dma = (vu32 *) 0x040000D4;
  W(dma) = (u32) (&buf);
  dmaDst = 0xC0 << 19;
  W(dma + 1) = dmaDst;
  W(dma + 2) = 0x8100C000;
  tmp = W(dma + 2);
  decompressToVram(0x08639F0C, 0x06008000);
  decompressToVram(0x0863B158, 0x0600A000);
  decompressToVram(0x0863D4CC, dmaDst);
  decompressToVram(0x0863D730, 0x06000800);
  decompressToVram(0x0863D8C0, 0x06001000);
  decompressToVram(0x0863DB80, 0x06001800);
  decompressToVram(0x0863DDD8, 0x06002000);
  decompressToVram(0x0863E028, 0x06002800);
  decompressToVram(0x0863E280, 0x06003000);
  decompressToVram(0x0863E588, 0x06003800);
  postDisplaySprite(1, 0x0863D42C, 0x050000A0, 0x60, 0x10);
  decompressToVram(0x0863D224, 0x06010000);
  postDisplaySprite(1, 0x0863D48C, 0x05000380, 0x40, 0x10);
  resetMapRender();
  setMapLayerParams(0, 1, 1);
  setScreenTransition(0);
  sub_08010250();
  r8p[0x0C] = (u8) zero2;
  idx = *((s16 *) (obj + 0x22));
  *inline_fn(obj + (idx * 2), 0x19) = (u8) zero2;
  pp = (u32 *) 0x08671BB0;
  p = obj + 0x18;
  sub_080C31E4(p, obj + 0x22, *pp);
  idx = *((s16 *) (obj + 0x22));
  *inline_fn(obj + (idx * 2), 0x19) += 1;
  idx = *((s16 *) (obj + 0x22));
  b = *inline_fn(p, idx * 2);
  sub_080C31E0(obj, U((*((u32 *) (obj + 0x14))) + (b * 4)));
}
