/* Per-scanline alpha-blend ramp: waits for a VBlank/HBlank window, sets
 * BLDCNT/BLDALPHA for the current scanline from the eva/evb counters in
 * gCameraState, steps those counters, then reprograms the DISPSTAT VCOUNT
 * compare (current line + 4) for the next scanline. */
void sub_080BF73C(void)
{
  u32 nextLine = (*((vu8 *) 0x04000006)) + 4;
  vu8 *dispstat;
  vu8 *dispstatCopy;
  u8 *blendState;
  int vblankFlag;
  s32 evaScaled;
  if (nextLine > 0x9F)
  {
    nextLine = 0;
  }
  dispstat = (vu8 *) 0x04000004;
  vblankFlag = (*dispstat) & 2;
  blendState = (u8 *) 0x02021E90;
  if (vblankFlag == 0)
  {
    u16 vblankMask = 2;
    dispstatCopy = &(*dispstat);
    do
    {
    }
    while (((*dispstatCopy) & vblankMask) == 0);
  }
  *((vu16 *) 0x04000050) = 0x142;
  {
    vu16 *bldAlpha = (vu16 *) 0x04000052;
    s32 *pEva = (s32 *) (blendState + 0x136C);
    s32 eva = *pEva;
    s32 evaShifted = eva << 8;
    s32 *pEvb = (s32 *) (blendState + 0x1368);
    s32 evb = *pEvb;
    evaScaled = evaShifted;
    *bldAlpha = (u16) (evaScaled | evb);
    *pEvb = evb - 1;
    *pEva = eva + 1;
    if ((evb - 1) >= 0)
    {
      *((vu8 *) 0x04000005) = (u8) nextLine;
    }
  }
}
