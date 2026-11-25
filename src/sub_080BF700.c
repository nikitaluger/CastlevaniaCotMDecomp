/* Clear DISPCNT bit 3, set bit 0, wait for VBlank, then write DISPCNT back. */
void sub_080BF700(void)
{
  vu8 *dispstatRead;
  u16 dispCnt = *((vu16 *) 0x04000000);
  {
    s16 mask = 8;
    do
    {
      dispCnt &= (u16) (-mask);
    }
    while (0);
  }
  dispCnt |= 1;
  {
    vu8 *dispstat = (vu8 *) 0x04000004;
    if (((*dispstat) & 2) == 0)
    {
      u8 vblankBit = 2;
      dispstatRead = dispstat;
      do
      {
      }
      while (((*dispstatRead) & vblankBit) == 0);
    }
  }
  *((vu16 *) 0x04000000) = dispCnt;
}
