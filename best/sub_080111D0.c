extern u8 D_080CB238[];
extern void copyBytes(void *, void *, u32);
extern volatile int postDisplaySprite(void *, void *, void *, u32, u32);
void sub_080111D0(void *arg0, u16 *entries, u32 a2, u32 a3)
{
  u16 dedupKey[32];
  u16 dedupVal[32];
  u32 table[16];
  u32 r12;
  u32 r10;
  s32 count;
  u32 destOff;
  u16 *p;
  s32 found;
  u32 r7;
  u16 *r2p;
  u16 *r1p;
  s32 k;
  int new_var;
  u32 idx;
  u32 tbl;
  copyBytes(table, D_080CB238, 0x40);
  r12 = 0;
  r10 = 0;
  count = 0;
  destOff = 0;
  p = entries;
  while (1)
  {
    found = 0;
    r7 = p[2] & 0x0FFF;
    if (found < count)
    {
      r2p = dedupVal;
      r1p = dedupKey;
      k = count;
      do
      {
        if (r7 == (*r1p))
        {
          found = 1;
          r12 = *r2p;
        }
        r2p++;
        r1p++;
        k--;
      }
      while (k != 0);
    }
    new_var = 0;
    if (found == 0)
    {
      idx = (((((u32) p[3]) << 16) >> 22) & 3) << 2;
      idx += (((((u32) p[3]) << 16) >> 30) & 3) << 4;
      tbl = *((u32 *) (((u8 *) table) + idx));
      if (p[3] & 0x2000)
      {
        tbl <<= 1;
      }
      postDisplaySprite((void *) 1, (void *) (a2 + (r7 << 5)), (void *) (a3 + (r10 << 5)), tbl << 5, 0x10);
      r12 = ((a3 + 0xF9FF0000U) >> 5) + r10;
      r10 += tbl;
      dedupKey[count] = r7;
      dedupVal[count] = (u16) (r12 & 0x0FFF);
      count++;
    }
    *((u16 *) (((*((vu32 *) (((u8 *) arg0) + 0x24))) + destOff) + 0)) = p[new_var];
    *((u16 *) (((*((vu32 *) (((u8 *) arg0) + 0x24))) + destOff) + 2)) = p[1];
    *((u16 *) (((*((vu32 *) (((u8 *) arg0) + 0x24))) + destOff) + 4)) = (u16) ((p[2] & 0xF000) | (r12 & 0x0FFF));
    *((u16 *) (((*((vu32 *) (((u8 *) arg0) + 0x24))) + destOff) + 6)) = p[3];
    if (p[3] & 1)
    {
      break;
    }
    p += 4;
    destOff += 8;
  }

}

