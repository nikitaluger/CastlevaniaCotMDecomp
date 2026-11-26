struct Unk
{
  u8 pad[0x28];
  u32 f28;
  u8 pad2[0x40 - 0x2C];
  u8 *f40;
};
void sub_080C1674(void *arg0, struct Unk *arg1)
{
  u32 val;
  u32 b;
  unsigned int s;
  u8 *p;
  unsigned int *new_var;
  p = arg1->f40;
  val = val & 0xFFFFFF00;
  do { val = val | p[0]; } while (0);
  do { do { b = p[1]; } while (0); } while (0);
  s = b << 8;
  val = val & 0xFFFF00FF;
  val = val | s;
  do { do { s = (b = p[2]) << 16; } while (0); } while (0);
  val = val & 0xFF00FFFF;
  val = (*(new_var = &s)) | val;
  do { do { b = p[3]; } while (0); } while (0);
  s = 24;
  s = b << s;
  val = val & 0x00FFFFFF;
  val = val | s;
  arg1->f28 = val;
  arg1->f40 = p + 4;
}

