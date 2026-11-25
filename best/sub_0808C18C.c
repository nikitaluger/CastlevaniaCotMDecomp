extern u8 D_02025FF0[];
extern u8 D_02025368[];
extern u32 D_085D3CC4[];
extern u32 D_085D3D24[];
struct DMA
{
  u32 a;
  u32 b;
  u32 c;
};
void sub_0808C18C(void)
{
  int new_var3;
  volatile struct DMA *new_var2;
  volatile struct DMA *dma = (volatile struct DMA *) 0x040000D4;
  u32 new_var;
  u32 src;
  (void) D_02025368;
  new_var2 = dma;
  switch ((D_02025FF0[0x50] << 8) + D_02025FF0[0x51])
  {
    case 0xA01:

    case 0xA03:

    case 0xA05:

    case 0xA06:

    case 0xA09:

    case 0xA0A:

    case 0xA0B:
      if ((*((vu8 *) 0x3CF)) == 3)
    {
      src = (u32) D_085D3CC4;
    }
    else
    {
      new_var = (u32) D_085D3D24;
      src = new_var;
    }
      dma->a = src;
      dma->b = 0x050001E0;
      dma->c = (dma->c = 0x050002C0);
      new_var3 = 0x050001E0;
      (void) (*((vu32 *) (new_var3 + 8)));
      dma->b = new_var3;
      dma->a = src;
      (void) new_var2->c;
      break;

    default:
      break;

  }

}

