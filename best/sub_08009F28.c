void sub_080103BC(u8);
s32 sub_080103F0(u8);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
extern u8 D_02025358[];
extern u8 D_080CAB64[];
extern vu32 D_040000D4[];
inline int inline_fn(s32 arg0, int arg1)
{
  return arg0 * arg1;
}

void sub_08009F28(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *p = D_02025358;
  u8 *p3C = *((u8 **) (self + 0x3C));
  volatile u16 sp0;
  u32 i;
  u32 j;
  u32 dst;
  u8 b0;
  dst = 0;
  *((u32 *) (self + 0x6C)) = dst;
  for (i = 0; i < 8; i++)
  {
    u8 b = (u8) i;
    if (sub_080103F0(b) == 0)
    {
      sub_080103BC(b);
    }
    else
    {
      *((u32 *) (self + 0x6C)) |= 1 << i;
    }
  }

  b0 = p[0x0B];
  *(p3C + 0x634) = b0;
  dst = 0x06001182;
  for (j = 0; j < 4; j++)
  {
    u32 bit = ((*(p3C + 0x634)) >> D_080CAB64[j]) & 1;
    if (bit == 0)
    {
      sp0 = bit;
      {
        vu32 *dma = D_040000D4;
        dma[0] = (u32) (&sp0);
        dma[1] = dst;
        dma[2] = 0x8100000B;
        (void) dma[2];
      }
      sp0 = bit;
      {
        vu32 *dma = D_040000D4;
        dma[0] = (u32) (&sp0);
        dma[1] = dst + 0x40;
        dma[2] = 0x8100000B;
        (void) dma[2];
      }
    }
    dst += 0x80;
  }

  {
    u8 *base = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
    *((u8 *) (base + 0x19)) = 0;
  }
  sub_080C31E4(self + 0x18, self + 0x22, *((u32 *) 0x08671BB0));
  {
    u8 *base = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
    *((u8 *) (base + 0x19)) = (*((u8 *) (base + 0x19))) + 1;
  }
  {
    s32 idx = inline_fn((s32) ((s16) (*((s16 *) (self + 0x22)))), 2);
    u8 *q = (self + 0x18) + idx;
    u8 byte = *q;
    s32 funcptr = *((s32 *) (((u32) (byte * 4)) + (*((u32 *) (self + 0x14)))));
    sub_080C31E0((s32) self, funcptr);
  }
}

