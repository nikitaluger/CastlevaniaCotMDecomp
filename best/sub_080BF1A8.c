extern u16 sub_080C2F20(s32 a, s32 b);
extern s16 D_08103318[];
struct BgIo2
{
  u8 pad0[0x20];
  u16 f20;
  u8 pad22[2];
  u16 f24;
  u8 pad26[2];
  u16 f28;
  u8 pad2A[2];
  u16 f2C;
};
inline static u16 addOffset(u8 value, u16 offset)
{
  s32 tmp = value;
  tmp += offset;
  return tmp;
}
inline static s32 andBits(s32 a, u8 b)
{
  s32 r = a;
  r &= b;
  return r;
}

void sub_080BF1A8(void)
{
  u8 *base = (u8 *) 0x02021E90;
  u16 sp[4];
  u8 *p1;
  u8 *p2;
  u8 t;
  p1 = base + 0x136D;
  p2 = base + 0x1376;
  t = *p1;
  if (t > (*p2))
  {
    u16 *dst = sp;
    u16 *src = (u16 *) 0x03000830;
    dst[0] = src[0x10];
    dst[1] = src[0x12];
    dst[2] = src[0x14];
    dst[3] = src[0x16];
  }
  else
  {
    u16 r3;
    u8 b;
    *p1 = t + (*(base + 0x1378));
    *((vu8 *) 0x04000005) = (*p1) - 1;
    r3 = sub_080C2F20(0x80, D_08103318[*(base + 0x136F)] * (*(base + 0x137A)));
    b = *(base + 0x137B);
    if (b & 1)
    {
      u16 *dst = sp;
      dst[0] = addOffset(*(base + 0x1370), r3);
    }
    else
    {
      sp[0] = ((struct BgIo2 *) 0x03000830)->f20;
    }
    {
      u8 *base2 = (u8 *) 0x02021E90;
      b = *(base2 + 0x137B);
      if (b & 2)
      {
        u16 *dst = sp;
        dst[1] = addOffset(*(base2 + 0x1371), r3);
      }
      else
      {
        sp[1] = ((struct BgIo2 *) 0x03000830)->f24;
      }
      b = *(base2 + 0x137B);
      if (b & 4)
      {
        u16 *dst = sp;
        dst[2] = addOffset(*(base2 + 0x1372), r3);
      }
      else
      {
        sp[2] = ((struct BgIo2 *) 0x03000830)->f28;
      }
      b = *(base2 + 0x137B);
      if (b & 8)
      {
        u16 *dst = sp;
        dst[3] = addOffset(*(base2 + 0x1373), r3);
      }
      else
      {
        sp[3] = ((struct BgIo2 *) 0x03000830)->f2C;
      }
      *(base2 + 0x136F) += *(base2 + 0x1377);
    }
  }
  {
    vu8 *dispstat = (vu8 *)0x04000004;
    if (!andBits(2, *dispstat))
    {
      s32 mask = 2;
      while (!andBits(mask, *dispstat))
      {
      }
    }
  }
  *((vu16 *) 0x04000012) = sp[0];
  *((vu16 *) 0x04000016) = sp[1];
  *((vu16 *) 0x0400001A) = sp[2];
  *((vu16 *) 0x0400001E) = sp[3];
}
