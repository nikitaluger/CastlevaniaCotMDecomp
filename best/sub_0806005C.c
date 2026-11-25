extern u8 D_02025358[];
extern u8 D_02021E90[];
extern u16 D_02025FF0[];
extern u8 D_020232C9[];
extern u8 D_084428E0[];
struct E600
{
  u8 _0[4];
  u32 f4;
  u8 _8[0x125A];
  u16 f1262;
  u8 _1264[0x1D5];
  u8 f1439;
  u8 _143A[2];
  u8 f143C;
  u8 _143D[7];
  u8 f1444;
  u8 _1445[0xF];
  u32 f1454;
  u8 f1458;
  u8 _1459[3];
  u8 f145C;
  u8 _145D[0xF];
  u16 f146C;
};
s32 sub_0806005C(void)
{
  struct E600 *e;
  u8 *s;
  u8 *eb;
  u16 tmp;
  u8 b6;
  u8 buf[0x20];
  s = D_02025358;
  eb = D_02021E90;
  if ((*(u8 *) (eb + 0x145C) & 1) == 0)
  {
    *(u8 *) (eb + 0x145C) |= 1;
    return 2;
  }
  e = (struct E600 *) eb;
  b6 = s[0x0C];
  if (e->f4 & 0x10)
  {
    goto do_fill;
  }
  if (b6 & 0x80)
  {
    goto chk_146c;
  }
  if (b6 == 0)
  {
    goto chk_146c;
  }
  if (D_02025FF0[0x14] & 1)
  {
    goto do_fill;
  }
  goto do_buf;
  chk_146c:
  if (e->f146C & 1)
  {
    goto do_fill;
  }

  goto do_buf;
  do_fill:
  {
    volatile u32 *dma;
    u8 v = e->f1439;
    tmp = (u16) ((v << 4) | v);
    dma = (volatile u32 *) 0x040000D4;
    dma[0] = (u32) (&tmp);
    dma[1] = 0x06000020 + ((e->f1262 & 0xC) << 12);
    dma[2] = 0x81000010;
    dma[2];
  }

  goto after_dma;
  do_buf:
  {
    volatile u32 *dma;
    u32 i;
    u8 *tbl = D_084428E0;
    u8 *colors = D_020232C9;
    u8 *colors1 = colors + 1;
    for (i = 0; i < 0x20; i++)
    {
      switch (tbl[i])
      {
        case 0:
          buf[i] = (*colors << 4) | *colors;
          break;

        case 1:
          buf[i] = (*colors << 4) | *colors1;
          break;

        case 0x10:
          buf[i] = (*colors1 << 4) | *colors;
          break;

        case 0x11:
          buf[i] = (*colors1 << 4) | *colors1;
          break;

      }

    }

    dma = (volatile u32 *) 0x040000D4;
    dma[0] = (u32) buf;
    dma[1] = 0x06000020 + ((e->f1262 & 0xC) << 12);
    dma[2] = 0x80000010;
    dma[2];
  }

  after_dma:
  if ((b6 & 0x80) || (b6 == 0))
  {
    if ((e->f146C & 1) == 0)
    {
      if (e)
      {
        return 2;
      }
      else
      {
        return 2;
      }
    }
  }
  else
    if ((D_02025FF0[0x14] & 1) == 0)
  {
    return 2;
  }

  if (e->f145C & 2)
  {
    e->f145C &= 0xFD;
    e->f143C = e->f1444;
  }
  e->f145C &= 0xFE;
  *((u32 *) (&e->f1454)) += 1;
  return 0;
}
