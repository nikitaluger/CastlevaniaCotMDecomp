extern u16 D_086600A4[];
s32 sub_080C3B80(s32 arg0)
{
  s32 a = arg0;
  s32 v;
  if (v <= (0 - 1))
  {
    v = a;
    v = (0, -v);
  }
  v = (v <= 0xFFF) ? (s32)D_086600A4[v] : 0x10;
  if (arg0 < 0) v = 0 - v;
  return v;
}
