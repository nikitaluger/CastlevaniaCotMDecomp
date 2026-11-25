/* Refresh an entity's three 4-colour sub-palettes (indices 3-6) from a fixed
 * BGR555 table; sprite type 0xF selects an alternate set for the first one. */
void sub_08045970(void *entity, void *sprite)
{
  void *state;
  void *fxBase;
  u16 *srcColors;
  u16 * volatile *palette3Ptr;
  u16 *srcColors2;
  u16 *srcColors3;
  state = *((void **) (((u8 *) entity) + 0x3C));
  fxBase = ((u8 *) state) + 0x48;
  srcColors = (u16 *) 0x080CF58C;
 do { srcColors2 = srcColors + 8; srcColors3 = srcColors + 12; } while (0);
  if ((*((u16 *) (((u8 *) sprite) + 0x28))) == 0xF)
  {
    srcColors = srcColors + 4;
  }
  (*((u16 * volatile *) (((u8 *) state) + 0x28)))[3] = srcColors[0];
  (*((u16 * volatile *) (((u8 *) state) + 0x28)))[4] = srcColors[1];
  (*((u16 * volatile *) (((u8 *) state) + 0x28)))[5] = srcColors[2];
  (*((u16 * volatile *) (((u8 *) state) + 0x28)))[6] = srcColors[3];
  (*((u16 * volatile *) (((u8 *) fxBase) + 8)))[3] = srcColors2[0];
  (*((u16 * volatile *) (((u8 *) fxBase) + 8)))[4] = srcColors2[1];
  (*((u16 * volatile *) (((u8 *) fxBase) + 8)))[5] = srcColors2[2];
  (*((u16 * volatile *) (((u8 *) fxBase) + 8)))[6] = srcColors2[3];
  palette3Ptr = (u16 * volatile *) (((u8 *) fxBase) + 0xC);
  (*((u16 * volatile *) (((u8 *) fxBase) + 0xC)))[3] = srcColors3[0];
  (*((u16 * volatile *) (((u8 *) fxBase) + 0xC)))[4] = srcColors3[1];
  (*((u16 * volatile *) (((u8 *) fxBase) + 0xC)))[5] = srcColors3[2];
  (*palette3Ptr)[6] = srcColors3[3];
}
