struct PaletteEntry
{
  u16 c0[16];
  u16 c1[16];
  s32 v40;
  u32 pad;
};
extern struct PaletteEntry D_020227EC[];
void sub_08000E98(s32 a, void *b, void *c, s32 d, s32 e);

void sub_08006680(s32 start, s32 end)
{
  u16 tmp[0x200];
  s32 i = start;

  if (i <= end)
  {
    do
    {
      struct PaletteEntry *e = &D_020227EC[i];
      s32 v40 = e->v40;
      s32 t = v40 >> 16;
      s32 s = (0x01000000 - v40) >> 16;
      s32 j;

      for (j = 0; j < 16; j++)
      {
        u16 *dst = &tmp[i * 16 + j];
        u16 a = e->c0[j];
        s32 r = (((a & 0x1F) * t) + ((e->c1[j] & 0x1F) * s)) >> 8;
        u16 b = e->c1[j];
        s32 g = (((a & 0x3E0) * t) + ((b & 0x3E0) * s)) >> 8;
        s32 bl = (((a & 0x7C00) * t) + ((b & 0x7C00) * s)) >> 8;
        *dst = (r & 0x1F) | (g & 0x3E0) | (bl & 0x7C00);
      }
      i++;
    } while (i <= end);
  }

  sub_08000E98(1, &tmp[start * 16],
               (void *)(0x05000000 + (start << 5)),
               ((end - start) + 1) << 5, 0x10);
}
