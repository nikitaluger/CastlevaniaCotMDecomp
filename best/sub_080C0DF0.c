struct S
{
  struct 
  {
    u32 pad : 16;
    u32 b2 : 8;
    u32 b3 : 8;
  } w;
  u8 pad4[2];
  u8 b6;
  u8 pad7[3];
  u8 bA;
  u8 padB[0xE];
  u8 b19;
  u8 pad1A;
  u8 b1B;
  u8 b1C;
};
void sub_080C0DF0(struct S *arg0)
{
  u8 b2 = arg0->w.b2;
  u8 b3 = arg0->w.b3;
  u8 avg;
  if (b2 >= b3)
  {
    if ((b2 >> 1) < b3)
    {
      arg0->b1B = 0xFF;
      goto noclamp;
    }
    else
    {
      arg0->b1B = 0x0F;
      goto clamp;
    }
  }
  else
    if ((b3 >> 1) < b2)
  {
    arg0->b1B = 0xFF;
    goto noclamp;
  }
  else
  {
    arg0->b1B = 0xF0;
    goto clamp;
  }
  noclamp:
  avg = (arg0->w.b3 + arg0->w.b2) >> 4;

  goto store_avg;
  clamp:
  avg = (arg0->w.b3 + arg0->w.b2) >> 4;

  arg0->bA = avg;
  if (avg <= 0x0F)
  {
    goto done;
  }
  avg = 0x0F;
  store_avg:
  arg0->bA = avg;

  done:
  arg0->b19 = ((arg0->b6 * arg0->bA) + 0x0F) >> 4;

  b2 = arg0->b1C;
  arg0->b1B = b2 & arg0->b1B;
}

